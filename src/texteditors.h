/* texteditors.h
 *  
 * (c)   2009 Richard Shann 
 */

#ifndef TEXTEDITORS_H

#define TEXTEDITORS_H

#include <denemo/denemo.h>
void executeScript (void);
void create_scheme_window (void);
gchar *getSchemeText (void);
void deleteSchemeText (void);
void appendSchemeText (gchar * text);
gint getNumCharsSchemeText (void);

#endif
