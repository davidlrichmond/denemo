/*
 * jackutil.h
 * JACK utility functions.
 *
 * for Denemo, a gtk+ frontend to GNU Lilypond
 * Copyright (C) 2011  Dominic Sacré
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef JACKUTIL_H
#define JACKUTIL_H

#include <glib.h>

/**
 * Returns a list of available JACK port names, that is, ports to which our
 * own input/output ports can be connected.
 *
 * If the JACK server is not running or there are no available ports, this
 * function returns NULL.
 *
 * @param midi    if TRUE returns MIDI ports, otherwise audio ports.
 * @param output  if TRUE returns output ports, otherwise input ports.
 */
GList *get_jack_ports (gboolean midi, gboolean output);

/**
 * Frees a list returned by get_jack_ports()
 */
void free_jack_ports (GList * list);


#endif // JACKUTIL_H
