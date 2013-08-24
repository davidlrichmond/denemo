//      sourceaudio.c
//      
//      Copyright 2012 Richard Shann <rshann@debian2>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <stdio.h>
#include <sndfile.h>
#include <fcntl.h>
#include <aubio/aubio.h>
#include "utils.h"
#include "midi.h"
#include "sourceaudio.h"
#include "keyresponses.h"
#include "audiointerface.h"
#if GTK_MAJOR_VERSION==3
#include <gdk/gdkkeysyms-compat.h>      //FIXME Look for something more gtk3 like
#endif

static gint leadin = 0;         //number of frames of silence before playing audio
static gboolean playing = FALSE;




//Creates a list of times which the aubio onset detector thinks are note onset times for the audio Denemo->si->audio
//Result is placed in Denemo->si->note_onsets
void generate_note_onsets(void)
{
  DenemoAudio *audio = Denemo.gui->si->audio;
  gint channels = audio->channels;
  
 aubio_onsetdetection_type type_onset = aubio_onset_kl;
 aubio_onsetdetection_type type_onset2 = aubio_onset_complex;
 smpl_t threshold = 0.3;
 smpl_t silence = -90.;
 uint_t buffer_size = 1024;
 uint_t overlap_size = 512;       

 uint_t samplerate = 44100;

 aubio_pvoc_t *pv;
 fvec_t *ibuf;
 fvec_t *obuf;
 cvec_t *fftgrain;

 aubio_onsetdetection_t *o;
 aubio_onsetdetection_t *o2;
 fvec_t *onset;
 fvec_t *onset2;
 int isonset = 0;
 aubio_pickpeak_t *parms;
  
  
  
  unsigned int pos = 0;         /*frames%dspblocksize */
  unsigned int i;               /*channels */
  unsigned int j;               /*frames */

  busy_cursor (Denemo.notebook);
  gtk_window_set_modal (progressbar (_("Analysing Audio"), NULL), TRUE);
   
  ibuf = new_fvec (overlap_size, channels);
  obuf = new_fvec (overlap_size, channels);
  fftgrain = new_cvec (buffer_size, channels);
 
   /* phase vocoder */
  pv = new_aubio_pvoc (buffer_size, overlap_size, channels);
  /* onsets */
  parms = new_aubio_peakpicker (threshold);
  o = new_aubio_onsetdetection (type_onset, buffer_size, channels);
  
  // if (usedoubled)
   // {
      o2 = new_aubio_onsetdetection (type_onset2, buffer_size, channels);
      onset2 = new_fvec (1, channels);
   // }
    
  onset = new_fvec (1, channels);
  rewind_audio ();
  if(audio->onsets)
	{
		g_list_free(audio->onsets);
		audio->onsets = NULL;
	}
  for (j = 0; j < (unsigned) audio->nframes; j++)
    {	
         sf_read_float (audio->sndfile, ibuf->data[0]+pos, 2); //g_print("\t%f", ibuf->data[0][pos]);
		if (pos == overlap_size - 1)
			{
			/* block loop */
			gtk_main_iteration_do (FALSE);
			aubio_pvoc_do (pv, ibuf, fftgrain);
						while (gtk_events_pending ())
  gtk_main_iteration ();

			aubio_onsetdetection (o, fftgrain, onset);
						while (gtk_events_pending ())
  gtk_main_iteration ();

			     // if (usedoubled) {
        aubio_onsetdetection(o2,fftgrain, onset2);
        			while (gtk_events_pending ())
  gtk_main_iteration ();

        onset->data[0][0] *= onset2->data[0][0];
     // }
			isonset = aubio_peakpick_pimrt (onset, parms);
			if(isonset)
				audio->onsets = g_list_append(audio->onsets, GINT_TO_POINTER(j) /* /audio->samplerate for seconds */);
          
			pos = -1;                 /* so it will be zero next j loop */
			}                           /* end of if pos==overlap_size-1 */
  pos++;
	}


  del_aubio_onsetdetection (o2);
  del_fvec (onset2);

  del_aubio_onsetdetection (o);
  del_aubio_peakpicker (parms);
  del_aubio_pvoc (pv);
  del_fvec (obuf);
  del_fvec (ibuf);
  del_cvec (fftgrain);
  del_fvec (onset);
  aubio_cleanup ();











  progressbar_stop();
  normal_cursor(Denemo.notebook);  

#ifdef DEBUG
GList *g;
for(g=audio->onsets;g;g=g->next) {
	g_print("Note at %f seconds\n", ((gint)g->data)/(double)audio->samplerate);
}
#endif
}

gboolean
get_audio_sample (float *sample)
{
  if (!playing)
    return FALSE;
  gboolean ret = FALSE;
  if (leadin)
    {
      *sample = *(sample + 1) = 0.0;
      leadin--;
      ret = TRUE;
    }
  else
    {
      if (Denemo.gui->si && Denemo.gui->si->audio && Denemo.gui->si->audio->sndfile)
        {
          ret = (2 == sf_read_float (Denemo.gui->si->audio->sndfile, sample, 2));
          if (ret)
            *sample *= Denemo.gui->si->audio->volume;
          *(sample + 1) *= Denemo.gui->si->audio->volume;
        }
    }
  return ret;
}

gboolean
open_source_audio (gchar * filename)
{
  SF_INFO sfinfo;
  DenemoAudio *temp;
  sfinfo.format = 0;

  
  //FIXME a better name for the mutex which originally was just for midi data, but will work for audio data too.
  if (Denemo.gui->si->audio && Denemo.gui->si->audio->sndfile)
    {
      temp = Denemo.gui->si->audio;
      g_static_mutex_lock (&smfmutex);
      Denemo.gui->si->audio = NULL;
      g_static_mutex_unlock (&smfmutex);
      sf_close (temp->sndfile);
      g_free (temp->filename);
      g_free (temp);

    }
  if (filename)
    {
      gpointer sndfile = sf_open (filename, SFM_READ, &sfinfo);
      if (sndfile)
        {
          temp = (DenemoAudio *) g_malloc (sizeof (DenemoAudio));
          temp->sndfile = sndfile;
          temp->filename = g_strdup (filename);
          temp->samplerate = sfinfo.samplerate;
          temp->channels = sfinfo.channels;
          temp->nframes = (int) sf_seek (temp->sndfile, -1, SEEK_END);
          g_print ("sndfile: %s sample rate is %d channels %d containing %d \n", 
                   sf_strerror (temp->sndfile), 
                   sfinfo.samplerate, 
                   sfinfo.channels, 
                   temp->nframes);
          
          
          temp->volume = 1.0;
          g_static_mutex_lock (&smfmutex);
          Denemo.gui->si->audio = temp;
          g_static_mutex_unlock (&smfmutex);
          update_leadin_widget (-1.0);
          if(sfinfo.channels != 2)
			warningdialog(_("Audio is not stereo - expect bad things!"));
          if(sfinfo.samplerate != 44100)
			warningdialog(_("Audio does not have 44100 sample rate: this could be bad"));
			//FIXME here generate a click track if the score is empty
		  if (Denemo.gui->si->smfsync != Denemo.gui->si->changecount)
			{
				exportmidi (NULL, Denemo.gui->si, 0, 0);//generate a timebase
			}
		  generate_note_onsets();
		  gtk_widget_queue_draw (Denemo.scorearea);
        }
    }
  Denemo.gui->si->audio ? gtk_widget_show (Denemo.audio_vol_control) : gtk_widget_hide (Denemo.audio_vol_control);
  return (Denemo.gui->si->audio != NULL);
}

gboolean
close_source_audio (void)
{
  gboolean ret = (Denemo.gui->si->audio != NULL);
  (void) open_source_audio (NULL);
  return ret;
}

void
rewind_audio (void)
{
  if (Denemo.gui->si->audio)
    {
      if (Denemo.gui->si->audio->sndfile == NULL)
        {
          gint leadin = Denemo.gui->si->audio->leadin;  /* not part of the audio file itself */
          open_source_audio (Denemo.gui->si->audio->filename);
          if (Denemo.gui->si->audio->samplerate)
            {
              Denemo.gui->si->audio->leadin = leadin;
              update_leadin_widget (((double) leadin) / Denemo.gui->si->audio->samplerate);
            }
        }
      gdouble start = get_start_time ();
      if (start < 0.0)
        start = 0.0;
      gint startframe = start * Denemo.gui->si->audio->samplerate;
      startframe += Denemo.gui->si->audio->leadin;
      if (startframe < 0)
        {
          leadin = -startframe;
          startframe = 0;
        }
      else
        leadin = 0;
      sf_seek (Denemo.gui->si->audio->sndfile, startframe, SEEK_SET);
    }
  else
    gtk_widget_hide (Denemo.audio_vol_control);
}

gboolean
set_lead_in (gdouble secs)
{
  if (Denemo.gui->si->audio)
    {
      if (Denemo.gui->si->audio->sndfile == NULL)
        open_source_audio (Denemo.gui->si->audio->filename);
      if (Denemo.gui->si->audio->sndfile)
        {
          Denemo.gui->si->audio->leadin = secs * Denemo.gui->si->audio->samplerate;
          return TRUE;
        }
    }
  return FALSE;
}




gboolean
audio_is_playing (void)
{
  return playing;
}



static gboolean annotating = FALSE;
static GQueue *timings = NULL;  //list of measure start times in microseconds from start, as indicated by the user.
static gint
record_timing (GtkWidget * widget, GdkEventKey * event)
{
  if (event->keyval == GDK_Escape)
    {
      call_out_to_guile ("(if (defined? 'DenemoAudioAnnotateFinished) (DenemoAudioAnnotateFinished))");
      stop_audio_playing ();
    }
  else
    {
      g_queue_push_tail (timings, GINT_TO_POINTER ((gint) (1000000 * get_playback_time ())));
      call_out_to_guile ("(DenemoAudioAnnotate)");
    }
  return TRUE;
}

gdouble
get_audio_timing (void)
{
  gdouble ret = -1.0;
  if (!g_queue_is_empty (timings))
    {
      ret = (GPOINTER_TO_INT (g_queue_pop_head (timings))) / 1000000.0;
    }
  return ret;
}

void
start_audio_playing (gboolean annotate)
{
  if (annotate)
    {
      annotating = TRUE;
      if (timings)
        g_queue_clear (timings);
      else
        timings = g_queue_new ();
      g_signal_connect (G_OBJECT (Denemo.scorearea), "key_press_event", G_CALLBACK (record_timing), NULL);
      g_signal_handlers_block_by_func (G_OBJECT (Denemo.scorearea), G_CALLBACK (scorearea_keypress_event), NULL);
      g_signal_handlers_block_by_func (G_OBJECT (Denemo.scorearea), G_CALLBACK (scorearea_button_press), NULL);
      g_signal_handlers_block_by_func (G_OBJECT (Denemo.scorearea), G_CALLBACK (scorearea_button_release), NULL);


    }
  rewind_audio ();

  initialize_until_time ();
  audio_play ();
  playing = TRUE;
}

void
stop_audio_playing (void)
{
  playing = FALSE;
  if (annotating)
    {
      annotating = FALSE;
      g_signal_handlers_disconnect_by_func (G_OBJECT (Denemo.scorearea), record_timing, NULL);
      g_signal_handlers_unblock_by_func (G_OBJECT (Denemo.scorearea), G_CALLBACK (scorearea_keypress_event), NULL);
      g_signal_handlers_unblock_by_func (G_OBJECT (Denemo.scorearea), G_CALLBACK (scorearea_button_press), NULL);
      g_signal_handlers_unblock_by_func (G_OBJECT (Denemo.scorearea), G_CALLBACK (scorearea_button_release), NULL);
    }
}

gboolean
open_source_audio_file (void)
{
  gboolean ret = FALSE;
  GtkWidget *dialog = gtk_file_chooser_dialog_new ("Open Audio Source File",
                                                   NULL,
                                                   GTK_FILE_CHOOSER_ACTION_OPEN,
                                                   GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                   GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                                   NULL);
  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
      char *filename;
      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
      gtk_widget_destroy (dialog);

      

      ret = open_source_audio (filename);
      g_free (filename);
      
      if(!ret)
		warningdialog(_("Could not load the audio file. Note only stereo with sample rate 44100 are supported at present. Use Audacity or similar to convert."));
    } else
	gtk_widget_destroy (dialog);
	      
	return ret;
}

