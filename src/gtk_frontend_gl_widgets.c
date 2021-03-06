/*
 *      gtk_frontend_gl_widgets.c
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


#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "data_structures_init.h"
#include "gtk_frontend.h"
#include "gtk_callbacks.h"

/*
#include "gtk_callbacks.h"
*/
#include "glarea_callbacks.h"
/*
#include "gtk_frontend_widgets.h"
#include "gtk_frontend_gl_widgets.h"
*/



static GtkWidget *gtkglext_context_widget (GdkGLConfig *glconfig);



extern GdkGLConfig *glconfig;               // from gl_config.h
gpointer gl_area_main;
 




//~ --------------------------------------------------------------------------------------------------------------------
//~ application main gtkglext context widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *main_gtkglext_context_widget () {

    GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
    GtkWidget *drawing_area = gtkglext_context_widget (glconfig);
    gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

    return vbox;
}
 
   
//~ --------------------------------------------------------------------------------------------------------------------
//~ gtkglext_context_widget
//~ --------------------------------------------------------------------------------------------------------------------

static GtkWidget *gtkglext_context_widget (GdkGLConfig *glconfig) {

    GtkWidget *drawing_area = gtk_drawing_area_new ();

    gl_area_main = g_object_ref (drawing_area);     // adds a reference to drawing_area called: (gpointer) gl_area

/*
    gtk_widget_set_size_request (GTK_WIDGET (drawing_area), config->graph_width, config->graph_height);
*/

    //gtk_widget_set_size_request (drawing_area, 640, 480);
    gtk_widget_set_size_request (drawing_area, 480, 480);

    gtk_widget_set_gl_capability (drawing_area, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE);

    gtk_widget_add_events (drawing_area,
                             GDK_BUTTON1_MOTION_MASK    |
                             GDK_BUTTON2_MOTION_MASK    |
                             GDK_BUTTON_PRESS_MASK      |
                             GDK_BUTTON_RELEASE_MASK    |
                             GDK_POINTER_MOTION_MASK    |
                             GDK_VISIBILITY_NOTIFY_MASK);
/*
    gtk_widget_add_events (gl_area_main, GDK_SCROLL_MASK);
*/ 

   
    //     g_signal_connect (G_OBJECT (gl_area_main), "scroll-event", G_CALLBACK (cb_chgval_glulookat_mouse), GINT_TO_POINTER (1));
    g_signal_connect_after (G_OBJECT (drawing_area), "realize",
                                                G_CALLBACK (realize_main_gldisplay), (gpointer) displaydata);
    g_signal_connect (G_OBJECT (drawing_area), "configure_event",
                                                G_CALLBACK (configure_main_gldisplay), NULL);
    g_signal_connect (G_OBJECT (drawing_area), "expose_event",
                                                G_CALLBACK (expose_main_gldisplay), (gpointer) displaydata);

    g_signal_connect (G_OBJECT (drawing_area), "button_press_event",
                                                G_CALLBACK (button_press_main_gldisplay), (gpointer) displaydata);
 
    g_signal_connect (G_OBJECT (drawing_area), "button_release_event",
                                                G_CALLBACK (button_release_main_gldisplay), (gpointer) displaydata);
    g_signal_connect (G_OBJECT (drawing_area), "motion_notify_event",
                                                G_CALLBACK (motion_notify_main_gldisplay), (gpointer) displaydata);
 
    g_signal_connect (G_OBJECT (drawing_area), "map_event",
                                                G_CALLBACK (cb_map_event), (gpointer) displaydata);
    g_signal_connect (G_OBJECT (drawing_area), "unmap_event",
                                                G_CALLBACK (cb_unmap_event), (gpointer) displaydata);
    g_signal_connect (G_OBJECT (drawing_area), "visibility_notify_event",
                                                G_CALLBACK (cb_visibility_notify_event), (gpointer) displaydata);
 
    return drawing_area;
 
}
  


 
