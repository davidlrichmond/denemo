/* objops.h
 * header file for operations to objects
 *
 * for Denemo, a gtk+ frontend to GNU Lilypond
 * (c) 1999-2005 Matthew Hiller
 */
#ifndef OBJOPS_H
#define OBJOPS_H 

#include <denemo/denemo.h>

void
freeobject (DenemoObject *mudobj);

//void
//initkeyaccs (gint *accs, gint number);

//void dnm_setinitialkeysig (DenemoStaff * curstaff, gint tokey, gint type);
	
DenemoObject *
newmeasurebreakobject ();

DenemoObject *
newstaffbreakobject ();

DenemoObject *
lily_directive_new (gchar* type);

DenemoObject *
dynamic_new (gchar *type);

#endif
