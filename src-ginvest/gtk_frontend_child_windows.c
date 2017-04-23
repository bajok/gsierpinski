/*
 *      gtk_frontend_child_windows.c
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
#include "gtk_frontend.h"
#include "gtk_callbacks.h"



#include "gtk_frontend.h"
#include "gtk_frontend_widgets.h"
#include "gtk_frontend_settings_widgets.h"
#include "gtk_frontend_treeview_widgets.h"




//~ --------------------------------------------------------------------------------------------------------------------
//~        append_child_window_settings
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *append_child_window_settings (const gchar *name) {

    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW      (DEBUG_GTK, "append_child_window_settings", "creating child window with settings")
    DEBUG_LOG_STRING    (DEBUG_GTK, " ", "name", name)
    #endif

    GtkWidget *window                       = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *window_interior              = gtk_vbox_new (FALSE, 0);

    GtkWidget *current_settings             = current_settings_widget ();
    GtkWidget *gldisplay_settings           = glarea_settings_widget ();
/*
    GtkWidget *main_menu                    = app_main_window_menu ();
*/

    gtk_window_set_default_size (GTK_WINDOW (window), config->settings_window_size_x, config->settings_window_size_y);

    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_hide_widget_itself), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (cb_hide_widget_itself), NULL);
    gtk_window_set_title (GTK_WINDOW (window), name);
    gtk_container_set_border_width (GTK_CONTAINER (window), 1);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);


    gtk_container_add (GTK_CONTAINER (window), window_interior);

    GtkWidget *hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window_interior), hbox);

    GtkWidget *tabbed_view = gtk_notebook_new ();
    gtk_container_add (GTK_CONTAINER (hbox), tabbed_view);
    gtk_widget_set_size_request (tabbed_view, -1, -1);

    GtkWidget *label;
    label = gtk_label_new ("current settings");
    gtk_notebook_append_page_menu (GTK_NOTEBOOK (tabbed_view), current_settings, label, NULL);
    label = gtk_label_new ("gldisplay settings");
    gtk_notebook_append_page_menu (GTK_NOTEBOOK (tabbed_view), gldisplay_settings, label, NULL);

/*
    label = gtk_label_new ("gtk_graph");
    gtk_notebook_append_page_menu (GTK_NOTEBOOK (tabbed_view), tabbed_gtk_graph, label, NULL);
*/


/*
    gtk_window_set_urgency_hint (GTK_WINDOW (window), TRUE);
*/

    return window;
}




/*
#define LABEL_CSTR_CURRENT_PERIOD "listed period: "
*/

//~ --------------------------------------------------------------------------------------------------------------------
//~        append_child_window_statistics
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *append_child_window_statistics (const gchar *name, gint t_stock_enum, std_entire_data *source) {

    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW      (DEBUG_GTK, "append_child_window_statistics", "creating child window with statistics")
    DEBUG_LOG_STRING    (DEBUG_GTK, " ", "name", name)
    #endif

    GtkWidget *window                       = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *window_interior              = gtk_vbox_new (FALSE, 0);
    GtkWidget *toolbar                      = child_window_statistics_toolbar ();
    GtkWidget *settings_widget              = statdata_settings_widget (t_stock_enum, source);
    GtkWidget *button, *scale_adj, *label;


/*  
    GtkWidget *current_settings             = current_settings_widget ();
    GtkWidget *gldisplay_settings           = glarea_settings_widget ();
*/
/* 
    GtkWidget *main_menu                    = app_main_window_menu ();
*/ 

    gtk_window_set_default_size (GTK_WINDOW (window),
                                 config->statistics_window_size_x, config->statistics_window_size_y);

    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_hide_widget_itself), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (cb_hide_widget_itself), NULL);
    gtk_window_set_title (GTK_WINDOW (window), name);
    gtk_container_set_border_width (GTK_CONTAINER (window), 1);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);

    gtk_container_add (GTK_CONTAINER (window), window_interior);
    gtk_box_pack_start (GTK_BOX (window_interior), toolbar, FALSE, FALSE, 0);
    GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
    GtkWidget *hbox = gtk_hbox_new (FALSE, 0); // stores spin buttons
    gtk_box_pack_start (GTK_BOX (window_interior), vbox, FALSE, TRUE, 0);
    
    UI->statistics_period_label = gtk_label_new (CSTR_STAT_CURRENT_PERIOD);
    gtk_box_pack_start (GTK_BOX (vbox), UI->statistics_period_label, FALSE, TRUE, 0);

    GtkWidget *separator = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, TRUE, 0);

    // adjustments:
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);
 

    guint first_listing = 0;
    guint last_listing = source->num_of_listings - 1;

    GtkWidget *hbox2 = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (hbox), hbox2);

    UI->statistics_listing_adjustment_label = gtk_label_new ("latest listing: ");
    gtk_box_pack_start (GTK_BOX (hbox2), UI->statistics_listing_adjustment_label, FALSE, FALSE, 0);
    GtkObject *adjustment = gtk_adjustment_new (statdata->get_listing, 0, last_listing, 1.0, 10.0, 0.0);
    scale_adj = gtk_hscale_new (GTK_ADJUSTMENT (adjustment));
    g_signal_connect (G_OBJECT (adjustment), "value-changed", G_CALLBACK (cb_chgval_statistics_data),
                                                              GINT_TO_POINTER (STATDATA_GET_LISTING_RANGE));
    gtk_box_pack_start (GTK_BOX (hbox2), scale_adj, TRUE, TRUE, 0);
 

 
 
    button = create_spin_button ("historic range: ", 0, last_listing, 1, statdata->get_listing_range,
                                 cb_chgval_statistics_data, GINT_TO_POINTER (STATDATA_GET_LISTING_RANGE));
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, FALSE, 0);
 

 
/*
    guint16 lstmax = current->listings_max - 1;
    button = create_spin_button ("latest listing: ", 0, lstmax, 1, statdata->get_listing,
                                 cb_chgval_statistics_data, GINT_TO_POINTER (STATDATA_GET_LISTING));
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, FALSE, 0);
 
    button = create_spin_button ("historic range: ", 0, lstmax - 1, 1, statdata->get_listing_range,
                                 cb_chgval_statistics_data, GINT_TO_POINTER (STATDATA_GET_LISTING_RANGE));
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, FALSE, 0);

    scale_adj = create_scale_adjustment ("latest listing: ", 0, lstmax, 1, statdata->get_listing, TRUE,
                                         cb_chgval_statistics_data, GINT_TO_POINTER (STATDATA_GET_SCALE_LISTING));
    gtk_box_pack_start (GTK_BOX (hbox), scale_adj, TRUE, TRUE, 0);
    
    scale_adj = create_scale_adjustment ("historic range: ", 0, lstmax, 1, statdata->get_listing_range, TRUE,
                                         cb_chgval_statistics_data, GINT_TO_POINTER (STATDATA_GET_SCALE_LISTING_RANGE));
    gtk_box_pack_start (GTK_BOX (hbox), scale_adj, TRUE, TRUE, 0);
*/
 


    button = create_spin_button ("label", 0, current->labels_max - 1, 1, statdata->get_label,
                                 cb_chgval_statistics_data, GINT_TO_POINTER (STATDATA_GET_LABEL));
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, FALSE, 0);



    UI->statistics_tabbed_view = gtk_notebook_new ();

    separator = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, TRUE, 0);

    gtk_container_add (GTK_CONTAINER (window_interior), UI->statistics_tabbed_view);
/*
    gtk_box_pack_start (GTK_BOX (vbox), tabbed_view, TRUE, TRUE, 0);
*/
    gtk_widget_set_size_request (UI->statistics_tabbed_view, -1, -1);


    UI->statistics_tab1_box = gtk_vbox_new (FALSE, 0);
    UI->statistics_tab2_box = gtk_vbox_new (FALSE, 0);

    UI->statistics_std_treeview_widget    = create_std_statistics_treeview_widget (t_stock_enum, source);
    UI->statistics_adv_treeview_widget    = create_adv_statistics_treeview_widget (t_stock_enum, source);
 
    gtk_container_add ((GtkContainer *) UI->statistics_tab1_box, UI->statistics_adv_treeview_widget);
    gtk_container_add ((GtkContainer *) UI->statistics_tab2_box, UI->statistics_std_treeview_widget);
   

    // notebook view is left unchanged
  
    label = gtk_label_new ("statistics");
    gtk_notebook_append_page_menu ((GtkNotebook *)
        (UI->statistics_tabbed_view), UI->statistics_tab1_box, label, NULL);

    label = gtk_label_new ("period overview");
    gtk_notebook_append_page_menu ((GtkNotebook *)
        (UI->statistics_tabbed_view), UI->statistics_tab2_box, label, NULL);


    label = gtk_label_new ("conditions");
    gtk_notebook_append_page_menu ((GtkNotebook *)
        (UI->statistics_tabbed_view), settings_widget, label, NULL);

 

// settings tab
 

/*
    gtk_box_pack_end (GTK_BOX (vbox), tabbed_view, TRUE, TRUE, 10);
*/


    return window;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~        append_child_window_verification
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *append_child_window_diagnostic (const gchar *name, gint t_stock_enum, std_entire_data *source) {

    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW      (DEBUG_GTK, "append_child_window_diagnostic", "creating diagnostic child window")
    DEBUG_LOG_STRING    (DEBUG_GTK, " ", "name", name)
    #endif

    GtkWidget *window                       = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *window_interior              = gtk_vbox_new (FALSE, 0);
    GtkWidget *toolbar                      = child_window_diagnostic_toolbar ();
    GtkWidget *verification_widget          = verify_input_data_widget (t_stock_enum, source);

/*
    GtkWidget *current_settings             = current_settings_widget ();
    GtkWidget *gldisplay_settings           = glarea_settings_widget ();
*/
/*
    GtkWidget *main_menu                    = app_main_window_menu ();
*/

    gtk_window_set_default_size (GTK_WINDOW (window),
                                 config->diagnostic_window_size_x, config->diagnostic_window_size_y);

    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_hide_widget_itself), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (cb_hide_widget_itself), NULL);
    gtk_window_set_title (GTK_WINDOW (window), name);
    gtk_container_set_border_width (GTK_CONTAINER (window), 1);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);

    gtk_container_add (GTK_CONTAINER (window), window_interior);
    gtk_box_pack_start (GTK_BOX (window_interior), toolbar, FALSE, FALSE, 0);
    GtkWidget *hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window_interior), hbox);


    gtk_box_pack_start (GTK_BOX (hbox), verification_widget, TRUE, TRUE, 10);


    return window;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~ main window widget
//~ --------------------------------------------------------------------------------------------------------------------

/*
GtkWidget *app_main_window (const gchar *name) {

    GtkWidget *window                       = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *window_interior              = gtk_vbox_new (FALSE, 0);
    GtkWidget *main_menu                    = app_main_window_menu ();
    GtkWidget *toolbar                      = app_main_window_toolbar ();
    // main GL widget
    GtkWidget *gtkglext_context_widget      = app_main_gtkglext_context_widget ();
    // tabbed view:
    GtkWidget *tabbed_current_settings      = current_settings_widget ();
    GtkWidget *tabbed_glarea_settings       = glarea_settings_widget ();
    GtkWidget *tabbed_gtk_graph             = gtk_graph_widget ();
    GtkWidget *tabbed_verify_data           = verify_input_data_widget ();

    gtk_window_set_default_size (GTK_WINDOW (window), config->window_size_x, config->window_size_y);

    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_app_close), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (cb_app_close), NULL);
    gtk_window_set_title (GTK_WINDOW (window), name);
    gtk_container_set_border_width (GTK_CONTAINER (window), 1);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);


    gtk_container_add (GTK_CONTAINER (window), window_interior);                       // packing main container inside window
    gtk_box_pack_start (GTK_BOX (window_interior), main_menu, FALSE, FALSE, 2);        // packing main menu inside container
    gtk_box_pack_start (GTK_BOX (window_interior), toolbar, FALSE, FALSE, 0);          // next, packing a toolbar
//     gtk_box_pack_start (GTK_BOX (window_interior), display_widget, FALSE, FALSE, 0);          // next, packing a graph widget



    //~ ---------------------
    //~ main GL display area:
    //~ ---------------------
    gtk_box_pack_start (GTK_BOX (hbox), gtkglext_context_widget, TRUE, TRUE, 20);
    gtk_widget_set_size_request (GTK_WIDGET (gtkglext_context_widget), config->graph_width, config->graph_height);

//    gtk_container_add (GTK_CONTAINER (hbox), gtkglext_context_widget);

//     tabbed_view = gtk_notebook_new ();
//     gtk_container_add (GTK_CONTAINER (vbox), tabbed_view);
//     gtk_widget_set_size_request (tabbed_view, 720, -1);

    GtkWidget *status_bar = gtk_statusbar_new ();
    gtk_box_pack_end (GTK_BOX (window_interior), status_bar, FALSE, FALSE, 0);

    return window;
}

*/
