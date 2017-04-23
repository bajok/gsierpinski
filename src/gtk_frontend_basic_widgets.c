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
// move value to the beginning ?
*/

  
//~ --------------------------------------------------------------------------------------------------------------------
//~ create_scale_adjustment
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *create_scale_adjustment (const char *name, gdouble min, gdouble max, gdouble step, gdouble value,
                                    gboolean horiz, void callback (), gpointer data) {

    GtkWidget *scale, *box, *label;
    if (horiz == TRUE)
        box = gtk_hbox_new (TRUE, 5);
    else
        box = gtk_vbox_new (TRUE, 5);
    label = gtk_label_new (name);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
    GtkObject *adjustment = gtk_adjustment_new (value, min, max, step, 0.001, 0.1);
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
//~ create_scale_adjustment
//~ --------------------------------------------------------------------------------------------------------------------
 
GtkWidget *create_scale_adjustment_nolabel (gdouble min, gdouble max, gdouble step, gdouble value,
                                            void callback (), gpointer data) {

    GtkWidget *scale, *box;
    box = gtk_hbox_new (TRUE, 5);
    GtkObject *adjustment = gtk_adjustment_new (value, min, max, step, 0.001, 0.01);
    // value, lower, upper, step_increment, page_inc, page_size
    scale = gtk_hscale_new (GTK_ADJUSTMENT (adjustment));
    g_signal_connect (G_OBJECT (adjustment), "value-changed", G_CALLBACK (callback), data);
    gtk_box_pack_start (GTK_BOX (box), scale, TRUE, TRUE, 0);
    return box;
}
  
//~ --------------------------------------------------------------------------------------------------------------------
//~ create_spin_button
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *create_spin_button (const char *name, gfloat min, gfloat max, gfloat step, gfloat value,
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


 
