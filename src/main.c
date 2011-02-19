/* main.c
 * sets up the GUI and connects the main callback functions.
 *
 * for Denemo, a gtk+ frontend to GNU Lilypond
 * (c) 1999-2005 Matthew Hiller, Adam Tee
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <gtk/gtk.h>
#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif
#ifdef HAVE_WAIT_H
#include <wait.h>
#endif
#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#include "denemo/denemo.h"
#include "importxml.h"
#include <sys/types.h>
#include <dirent.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <libguile.h>
#include "view.h"
#include "exportxml.h"
#include "runsilent.h"
#include "utils.h"
#include "keyboard.h"
#ifdef _HAVE_FLUIDSYNTH_
#include "fluid.h"
#endif
#ifdef _HAVE_JACK_
#include "jackmidi.h"
#endif

struct DenemoRoot Denemo;

/* set strings for midi_audio_output */
const gchar *None = "None";
const gchar *Jack = "Jack";
const gchar *Portaudio = "Portaudio";
const gchar *Fluidsynth = "InternalSynth";


/* just a simple check, if the user has never run denemo before
   better, keep this for whole first session? */
gboolean first_time_user(void) {
  gchar *filename = g_build_filename(locatedotdenemo(), "actions", NULL);
  gboolean ret = !g_file_test (filename, G_FILE_TEST_EXISTS);
  g_free(filename);
  return ret;
}

gboolean uses_default_commandset(void) {
  gchar *filename = g_build_filename(locatedotdenemo(), "actions", "Default.commands", NULL);
  gboolean ret = !g_file_test (filename, G_FILE_TEST_EXISTS);
  g_free(filename);
  return ret;
}



static const GtkStockItem denemo_stock_items[] = {
  {"denemo-staccato", N_("Staccato"), (GdkModifierType) 0, 0, NULL},
  {"denemo-staccatissimo", N_("Staccatissimo"), (GdkModifierType) 0, 0, NULL},
  {"denemo-marcato", N_("Marcato"), (GdkModifierType) 0, 0, NULL},
  {"denemo-accent", N_("Accent"), (GdkModifierType) 0, 0, NULL},
  {"denemo-fermata", N_("Fermata"), (GdkModifierType) 0, 0, NULL},
  {"denemo-coda", N_("Coda"), (GdkModifierType) 0, 0, NULL},
  {"denemo-tenuto", N_("Tenuto"), (GdkModifierType) 0, 0, NULL},
  {"denemo-turn", N_("Turn"), (GdkModifierType) 0, 0, NULL},
  {"denemo-reverse-turn", N_("Reverse turn"), (GdkModifierType) 0, 0, NULL},
  {"denemo-trill", N_("Trill"), (GdkModifierType) 0, 0, NULL},
  {"denemo-mordent", N_("Mordent"), (GdkModifierType) 0, 0, NULL},
  {"denemo-up-bow", N_("Up bow"), (GdkModifierType) 0, 0, NULL},
  {"denemo-down-bow", N_("Down bow"), (GdkModifierType) 0, 0, NULL},
  {"denemo-rheel", N_("Right heel"), (GdkModifierType) 0, 0, NULL},
  {"denemo-lheel", N_("Left heel"), (GdkModifierType) 0, 0, NULL},
  {"denemo-ltoe", N_("Left toe"), (GdkModifierType) 0, 0, NULL},
  {"denemo-rtoe", N_("Right toe"), (GdkModifierType) 0, 0, NULL},
  {"denemo-whole-note", N_("Whole note"), (GdkModifierType) 0, 0, NULL},
  {"denemo-half-note", N_("Half note"), (GdkModifierType) 0, 0, NULL},
  {"denemo-quarter-note", N_("Quarter note"), (GdkModifierType) 0, 0, NULL},
  {"denemo-eight-note", N_("Eight note"), (GdkModifierType) 0, 0, NULL},
  {"denemo-sixteenth-note", N_("Sixteenth note"), (GdkModifierType) 0, 0,
   NULL},
  {"denemo-whole-rest", N_("Whole rest"), (GdkModifierType) 0, 0, NULL},
  {"denemo-half-rest", N_("Half rest"), (GdkModifierType) 0, 0, NULL},
  {"denemo-quarter-rest", N_("Quarter rest"), (GdkModifierType) 0, 0, NULL},
  {"denemo-eight-rest", N_("Eigth rest"), (GdkModifierType) 0, 0, NULL},
  {"denemo-sixteenth-rest", N_("Sixteenth rest"), (GdkModifierType) 0, 0,
   NULL},
  {"denemo-prall", N_("Prall"), (GdkModifierType) 0, 0, NULL},
  {"denemo-flageolet", N_("Flageolet"), (GdkModifierType) 0, 0, NULL},
  {"denemo-prallmordent", N_("PrallMordent"), (GdkModifierType) 0, 0, NULL},
  {"denemo-prallprall", N_("PrallPrall"), (GdkModifierType) 0, 0, NULL},
  {"denemo-open", N_("Open"), (GdkModifierType) 0, 0, NULL},
  {"denemo-segno", N_("Segno"), (GdkModifierType) 0, 0, NULL},
  {"denemo-stopped", N_("Stopped"), (GdkModifierType) 0, 0, NULL},
  {"denemo-thumb", N_("Thumb"), (GdkModifierType) 0, 0, NULL},
  {"denemo-upprall", N_("Upprall"), (GdkModifierType) 0, 0, NULL},
  {"denemo-arpeggio", N_("Arpeggio"), (GdkModifierType) 0, 0, NULL}
};

static void
register_stock_icon (GtkIconFactory * icon_factory, const gchar * stock_id,
                     const gchar * file)
{
  static gboolean warned;
  GtkIconSet *icon_set;
  GdkPixbuf *pixbuf;
  GError *error = NULL;
  gchar *path = g_build_filename (get_data_dir (), "pixmaps", file, NULL);

  g_debug ("path is %s\n", path);
  pixbuf = gdk_pixbuf_new_from_file (path, &error);
  if(!warned)
  if(error != NULL)
    {
      g_warning (_("Could not load specified pixbuf:\n%s\n"),
                 error->message);
      g_error_free (error);
      if(first_time_user())
	g_warning("some icons will not display properly, but program will run ok.");
      warned = TRUE;
    }
  if(pixbuf != NULL) {
    icon_set = gtk_icon_set_new_from_pixbuf (pixbuf);
    g_object_unref (pixbuf);
    gtk_icon_factory_add (icon_factory, stock_id, icon_set);
    g_free (path);
  } 
  //FIXME  path may leak
}

// removes the accel of a standard stock item. We use this because we want to
// handle all the keybindings in denemo's keymap.
// Also, removes the _ in the label of the accel so that no mnemonic is defined
static void
clean_stock_item(const gchar *stock_id)
{
    gint i, j;
    GtkStockItem stock;
    gchar *label;
    if (gtk_stock_lookup(stock_id, &stock)) {
        label = g_strdup(stock.label);
        if (stock.label != NULL) {
            i = 0;
            j = 0;
            while (stock.label[i]) {
                if (stock.label[i] == '_')
                    i++;
                else {
                    label[j] = stock.label[i];
                    i++;
                    j++;
                }
            }
            label[j] = '\0';
        }
        stock.label = label;
        stock.keyval = 0;
        stock.modifier = 0;
        gtk_stock_add(&stock, 1);
        g_free(label);
    }
}

static void
register_stock_items ()
{
  GtkIconFactory *icon_factory;

  /* Load stock items that denemo defines*/
  gtk_stock_add_static (denemo_stock_items,
                        G_N_ELEMENTS (denemo_stock_items));

  /* Load stock icons for the new stock items*/
  icon_factory = gtk_icon_factory_new ();
  gtk_icon_factory_add_default (icon_factory);
  register_stock_icon (icon_factory, "denemo-staccato", "staccato.svg");
  register_stock_icon (icon_factory, "denemo-staccatissimo",
		       "staccatissimo.svg");
  register_stock_icon (icon_factory, "denemo-marcato", "marcato.svg");
  register_stock_icon (icon_factory, "denemo-accent", "accent.svg");	 
  register_stock_icon (icon_factory, "denemo-fermata", "fermata.svg");
  register_stock_icon (icon_factory, "denemo-tenuto", "tenuto.svg");
  register_stock_icon (icon_factory, "denemo-turn", "turn.svg");
  register_stock_icon (icon_factory, "denemo-reverse-turn",
		       "reverse-turn.svg");	 
  register_stock_icon (icon_factory, "denemo-trill", "trill.svg");
  register_stock_icon (icon_factory, "denemo-mordent", "mordent.svg");
  register_stock_icon (icon_factory, "denemo-up-bow", "upbow.svg");
  register_stock_icon (icon_factory, "denemo-down-bow", "downbow.svg");
	 
  register_stock_icon (icon_factory, "denemo-rheel", "rheel.svg");
  register_stock_icon (icon_factory, "denemo-lheel", "lheel.svg");
  register_stock_icon (icon_factory, "denemo-rtoe", "rtoe.svg");
  register_stock_icon (icon_factory, "denemo-ltoe", "ltoe.svg");
	 
  register_stock_icon (icon_factory, "denemo-whole-note", "icon-note-0.svg");
  register_stock_icon (icon_factory, "denemo-half-note", "icon-note-1.svg");
  register_stock_icon (icon_factory, "denemo-quarter-note",
		       "icon-note-2.svg");
  register_stock_icon (icon_factory, "denemo-eight-note", "icon-note-3.svg");
  register_stock_icon (icon_factory, "denemo-sixteenth-note",
		       "icon-note-4.svg");	 
  register_stock_icon (icon_factory, "denemo-whole-rest", "icon-rest-0.svg");
  register_stock_icon (icon_factory, "denemo-half-rest", "icon-rest-1.svg");
  register_stock_icon (icon_factory, "denemo-quarter-rest",
		       "icon-rest-2.svg");
  register_stock_icon (icon_factory, "denemo-eight-rest", "icon-rest-3.svg");
  register_stock_icon (icon_factory, "denemo-sixteenth-rest",
		       "icon-rest-4.svg");

  //New Ornaments added here, loding XBM's until svgs have been generated.
  register_stock_icon (icon_factory, "denemo-coda",
                       "feta26-scripts-coda.xbm");
  register_stock_icon (icon_factory, "denemo-prall",
                       "feta26-scripts-prall.xbm");
  register_stock_icon (icon_factory, "denemo-flageolet",
                       "feta26-scripts-flageolet.xbm");
  register_stock_icon (icon_factory, "denemo-prallmordent",
                       "feta26-scripts-prallmordent.xbm");
  register_stock_icon (icon_factory, "denemo-prallprall",
                       "feta26-scripts-prallprall.xbm");
  register_stock_icon (icon_factory, "denemo-open",
                       "feta26-scripts-open.xbm");
  register_stock_icon (icon_factory, "denemo-segno",
                       "feta26-scripts-segno.xbm");
  register_stock_icon (icon_factory, "denemo-stopped",
                       "feta26-scripts-stopped.xbm");
  register_stock_icon (icon_factory, "denemo-thumb",
                       "feta26-scripts-thumb.xbm");
  register_stock_icon (icon_factory, "denemo-upprall",
                       "feta26-scripts-upprall.xbm");
  register_stock_icon (icon_factory, "denemo-arpeggio",
                       "feta26-scripts-arpeggio.xbm");

  //remove accelerators from some gtk standard stock items
  clean_stock_item(GTK_STOCK_NEW);
  clean_stock_item(GTK_STOCK_OPEN);
  clean_stock_item(GTK_STOCK_SAVE);
  clean_stock_item(GTK_STOCK_CLOSE);
  clean_stock_item(GTK_STOCK_QUIT);
  clean_stock_item(GTK_STOCK_CUT);
  clean_stock_item(GTK_STOCK_COPY);
  clean_stock_item(GTK_STOCK_PASTE);
  clean_stock_item(GTK_STOCK_GOTO_FIRST);
  clean_stock_item(GTK_STOCK_GOTO_LAST);
  clean_stock_item(GTK_STOCK_ADD);
  clean_stock_item(GTK_STOCK_REMOVE);
  clean_stock_item(GTK_STOCK_FIND);

  g_object_unref (icon_factory);
}

#ifdef HAVE_SIGCHLD
/* Code by Erik Mouw, taken directly from the gtk+ FAQ */

/**
 * signal handler to be invoked when child processes _exit() without
 * having to wait for them 
 */
static void
sigchld_handler (gint num)
{
  sigset_t set, oldset;
  pid_t pid;
  gint status, exitstatus;


  /* block other incoming SIGCHLD signals */
  sigemptyset (&set);
  sigaddset (&set, SIGCHLD);
  sigprocmask (SIG_BLOCK, &set, &oldset);

  /* wait for child */
  while ((pid = waitpid ((pid_t) - 1, &status, WNOHANG)) > 0)
    {
      if (WIFEXITED (status))
        {
          exitstatus = WEXITSTATUS (status);

          fprintf (stderr,
                   _("Parent: child exited, pid = %d, exit status = %d\n"),
                   (int) pid, exitstatus);
        }
      else if (WIFSIGNALED (status))
        {
          exitstatus = WTERMSIG (status);

          fprintf (stderr,
                   _("Parent: child terminated by signal %d, pid = %d\n"),
                   exitstatus, (int) pid);
        }
      else if (WIFSTOPPED (status))
        {
          exitstatus = WSTOPSIG (status);

          fprintf (stderr,
                   _("Parent: child stopped by signal %d, pid = %d\n"),
                   exitstatus, (int) pid);
        }
      else
        {
          fprintf (stderr,
                   _("Parent: child exited magically, pid = %d\n"),
                   (int) pid);
        }
    }

  /* re-install the signal handler (some systems need this) */
  signal (SIGCHLD, sigchld_handler);

  /* and unblock it */
  sigemptyset (&set);
  sigaddset (&set, SIGCHLD);
  sigprocmask (SIG_UNBLOCK, &set, &oldset);
}
#endif /* HAVE_SIGCHLD */

#if GTK_MAJOR_VERSION > 1
/**
 * Segmentation fault dialog warning the cannot continue
 *
 */
void
segdialog (gchar * sigtype, gchar * message)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                                   "%s : %s", sigtype, message);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}
#endif /* GTK_MAJOR_VERSION > 1 */

/**
 * SIGSEGV Handler to do nice things if denemo bombs
 *
 */
void
denemo_signal_handler (int sig)
{
  GList *tmp = NULL;
  DenemoGUI *gui;
  static int already_in_segfault = 0;
  if (already_in_segfault)
    exit (1);
  else
    already_in_segfault = 1;


  g_print ("\nNo of displays : %d\n", g_list_length (Denemo.guis));

  if (g_list_length (Denemo.guis) == 1)
    {
      gui = (DenemoGUI *) Denemo.guis->data;
      g_debug ("si is %p", gui);
      gchar *filename = g_build_filename(locatedotdenemo (), 
                                         "crashrecovery.denemo", NULL);
      gui->si->markstaffnum = 0;
      if (gui->si->lily_file)
        exportlilypond (filename, gui, TRUE);
      else
        exportXML (filename, gui, 0, 0);


    }
  else
    {
      int i = 0;
      for (tmp = Denemo.guis; tmp && g_list_length (tmp) > 1; tmp = tmp->next)
        {
          gui = (DenemoGUI *) tmp->data;
          gchar *filename = g_build_filename(locatedotdenemo (), 
                                             "crashrecovery", NULL);
          char t[5];
          sprintf (t, "%d", i);
          strncat (filename, t, strlen (t));
          strcat (filename, ".denemo");
	  gui->si->markstaffnum = 0;
          if (gui->si->lily_file)
            exportlilypond (filename, gui, TRUE);
          else
            exportXML (filename, gui, 0, 0);
          i++;
        }
    }

  exit (1);
}

/**
 * Handler used to print debug messages.
 */
void
debug_handler (const gchar *log_domain, GLogLevelFlags log_level,
               const gchar *message, gpointer user_data)
{
  //g_debug ("%s",message);
}





/**
 * Main function
 *
 */
int
main (int argc, char *argv[])
{

//#ifdef G_OS_WIN32
//  /* workaround necessary for compilation on Cygwin */
//  g_set_print_handler ((GPrintFunc)printf);
//#endif
  
   /* set the default handler for debug messages */
  //FIXME this does not work
  g_log_set_handler (NULL, G_LOG_LEVEL_DEBUG, debug_handler, NULL);


  /* initialization of directory relocatability */
  initdir();
#ifdef G_OS_WIN32
  gchar *prefix = g_win32_get_package_installation_directory (NULL, NULL);
  gchar *guile = g_build_filename (prefix, "share", "guile", NULL);
  gchar *guile_1_8 = g_build_filename (guile, "1.8", NULL);
  gchar *lilypond_current_scm = g_build_filename (prefix, "share", "lilypond", "current", "scm", NULL);
  if (g_file_test (guile, G_FILE_TEST_EXISTS))
    {
      gchar *guile_path = g_strconcat (guile, ";", guile_1_8, ";", lilypond_current_scm, NULL);
      g_setenv ("GUILE_LOAD_PATH", guile_path, TRUE);//FIXME TRUE means we overwrite any installed version of lilyponds scm, FALSE risks not putting denemos scm in the path...
      g_print ("Setting GUILE_LOAD_PATH=%s\n", guile_path);
    }
  else
    warningdialog ("You may need to set GUILE_LOAD_PATH to the directory where you have ice9 installed\n");
  g_setenv ("PANGO_PREFIX", prefix, TRUE);
  g_setenv ("PANGO_MODULE_VERSION", "1.6.0", TRUE);
  g_setenv ("PANGO_SO_EXTENSION", ".dll", TRUE);
  g_print ("Setting PANGO_PREFIX=%s\n", prefix);

  g_setenv ("GTK_MODULE_VERSION", "2.10.0", TRUE);
  g_setenv ("GTK_SO_EXTENSION", ".dll", TRUE);
  g_setenv ("GTK_PREFIX", prefix, TRUE);
  g_print ("Setting GTK_PREFIX=%s\n", prefix);

  gchar *fc_path = g_build_filename (prefix, "etc","fonts", NULL);
  g_setenv ("FONTCONFIG_PATH", fc_path, TRUE);
  g_print ("Setting FONTCONFIG_PATH=%s\n", fc_path);
  gchar *fc_file = g_build_filename (fc_path, "fonts.conf", NULL);
  g_setenv ("FONTCONFIG_FILE", fc_file, TRUE);
  g_print ("Setting FONTCONFIG_FILE=%s\n", fc_file);


  gchar *program_files =  g_getenv("PROGRAMFILES");
  gchar *path = g_getenv ("PATH");
  gchar *lilypond_path = g_build_filename(prefix, "bin", NULL);
  gchar *lib_path = g_build_filename(prefix, "lib", NULL);
  path = g_strconcat (path,";", lilypond_path, ";", lib_path, NULL);

  g_setenv ("PATH", path, TRUE);
  g_print("PATH set to %s\n", path);
  gchar *lilypond_data_path = g_build_filename (prefix, "share", "lilypond", "current", NULL);
  g_setenv ("LILYPOND_DATA_PATH", lilypond_data_path, FALSE);
  g_print("LILYPOND_DATA_PATH will be %s if not already set", lilypond_data_path);
  gchar *fontpath = g_build_filename (prefix, "share", "fonts", "truetype","denemo", "fetta.ttf", NULL);
  g_setenv ("LILYPOND_VERBOSE", "1", FALSE);
  add_font_directory(fontpath);
  fontpath = g_build_filename (prefix, "share", "fonts", "truetype","denemo", "denemo.ttf", NULL);
  add_font_directory(fontpath);
#else
  add_font_directory (DATAROOTDIR "/fonts");
#endif
  GError *error = NULL;
  /* gtk initialization */
  gtk_init (&argc, &argv);

  /* locale initialization */
  //setlocale (LC_CTYPE, "");
  //setlocale (LC_MESSAGES, "");
  setlocale (LC_ALL, "");
  //gtk_set_locale ();
  bindtextdomain (PACKAGE, get_locale_dir ());
  bind_textdomain_codeset (PACKAGE, "UTF-8");
  textdomain (PACKAGE);

  register_stock_items ();


  //g_print("Calling scm boot guile with %d and %p\n", argc, argv);
  scm_boot_guile (argc, argv, inner_main, NULL);
  
  return 0;
}

gchar * process_command_line(int argc, char**argv) {

  gint opts;
  GDir *dir=NULL;
  gchar *filename;
  GError *error = NULL;
  gchar *commandsetfile=NULL;
  /* parse command line and display help messages */
  gchar *helptext  = g_strconcat (_("\nGNU Denemo version "), VERSION, ".\n\n",
                                 _("\
Usage: denemo [OPTION]... [FILE]\n\n\
Run denemo, optionally starting with FILE\n\n\
Denemo is a graphical music notation editor.\n\
It uses GNU Lilypond for music typesetting\n\
Denemo is part of the GNU project.\n\n\
Options:\n\
  -h,--help             print this help and exit\n\
  -c file               use commandset found in system file\n\
  -k file               use commandset found in local file (in ~/.denemo)\n\
  -i pathtofile         process scheme commands in pathtofile on startup\n\
  -s filename           process scheme commands from system file\n\
  -v,--version          print version number and exit\n\n\n\
Report bugs to bug-denemo@gnu.org\n"), NULL) ;

  gchar *copytext = _("(c) 1999-2005, 2009 Matthew Hiller, Adam Tee, and others\n\n\n"
"This program is provided with absolutely NO WARRANTY; see\n"
"the file COPYING for details.\n\n"
"This software may be redistributed and modified under the\n"
"terms of the GNU General Public License; again, see the file\n"
"COPYING for details.\n\n");


#ifdef HAVE_GETOPT_H
  static struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'}
  };
#endif

#ifdef HAVE_GETOPT_H
  while ((opts = getopt_long (argc, argv, "s:hi:vc:k:", long_options, NULL)) != -1)
#else
  while ((opts = getopt (argc, argv, "s:hi:vc:k:")) != -1)
#endif
    {
	  g_print("opt %c has %s\n", opts, argv[optind]);
      if (opts == 'h')
        {
          g_print ("%s", helptext);
          exit (0);
        }
      else if (opts == 's')
        {
	  Denemo.schemeinit = g_build_filename(get_data_dir(), "actions",  optarg, NULL);
        }
      else if (opts == 'i')
        {
          Denemo.schemeinit = g_strdup(optarg);
        }

      else if (opts == 'c')
        {
	  commandsetfile = g_build_filename(get_data_dir(), "actions",  optarg, NULL);
        }
      else if (opts == 'k')
        {
	  commandsetfile = g_build_filename(locatedotdenemo(), "actions",  optarg, NULL);
        }
      else if (opts == 'v')
        {
          g_print (_("\nGNU Denemo version "));
          g_print (VERSION ".\n\n");
          g_print ("%s", copytext);
          exit (0);
        }
    }

  g_print (_("\nGNU Denemo, a gtk+ frontend for GNU Lilypond\n"));
  g_print ("%s", copytext);

  g_free (helptext);


  /* Set up the signal handler */
  signal (SIGSEGV, denemo_signal_handler);
#ifdef HAVE_SIGCHLD
  signal (SIGCHLD, sigchld_handler);
#endif


    if (optind < argc)
      return argv[optind];
    else
      return NULL;


}
