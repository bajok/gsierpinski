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


#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "gldisplay.h"

 
// remove not necessary functions from header


void redisplay_gldisplay (gpointer drawing_area, gpointer data, gpointer params);
/*
void redisplay_sierpinski (gpointer drawing_area);
*/


void     realize_main_gldisplay         (GtkWidget *widget, gpointer data);
gboolean expose_main_gldisplay          (GtkWidget *widget, GdkEventExpose *event, gpointer data);
gboolean configure_main_gldisplay       (GtkWidget *widget, GdkEventConfigure *event, gpointer data);
gboolean button_press_main_gldisplay    (GtkWidget *widget, GdkEventButton *event, gpointer data);
gboolean button_release_main_gldisplay  (GtkWidget *widget, GdkEventButton *event, gpointer data);
gboolean motion_notify_main_gldisplay   (GtkWidget *widget, GdkEventMotion *event, gpointer data);


 


#endif // __glarea_callbacks_h_
