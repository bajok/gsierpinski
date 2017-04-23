/*
 *      glarea_callbacks.h
 *      
 *      Copyright 2009 Przemysław Dużyk <przemyslaw.duzyk@gmail.com>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */


#ifndef __glarea_callbacks_h_
#define __glarea_callbacks_h_


#include "structures_glgraph.h"

 
// remove not necessary functions from header


void redisplay_glgraph (gpointer drawing_area, gpointer data);
void redisplay_sierpinski (gpointer drawing_area);


gboolean expose_main_glgraph (GtkWidget *widget, GdkEventExpose *event, gpointer data);
void realize_main_glgraph (GtkWidget *widget, gpointer data);
gboolean configure_main_glgraph (GtkWidget *widget, GdkEventConfigure *event, gpointer data);

gboolean expose_event_sierpinski (GtkWidget *widget, GdkEventExpose *event, gpointer data);
void realize_sierpinski (GtkWidget *widget, gpointer data);
gboolean configure_event_sierpinski (GtkWidget *widget, GdkEventConfigure *event, gpointer data);



#endif // __glarea_callbacks_h_
