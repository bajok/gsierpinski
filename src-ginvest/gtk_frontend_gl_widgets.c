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
#include "glarea_callbacks.h"





#include "gtk_frontend_widgets.h"
#include "gtk_frontend_gl_widgets.h"



static GtkWidget *gtkglext_context_widget (GdkGLConfig *glconfig);



extern GdkGLConfig *glconfig;               // from gl_config.h
gpointer gl_area_main, gl_area_sierpinski;



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

    //     gtk_widget_set_size_request (drawing_area, 640, 480);

    gtk_widget_set_gl_capability (drawing_area, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE);
    gtk_widget_add_events (gl_area_main, GDK_SCROLL_MASK);

    //     g_signal_connect (G_OBJECT (gl_area_main), "scroll-event", G_CALLBACK (cb_chgval_glulookat_mouse), GINT_TO_POINTER (1));
    g_signal_connect (G_OBJECT (gl_area_main), "realize", G_CALLBACK (realize_main_glgraph), displaydata);
    g_signal_connect (G_OBJECT (gl_area_main), "configure_event", G_CALLBACK (configure_main_glgraph), NULL);
    g_signal_connect (G_OBJECT (gl_area_main), "expose_event", G_CALLBACK (expose_main_glgraph), displaydata);
 
    return drawing_area;
}
  
 
//~ --------------------------------------------------------------------------------------------------------------------
//~ main_about_window
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *main_about_window (GdkGLConfig *glconfig) {

    GtkWidget *window_interior;
    GtkWidget *window =                     gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size (GTK_WINDOW (window), -1, -1);
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (widget_destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (widget_destroy), NULL);
    gtk_window_set_title (GTK_WINDOW (window), "about");
    gtk_container_set_border_width (GTK_CONTAINER (window), 1);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

    window_interior = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), window_interior);                 // packing main container inside window

    GtkWidget *hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window_interior), hbox);

    // sierpinski widget
    GtkWidget *drawing_area = drawing_area = gtk_drawing_area_new ();
    GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (hbox), vbox);

    gl_area_sierpinski = g_object_ref (drawing_area);     // adds a reference to drawing_area called: (gpointer) gl_area
    gtk_widget_set_size_request (GTK_WIDGET (drawing_area), 320, 240);

    gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

    gtk_widget_set_gl_capability (drawing_area, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE);
    //~ gtk_widget_add_events (gl_area_sierpinski, GDK_SCROLL_MASK);

    g_signal_connect (G_OBJECT (gl_area_sierpinski), "realize", G_CALLBACK (realize_sierpinski), NULL);
    g_signal_connect (G_OBJECT (gl_area_sierpinski), "configure_event", G_CALLBACK (configure_event_sierpinski), NULL);
    g_signal_connect (G_OBJECT (gl_area_sierpinski), "expose_event", G_CALLBACK (expose_event_sierpinski), NULL);



    GtkWidget *frame = gtk_frame_new ("gl");
    hbox = gtk_hbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window_interior), frame);
    gtk_container_add (GTK_CONTAINER (frame), hbox);

    GtkWidget *scale_adj;
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);

    scale_adj = create_scale_adjustment ("eyeX", -300.0,300.0, 0.01, sierp_gl_LookAt [0][0],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (1));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);
    scale_adj = create_scale_adjustment ("eyeY", -300.0,300.0, 0.01, sierp_gl_LookAt [0][1],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (2));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);
    scale_adj = create_scale_adjustment ("eyeZ", -300.0,300.0, 0.01, sierp_gl_LookAt [0][2],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (3));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
    scale_adj = create_scale_adjustment ("centerX", -2.0, 2.0, 0.01, sierp_gl_LookAt [1][0],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (4));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);
    scale_adj = create_scale_adjustment ("centerY", -3.0, 3.0, 0.01, sierp_gl_LookAt [1][1],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (5));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);
    scale_adj = create_scale_adjustment ("centerZ", -3.0, 3.0, 0.01, sierp_gl_LookAt [1][2],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (6));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
    scale_adj = create_scale_adjustment ("upX", -2.0, 2.0, 0.01, sierp_gl_LookAt [2][0],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (7));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);
    scale_adj = create_scale_adjustment ("upY", -3.0, 3.0, 0.01, sierp_gl_LookAt [2][1],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (8));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);
    scale_adj = create_scale_adjustment ("upZ", -3.0, 3.0, 0.01, sierp_gl_LookAt [2][2],
                                         TRUE, cb_chgval_sierp_gl_LookAt, GINT_TO_POINTER (9));
    gtk_box_pack_start (GTK_BOX (vbox), scale_adj, TRUE, FALSE, 0);


    return window;
}


