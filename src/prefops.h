/* prefops.h
 * header file for initializing preferences
 *
 * for Denemo, a gtk+ frontend to GNU Lilypond
 * (c) 1999-2005 Matthew Hiller
 */
#ifndef PREFOPSH
#define PREFOPSH

#include <denemo/denemo.h>
#include "plugin.h"

#define INITIAL_WIDTH 1000
#define INITIAL_HEIGHT 500

const gchar *locatedotdenemo ();

void initprefs (void);
GList* get_plugins_list(GList *plugins);
gint writeXMLPrefs( DenemoPrefs *prefs);
void writeHistory(void);
gint readHistory(void);

#endif
