/*
 *      gtk_frontend.c
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
#include "gtk_frontend.h"
#include "gtk_frontend_widgets.h"
#include "gtk_frontend_gl_widgets.h"
#include "gtk_callbacks.h"


frontend_widgets *UI;


/*
 * gtk frontend source file
 */

/*
 * gl configuration piece of code was grabbed from Simple.c
 * written by Naofumi Yasufuku  <naofumi@users.sourceforge.net>
 *
 * sierpinski algorithm: Lode's Computer Graphics Tutorial
 *
 */




//~ --------------------------------------------------------------------------------------------------------------------
//~ main window widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *append_main_window (const gchar *title) {

/*
    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW      (DEBUG_GTK, "append_main_window", "creating main window")
    DEBUG_LOG_STRING    (DEBUG_GTK, " ", "title", title)
    #endif
*/

 
    //~ ---------------------
    //~ window init
    //~ ---------------------
    GtkWidget *window                       = gtk_window_new (GTK_WINDOW_TOPLEVEL);
/*
    GtkWidget *parent                       = gtk_window_get_transient_for ((GtkWindow *) window);
    gtk_window_set_transient_for (window, parent);
*/

    gtk_window_set_default_size (GTK_WINDOW (window), UI->window_size_x, UI->window_size_y);
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_app_close), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (cb_app_close), NULL);
    gtk_window_set_title (GTK_WINDOW (window), title);
    gtk_container_set_border_width (GTK_CONTAINER (window), 1);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_NONE);
 

    //~ ---------------------
    //~ widgets init
    //~ ---------------------
    GtkWidget *window_interior              = gtk_vbox_new (FALSE, 0);
    GtkWidget *window_interior_side         = gtk_hbox_new (FALSE, 0);
    GtkWidget *main_menu                    = main_window_menu ();
    GtkWidget *toolbar                      = main_window_toolbar ();
    GtkWidget *settings_widget              = main_window_settings_widget ();
    GtkWidget *toolbar_aux                  = main_window_toolbar_aux ();
    // main GL widget
    GtkWidget *gtkglext_context_widget      = main_gtkglext_context_widget ();

 
    //~ ---------------------
    //~ inside window
    //~ ---------------------
    gtk_container_add (GTK_CONTAINER (window), window_interior);
    gtk_box_pack_start (GTK_BOX (window_interior), main_menu, FALSE, FALSE, 2);
    gtk_box_pack_start (GTK_BOX (window_interior), toolbar, FALSE, FALSE, 0);

    //~ ---------------------
    //~ main GL display area:
    //~ ---------------------
    gtk_box_pack_start (GTK_BOX (window_interior), window_interior_side, FALSE, FALSE, 10);
    gtk_box_pack_start (GTK_BOX (window_interior_side), gtkglext_context_widget, TRUE, TRUE, 0);
    gtk_widget_set_size_request (GTK_WIDGET (gtkglext_context_widget), -1, -1);

    //~ ---------------------
    //~ auxiliary toolbar
    //~ ---------------------
    // should have button for hiding beneath widget
    gtk_box_pack_start (GTK_BOX (window_interior), toolbar_aux, FALSE, FALSE, 0);

    //~ ---------------------
    //~ settings widget
    //~ ---------------------
    gtk_box_pack_start (GTK_BOX (window_interior_side), settings_widget, FALSE, FALSE, 0);


    //~ ---------------------
    //~ status bar
    //~ ---------------------
    GtkWidget *status_bar = gtk_statusbar_new ();
    gtk_box_pack_end (GTK_BOX (window_interior), status_bar, FALSE, FALSE, 0);

/*
    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW      (DEBUG_GTK, "append_main_window", "main window attached")
    #endif
*/

    return window;
}



