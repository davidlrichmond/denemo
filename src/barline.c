/* barline.cpp
 * Basic barlines
 * Not Functioning
 * 
 * for Denemo , a gtk+ frontend to GNU Lilypond
 * (c) 2002-2005 Adam Tee
 */
#include "barline.h"
#include "calculatepositions.h"
#include "commandfuncs.h"
#include "staffops.h"
#include <stdio.h>

/**
 * Textual description of barlines
 */
static gchar *string_barlines[6] = { "Ordinary", "Double",
  "End", "Open Repeat", "Close Repeat", "Open/Close Repeat"
};

struct callbackdata
{
  DenemoGUI *gui;
  GtkWidget *combo;
};

/**
 * Get barline type form string 
 * @param thetext textual description of the barline 
 * @return the numerical representation of the barline
 */
enum barline_type
barlinefromname (gchar * thetext)
{

  if (g_strcasecmp (thetext, _("Ordinary")) == 0)
    return ORDINARY_BARLINE;
  else if (g_strcasecmp (thetext, _("Double")) == 0)
    return DOUBLE_BARLINE;
  else if (g_strcasecmp (thetext, _("End")) == 0)
    return END_BARLINE;
  else if (g_strcasecmp (thetext, _("Open Repeat")) == 0)
    return OPENREPEAT_BARLINE;
  else if (g_strcasecmp (thetext, _("Close Repeat")) == 0)
    return CLOSE_REPEAT;
  else if (g_strcasecmp (thetext, _("Double")) == 0)
    return OPEN_CLOSE_REPEAT;
  else
    return ORDINARY_BARLINE;

}


/**
 * Dialog for inserting the barlines
 * @param action the gtk action emitted by the menu item
 * @param gui the DenemoGUI structure
 * @return none
 */
void
insert_barline (GtkAction * action, DenemoGUI * gui)
{
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *combobox;
  GtkWidget *okbutton;
  GtkWidget *cancelbutton;
  GList *list = NULL;
  static struct callbackdata cbdata;

  int i = 0;

  dialog = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog), _("Insert Barline"));

  label = gtk_label_new (_("Select desired barline"));
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox),
		      label, TRUE, TRUE, 0);
  gtk_widget_show (label);

  for (i = 0; i < 6; i++)
    list = g_list_append (list, string_barlines[i]);

  combobox = gtk_combo_new ();
  gtk_combo_set_popdown_strings (GTK_COMBO (combobox), list);

  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox),
		      combobox, TRUE, TRUE, 0);
  gtk_widget_show (combobox);

  okbutton = gtk_button_new_with_label (_("OK"));
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->action_area),
		      okbutton, TRUE, TRUE, 0);

  cbdata.gui = gui;
  cbdata.combo = combobox;
  /* Signal connection */
  gtk_signal_connect (GTK_OBJECT (okbutton), "clicked",
		      GTK_SIGNAL_FUNC (add_barline), &cbdata);
  gtk_signal_connect_object (GTK_OBJECT (okbutton), "clicked",
			     GTK_SIGNAL_FUNC (gtk_widget_destroy),
			     GTK_OBJECT (dialog));

  gtk_widget_show (okbutton);

  cancelbutton = gtk_button_new_with_label (_("Cancel"));
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->action_area),
		      cancelbutton, TRUE, TRUE, 0);
  /* Signal connection */
  gtk_signal_connect_object (GTK_OBJECT (cancelbutton), "clicked",
			     GTK_SIGNAL_FUNC (gtk_widget_destroy),
			     GTK_OBJECT (dialog));

  gtk_widget_show (cancelbutton);

  gtk_widget_grab_focus (combobox);
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_MOUSE);
  gtk_widget_show (dialog);

  /*printf("In barline\n"); */

}

/**
 * Add Barline into the score
 * @param widget widget associated with the callback
 * @param data a pointer to the scoreinfo structure
 * @return none
 */
void
add_barline (GtkWidget * widget, gpointer data)
{
  struct callbackdata *cbdata = (struct callbackdata *) data;
  DenemoScore *si = cbdata->gui->si;

  gchar *thetext =
    (gchar *)
    gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (cbdata->combo)->entry));

  object_insert (cbdata->gui, newbarline (barlinefromname (thetext)));

}

/**
 * Create new barline  
 * @param bartype	numeric representation of the barline
 * @return the new barline
 */
DenemoObject *
newbarline (enum barline_type bartype)
{
  DenemoObject *newobj;
  barline *obj = (barline *) g_malloc (sizeof (barline));
  newobj = (DenemoObject *) g_malloc (sizeof (DenemoObject));
  newobj->type = BARLINE;
  newobj->isinvisible = FALSE;
  obj->type = bartype;
  newobj->object = obj;
  return newobj;
}
