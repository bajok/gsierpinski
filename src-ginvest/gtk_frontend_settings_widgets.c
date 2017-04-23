/*
 *      gtk_frontend_settings_widgets.c
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
#include "configuration.h"
#include "gtk_frontend_widgets.h"
#include "gtk_frontend_gl_widgets.h"
#include "gtk_callbacks.h"


//~ --------------------------------------------------------------------------------------------------------------------
//~        verify_input_data_widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *verify_input_data_widget (gint t_stock_enum, std_entire_data *source) {
 
    GtkWidget *main_box = gtk_vbox_new (FALSE, 0);
    GtkWidget *frame;
    GtkWidget *vbox, *hbox;
    GtkWidget *adj;

    frame = gtk_frame_new (" --- print data --- ");
    gtk_box_pack_start (GTK_BOX (main_box), frame, TRUE, TRUE, 0);

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), hbox);

    adj = create_spin_button ("listing", 0, current->listings_max - 1, 1, dbg_data->print_listing,
                              cb_chgval_debug_data, GINT_TO_POINTER (DEBUG_PRINT_LISTING));
    gtk_box_pack_start (GTK_BOX (hbox), adj, TRUE, FALSE, 0);

    adj = create_spin_button ("label", 0, current->labels_max - 1, 1, dbg_data->print_label,
                              cb_chgval_debug_data, GINT_TO_POINTER (DEBUG_PRINT_LABEL));
    gtk_box_pack_start (GTK_BOX (hbox), adj, TRUE, FALSE, 0);


    frame = gtk_frame_new (" --- set data --- ");
    gtk_box_pack_start (GTK_BOX (main_box), frame, TRUE, TRUE, 0);

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), hbox);

    adj = create_spin_button ("current->get_listing", 0, current->listings_max - 1, 1, current->get_listing,
                              cb_chgval_current_data, GINT_TO_POINTER (CURRENT_GET_LABEL));
    gtk_box_pack_start (GTK_BOX (hbox), adj, TRUE, FALSE, 0);

    adj = create_spin_button ("current->get_label", 0, current->labels_max - 1, 1, current->get_label,
                              cb_chgval_current_data, GINT_TO_POINTER (CURRENT_GET_LISTING));
    gtk_box_pack_start (GTK_BOX (hbox), adj, TRUE, FALSE, 0);



    frame = gtk_frame_new (" draw graph for label ");
    gtk_box_pack_start (GTK_BOX (main_box), frame, TRUE, TRUE, 0);

 


    return main_box;
}

 

//~ --------------------------------------------------------------------------------------------------------------------
//~        current_settings_widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *current_settings_widget () {

    GtkWidget *main_box = gtk_vbox_new (FALSE, 0);
    GtkWidget *frame;
    GtkWidget *vbox, *hbox;
    GtkWidget *adj;

    frame = gtk_frame_new ("cb_chgval_current_data");
    gtk_box_pack_start (GTK_BOX (main_box), frame, TRUE, TRUE, 0);

    hbox = gtk_hbox_new (FALSE, 0);
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), hbox);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);

/*
    adj = create_spin_button ("current->listing_older", 0, current->listings_max - 3, 1, current->listing_older,
                              cb_chgval_current_data, GINT_TO_POINTER (CURRENT_LISTING_OLDER));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("current->listing_newer", 2, current->listings_max - 1, 1, current->listing_newer,
                              cb_chgval_current_data, GINT_TO_POINTER (CURRENT_LISTING_NEWER));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
*/

 
    return main_box;
} 
  
//~ --------------------------------------------------------------------------------------------------------------------
//~        current_settings_widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *statdata_settings_widget () {

    GtkWidget *main_box = gtk_vbox_new (FALSE, 0);
    GtkWidget *frame;
    GtkWidget *vbox, *hbox;
    GtkWidget *adj;

    frame = gtk_frame_new ("periods per period type: ");
    gtk_box_pack_start (GTK_BOX (main_box), frame, TRUE, TRUE, 0);

    hbox = gtk_hbox_new (FALSE, 0);
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), hbox);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);

    adj = create_spin_button ("t1 period", 2, T1_PERIOD_MAX, 1, statparams->t1_period_len,
                              cb_chgval_statistics_parameters, GINT_TO_POINTER (STATPAR_T1));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("t2 period", 3, T2_PERIOD_MAX, 1, statparams->t2_period_len,
                              cb_chgval_statistics_parameters, GINT_TO_POINTER (STATPAR_T2));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
//    adj = create_spin_button ("t3 period", 5, T3_PERIOD_MAX, 1, statparams->t3_period_len,
//                              cb_chgval_statistics_parameters, GINT_TO_POINTER (STATPAR_T3));
//    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
  
 
    frame = gtk_frame_new ("empty frame ");
    gtk_box_pack_end (GTK_BOX (main_box), frame, TRUE, TRUE, 0);
    hbox = gtk_hbox_new (FALSE, 0);
 

    frame = gtk_frame_new ("visible columns: ");
    gtk_box_pack_end (GTK_BOX (main_box), frame, TRUE, TRUE, 0);
    hbox = gtk_hbox_new (FALSE, 0);
 
    GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);  // scrolled window
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), GTK_WIDGET (hbox));

    gtk_container_add (GTK_CONTAINER (frame), scrolled_window);

    GtkWidget *button;
    guint stat_enum = STAT_T_STATISTIC_LAST_INDEX;
    guint column_set = 0;
 
    // this should be in scrolled window (horizontally)

    for (guint clmn_iter = 0; clmn_iter < UI->adv_columns_total; clmn_iter++) {

        // if (UI->adv_columns_visible_arr [clmn_iter] == FALSE) continue; // do not append this column

        if (stat_enum == STAT_T_STATISTIC_LAST_INDEX) { // append label column every statistic set

            gchar *column_name = g_strconcat ("label-",
                                              g_strdup_printf ("%d ", column_set), NULL);
            button = gtk_toggle_button_new_with_label (column_name);
            if (UI->adv_columns_visible_arr [clmn_iter] == TRUE)
                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
            else
                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), FALSE);
            g_signal_connect (G_OBJECT (button), "toggled", G_CALLBACK (cb_update_visible_columns),
                              GINT_TO_POINTER ((LIST_STORE_ADV_STATS * WIDGET_K) + clmn_iter));
  
            gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, FALSE, 0); 
            g_free (column_name);
 
            stat_enum = 0;
            column_set++;  // for string concatenation
            continue; // go next
        }
        
        gchar *column_name = g_strconcat (t_stat_name_default [stat_enum],
                                          g_strdup_printf ("%d ", column_set), NULL);
        button = gtk_toggle_button_new_with_label (column_name);
        if (UI->adv_columns_visible_arr [clmn_iter] == TRUE)
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
        else
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), FALSE);
        g_signal_connect (G_OBJECT (button), "toggled", G_CALLBACK (cb_update_visible_columns),
                          GINT_TO_POINTER ((LIST_STORE_ADV_STATS * WIDGET_K) + clmn_iter));
        gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, FALSE, 0); 
        g_free (column_name);
        stat_enum++;
    }
  

 
/*
    GtkWidget *button;
    guint iter = 0;

    for (guint clmn_set = 0; clmn_set < TN_PERIOD_TYPES; clmn_set++) {

        hbox = gtk_hbox_new (FALSE, 0);
        gtk_container_add (GTK_CONTAINER (vbox), hbox);
 
        // for each field in column set append value
        for (t_statistic_type_enum stat_enum = 0; stat_enum < STAT_T_STATISTIC_LAST_INDEX; stat_enum++) {
  
            gchar *button_label = g_strconcat (t_stat_name_default [stat_enum],
                                               g_strdup_printf ("%d", clmn_set + 1), NULL);
            button = gtk_toggle_button_new_with_label (button_label);
            if (UI->adv_columns_visible_arr [iter] == TRUE)
                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
            else
                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), FALSE);
            g_signal_connect (G_OBJECT (button), "toggled", G_CALLBACK (cb_update_visible_columns),
                                                            GINT_TO_POINTER (LIST_STORE_ADV_STATS * WIDGET_K + iter));
            gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, FALSE, 0); 
            g_free (button_label);
            iter++;
        }
    }
*/


 
// checkbuttons for columns
 
 

    return main_box;
}
 

//~ --------------------------------------------------------------------------------------------------------------------
//~        glarea_settings_widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *glarea_settings_widget () {

    GtkWidget *main_box = gtk_vbox_new (FALSE, 0);
    GtkWidget *frame;
    GtkWidget *vbox, *hbox;
    GtkWidget *adj;

    frame = gtk_frame_new ("glgraph_properties (scene)");
    gtk_box_pack_start (GTK_BOX (main_box), frame, TRUE, TRUE, 0);

    hbox = gtk_hbox_new (FALSE, 0);
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), hbox);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);

    adj = create_spin_button ("scene->gltranslate_X", -100.0, 100.0, 0.001, scene->gltranslate [0],
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (SCENE_GLTRANSLATE_X));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("scene->gltranslate_Y", -100.0, 100.0, 0.001, scene->gltranslate [1],
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (SCENE_GLTRANSLATE_Y));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("scene->gltranslate_Z", -100.0, 100.0, 0.001, scene->gltranslate [2],
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (SCENE_GLTRANSLATE_Z));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

    adj = create_spin_button ("scene->glrotate_angle", ANGLE_MIN, ANGLE_MAX, 1, scene->glrotate [0],
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (SCENE_GLROTATE_ANGLE));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("scene->glrotate_X", ANGLE_MIN, ANGLE_MAX, 1, scene->glrotate [1],
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (SCENE_GLROTATE_X));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("scene->glrotate_Y", ANGLE_MIN, ANGLE_MAX, 1, scene->glrotate [2],
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (SCENE_GLROTATE_Y));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("scene->glrotate_Z", ANGLE_MIN, ANGLE_MAX, 1, scene->glrotate [3],
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (SCENE_GLROTATE_Z));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

    frame = gtk_frame_new ("glgraph_properties (other)");
    gtk_box_pack_start (GTK_BOX (main_box), frame, TRUE, TRUE, 0);

    adj = create_spin_button ("properties->plane_thickness", 0, 10, 0.001, properties->plane_thickness,
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (PLANE_THICKNESS));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("properties->plane_altitude", 0, 10, 1, properties->plane_altitude,
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (PLANE_ALTITUDE));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("properties->line_Z_layer", -10, 10, 0.00001, properties->line_Z_layer,
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (LINE_Z_LAYER));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("properties->line_thickness", 0, 2, 0.00001, properties->line_thickness,
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (LINE_THICKNESS));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    adj = create_spin_button ("properties->line_altitude", -10, 10, 1, properties->line_altitude,
                              cb_chgval_glgraph_properties, GINT_TO_POINTER (LINE_ALTITUDE));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);


    hbox = gtk_hbox_new (FALSE, 0);
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), hbox);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);


    return main_box;
}




