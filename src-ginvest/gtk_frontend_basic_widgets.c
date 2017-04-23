/*
 *      gtk_frontend_basic_widgets.c
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

/*
#include <GL/gl.h>
#include <GL/glu.h>
*/





//~ --------------------------------------------------------------------------------------------------------------------
//~ other widgets
//~ --------------------------------------------------------------------------------------------------------------------

/*
GtkWidget *create_child_window_widget (const char *name, GtkWidget *widget, void callback (), gpointer data) {


    GtkWidget *window                       = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *window_interior              = gtk_vbox_new (FALSE, 0);
    GtkWidget *main_menu                    = app_main_window_menu ();
    GtkWidget *toolbar                      = app_main_window_toolbar ();

    gtk_window_set_default_size (GTK_WINDOW (window), config->window_size_x, config->window_size_y);

    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_app_close), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (cb_app_close), NULL);
    gtk_window_set_title (GTK_WINDOW (window), name);
    gtk_container_set_border_width (GTK_CONTAINER (window), 1);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);


    GtkWidget *box, *label, *spinbt;


    return box;
}
*/




/*
GtkWidget *create_adjustment (const char *name, float min, float max, float step, float value,
                              void callback (), gpointer data) {

    GtkWidget *box, *label, *spinbt;

    box = gtk_hbox_new (FALSE, 0);
    label = gtk_label_new (name);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);

    spinbt = gtk_spin_button_new_with_range (min, max, step);
    gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinbt), value);                    // start value
    g_signal_connect (G_OBJECT (spinbt), "value-changed", G_CALLBACK (callback), data);
    gtk_box_pack_end (GTK_BOX (box), spinbt, FALSE, FALSE, 0);

    return box;
}
*/



//~ --------------------------------------------------------------------------------------------------------------------
//~ this function shall be used when massively creating adj widgets
//~ --------------------------------------------------------------------------------------------------------------------
 
//~ --------------------------------------------------------------------------------------------------------------------
//~ create_scale_adjustment
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *create_scale_adjustment (const char *name, double min, double max, double step, double value,
                                    gboolean horiz, void callback (), gpointer data) {

    GtkWidget *scale, *box, *label;
    if (horiz == TRUE)
        box = gtk_hbox_new (FALSE, 0);
    else
        box = gtk_vbox_new (FALSE, 0);
    label = gtk_label_new (name);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
    GtkObject *adjustment = gtk_adjustment_new (value, min, max, step, 0.01, 0.0);
    // value, lower, upper, step_increment, page_inc, page_size
    if (horiz == TRUE)
        scale = gtk_hscale_new (GTK_ADJUSTMENT (adjustment));
    else
        scale = gtk_vscale_new (GTK_ADJUSTMENT (adjustment));
    g_signal_connect (G_OBJECT (adjustment), "value-changed", G_CALLBACK (callback), data);
    gtk_box_pack_start (GTK_BOX (box), scale, TRUE, TRUE, 0);
    return box;
}

//~ --------------------------------------------------------------------------------------------------------------------
//~ create_spin_button
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *create_spin_button (const char *name, float min, float max, float step, float value,
                               void callback (), gpointer data) {
 
    GtkWidget *box, *label, *spinbt;
    box = gtk_hbox_new (TRUE, 10);
    label = gtk_label_new (name);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
    spinbt = gtk_spin_button_new_with_range (min, max, step);
    gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinbt), value);                        // start value
    g_signal_connect (G_OBJECT (spinbt), "value-changed", callback, data);
    gtk_box_pack_start (GTK_BOX (box), spinbt, FALSE, FALSE, 0);
    return box;
}


 
