/* staffops.h
 * Header file for functions dealing with whole staffs

 * for Denemo, a gtk+ frontend to GNU Lilypond
 * (c) 1999-2005 Matthew Hiller */


#ifndef __STAFFOPS_H__
#define __STAFFOPS_H__
#include <denemo/denemo.h>

enum newstaffcallbackaction
  { INITIAL, FIRST, LAST, ADDFROMLOAD, BEFORE, AFTER, CURRENT,
  NEWVOICE,LYRICSTAFF, FIGURESTAFF, CHORDSTAFF
};

struct newstaffinfotopass {
  DenemoScore *si;
  DenemoStaff *staff;
  guint addat;
};

objnode *firstobjnode (measurenode *mnode);

objnode *lastobjnode (measurenode *mnode);

measurenode *firstmeasurenode (staffnode *thestaff);

measurenode *
nth_measure_node_in_staff (staffnode *thestaff, gint n);

objnode *firstobjnodeinstaff (staffnode *thestaff);

//void initkeysig (gint *accs, gint number);

void setcurrentprimarystaff (DenemoScore *si);

void newstaff (DenemoScore *si, enum newstaffcallbackaction action, DenemoContext context); /* default context shall be DENEMO_NONE */

gboolean deletestaff (DenemoScore *si);

void beamsandstemdirswholestaff (DenemoStaff *thestaff);

void showwhichaccidentalswholestaff (DenemoStaff *thestaff);

void fixnoteheights (DenemoStaff *thestaff);

void newstaffinitial(GtkAction *action, DenemoGUI *gui);

void newstaffbefore(GtkAction *action, DenemoGUI *gui);

void dnm_newstaffafter(GtkAction *action, DenemoGUI *gui);

void newstafflyric(GtkAction *action, DenemoGUI *gui);

void dnm_newstafffigured(GtkAction *action, DenemoGUI *gui);

void dnm_newstaffchords(GtkAction *action, DenemoGUI *gui);

void dnm_newstaffvoice(GtkAction *action, DenemoGUI *gui);

void newstafflast(GtkAction *action, DenemoGUI *gui);

#endif /* __STAFFOPS_H__ */
