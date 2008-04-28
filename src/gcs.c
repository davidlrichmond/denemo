/* gcs.cpp
 * gc creator functions
 *
 * for Denemo, a gtk+ frontend to GNU Lilypond
 * (c) 1999-2005  Matthew Hiller,  Adam Tee
 */

#include <gdk/gdk.h>

/**
 * helper function to generate the graphics contexts 
 * that denemo uses
 */
GdkGC *
colorhelper (GdkWindow * window, gchar * fgcolor, gchar * bgcolor)
{
  GdkColor thecolor;
  GdkGC *ret;

  gdk_color_parse (fgcolor, &thecolor);
  gdk_colormap_alloc_color (gdk_colormap_get_system (),
			    &thecolor, TRUE, TRUE);
  ret = gdk_gc_new (window);
  gdk_gc_set_foreground (ret, &thecolor);

  if (bgcolor)
    {
      gdk_color_parse (bgcolor, &thecolor);
      gdk_colormap_alloc_color (gdk_colormap_get_system (),
				&thecolor, TRUE, TRUE);
      gdk_gc_set_background (ret, &thecolor);
    }
  return ret;
}

GdkGC *blackgc;
GdkGC *graygc;
GdkGC *slategraygc;
GdkGC *greengc;
GdkGC *redgc;
GdkGC *bluegc;
GdkGC *purplegc;
GdkGC *yellowgc;

#define autocolor(color) color##gc = colorhelper (window, #color, "white")

/**
 * Initialise the graphics contexts that denemo uses
 *
 */
void
gcs_init (GdkWindow * window)
{
  autocolor (black);
  autocolor (gray);
  autocolor (slategray);
  autocolor (green);
  autocolor (red);
  autocolor (blue);
  autocolor (purple);
  autocolor (yellow);
}

/**
 * Get the black graphics context
 */
GdkGC *
gcs_blackgc ()
{
  return blackgc;
}

/**
 * Get the gray graphics context
 */
GdkGC *
gcs_graygc ()
{
  return graygc;
}

/**
 * Get the dark gray graphics context
 */
GdkGC *
gcs_slategraygc ()
{
  return slategraygc;
}

/**
 * Get the green graphics context
 */
GdkGC *
gcs_greengc ()
{
  return greengc;
}

/**
 * Get the red graphics context
 */
GdkGC *
gcs_redgc ()
{
  return redgc;
}

/**
 * Get the blue graphics context
 */
GdkGC *
gcs_bluegc ()
{
  return bluegc;
}

/**
 * Get the purple graphics context
 */
GdkGC *
gcs_purplegc ()
{
  return purplegc;
}

/**
 * Get the yellow graphics context
 */
GdkGC *
gcs_yellowgc ()
{
  return yellowgc;
}
