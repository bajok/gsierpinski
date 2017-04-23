/*
 *      gtk_callbacks.c
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
#include "gtk_callbacks.h"


//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_app_close -- all actions that should be done on application close signal
//~ --------------------------------------------------------------------------------------------------------------------

void cb_app_close () {

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_app_close", "closing application")
    #endif 
    gtk_main_quit ();
}


//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_null -- helpfull when adding widgets with no callbacks defined
//~ --------------------------------------------------------------------------------------------------------------------

void cb_null () {
    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_null", "null callback")
        DEBUG_LOG_WARNING   (DEBUG_GTK, " ", "it is more than obvious that a callback function should be used here")
    #endif 
}

//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_display_about_window
//~ --------------------------------------------------------------------------------------------------------------------

void cb_display_about_window () {

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_display_about_window", "an about window should appear")
    #endif 

    GtkWidget *window = main_about_window (glconfig);
    gtk_widget_show_all (window);
    redisplay_sierpinski (gl_area_sierpinski);
}


//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_hide_widget_itself
//~ --------------------------------------------------------------------------------------------------------------------

void cb_hide_widget_itself (GtkWidget *widget, gpointer data) {

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_hide_widget_itself", "hiding widget...")
    #endif 

    gtk_widget_hide_all (widget);
}

//~ --------------------------------------------------------------------------------------------------------------------
//~      widget_destroy
//~ --------------------------------------------------------------------------------------------------------------------

gboolean widget_destroy (GtkWidget *widget) {

    if (GTK_WIDGET_VISIBLE (widget) == TRUE)
        gtk_widget_destroy (GTK_WIDGET (widget));
    return FALSE;       // once the widget is destroyed (prevents from calling this function again)
}


//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_toggle_widget_display_state
//~ --------------------------------------------------------------------------------------------------------------------

void cb_toggle_widget_display_state (GtkWidget *widget, gpointer data) {

/*
    gtk_widget_set_sensitive(GTK_WIDGET(p_Data), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p_Widget)));
*/

    t_frontend_widgets_enum index = GPOINTER_TO_INT (data);
    gboolean button_active_state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget));

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_update_visible_columns", "updating column visibility")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "button_active_state", button_active_state)
    #endif 

    switch (index) {
        case CHILD_WINDOW_SETTINGS:
            if (button_active_state == TRUE)
                gtk_widget_show_all (GTK_WINDOW (UI->child_window_settings));
            else
                gtk_widget_hide_all (GTK_WINDOW (UI->child_window_settings));
            break;
        case CHILD_WINDOW_DIAGNOSTIC:
            if (button_active_state == TRUE)
                gtk_widget_show_all (GTK_WINDOW (UI->child_window_diagnostic));
            else
                gtk_widget_hide_all (GTK_WINDOW (UI->child_window_diagnostic));
            break;
        case CHILD_WINDOW_STATISTICS:
            if (button_active_state == TRUE)
                gtk_widget_show_all (GTK_WINDOW (UI->child_window_statistics));
            else
                gtk_widget_hide_all (GTK_WINDOW (UI->child_window_statistics));
            break;
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_toggle_widget_display_state", "no such widget!")
            #endif
    }
 
    gboolean toggle_state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget));

    #ifdef DEBUG_GTK
        DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "toggle_state", toggle_state)
/*
        g_prnt (" d GTK     widget is active = %d\n", toggle_state);
*/
    #endif

}


//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_update_visible_columns
//~ --------------------------------------------------------------------------------------------------------------------

void cb_update_visible_columns (GtkWidget *widget, gpointer data) {

    t_frontend_widgets_enum index = GPOINTER_TO_INT (data);
    guint col_num = index;

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_update_visible_columns", "updating column visibility")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "col_num", col_num)
    #endif 

    switch (index) {
        case LIST_STORE_STD_STATS:
 
            break;
        case LIST_STORE_ADV_STATS:
            if (col_num < UI->adv_columns_total) {
                ((UI->adv_columns_visible_arr [col_num]) == FALSE) ?
                    (UI->adv_columns_visible_arr [col_num] = TRUE) :
                    (UI->adv_columns_visible_arr [col_num] = FALSE);
            }

            gtk_list_store_clear ((GtkListStore *) UI->ls_adv_stats); 
            gtk_widget_destroy (UI->statistics_adv_treeview_widget);

            UI->statistics_adv_treeview_widget
                = create_adv_statistics_treeview_widget (current->t_stock_enum, current->data_source);

            gtk_container_add ((GtkContainer *) UI->statistics_tab1_box, UI->statistics_adv_treeview_widget);
            gtk_widget_show_all (UI->statistics_tab1_box); 

            break; 
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_update_visible_columns", "no callback defined")
            #endif
            break;
    }
}
  
   
 
//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_update_treeview
//~ --------------------------------------------------------------------------------------------------------------------

void cb_update_treeview (GtkWidget *button, gpointer data) {

    t_frontend_widgets_enum index = GPOINTER_TO_INT (data);

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_update_treeview", "updating treeview")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
    #endif 

/*
    g_return_if_fail (UI->ls_std_stats != NULL);
*/ 
/*
     gtk_list_store_clear ((GtkListStore *) UI->ls_std_stats);
*/

    switch (index) {
        case LIST_STORE_STD_STATS:
            append_gtkliststore_standard_stats (current->t_stock_enum, current->data_source, statdata->get_listing);
            break;
        case LIST_STORE_ADV_STATS: 
            statistics_regenerate              (current->t_stock_enum, current->data_source);
            append_gtkliststore_advanced_stats (current->t_stock_enum, current->data_source);
            break; 
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_update_treeview", "no callback defined")
            #endif
            break;
    }
  
  
/*
    gtk_list_store_clear (UI->ls_extra_stats);
    UI->ls_extra_stats = append_gtk_list_store_statistics (current->t_stock_enum, current->data_source,
                                                           statdata->get_listing);
*/
   
} 


//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_chgval_current_data
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_current_data (GtkWidget *spinbutton, gpointer data) {

    t_cb_current_data index = GPOINTER_TO_INT (data);
    gdouble get_value = gtk_spin_button_get_value (GTK_SPIN_BUTTON (spinbutton));

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_chgval_current_data", "current data value change")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
        DEBUG_LOG_FLOAT     (DEBUG_GTK, " ", "get_value", get_value)
    #endif 

    switch (index) {

        case CURRENT_T_STOCK:
            current->t_stock_enum = get_value;
            break;
        case CURRENT_LISTINGS_MAX:
            current->listings_max = get_value;
            break;
        case CURRENT_LABELS_MAX:
            current->labels_max = get_value;
            break;
        case CURRENT_GET_LISTING:
            current->get_listing = get_value;
            break;
        case CURRENT_GET_LABEL:
            current->get_label = get_value;
            break;
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_chgval_current_data", "no callback defined")
            #endif
            break;
    }
 
    #ifdef DEBUG_GTK
        DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "get_value", get_value)
    #endif

    redisplay_glgraph (gl_area_main);
}

//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_toggle_statistics_data
//~ --------------------------------------------------------------------------------------------------------------------
  
void cb_toggle_statistics_data (GtkWidget *toggle_widget, gpointer data) {

    t_cb_statistics_data index = GPOINTER_TO_INT (data);

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_toggle_statistics_data", "statistic data toggle value change")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
    #endif 
 
    switch (index) {
        case STATDATA_TOGGLE_SHOW_ZEROES:  
            ((statdata->toggle_show_zeroes) == FALSE) ? 
                (statdata->toggle_show_zeroes = TRUE) : (statdata->toggle_show_zeroes = FALSE);
            cb_update_treeview (NULL, GINT_TO_POINTER (LIST_STORE_STD_STATS));
            break;

        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_toggle_statistics_data", "no callback defined")
            #endif
            break;
    } 
}
  
  
//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_chgval_statistics_data
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_statistics_data (GtkWidget *spinbutton, gpointer data) {
 
    t_cb_statistics_data index = GPOINTER_TO_INT (data);
//    gdouble get_value = gtk_spin_button_get_value (GTK_SPIN_BUTTON (spinbutton));

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_chgval_statistics_data", "statistic data value change")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
    #endif 

    gdouble get_value = 0.0;

    guint num_of_listings = (current->data_source)->num_of_listings;
   
    switch (index) {
/*
        case STATDATA_GET_LISTING:
            if ((guint) get_value > statdata->get_listing_range) { // (listing > range)
                get_value = gtk_spin_button_get_value (spinbutton);
                statdata->get_listing = get_value;
                cb_update_treeview (NULL, GINT_TO_POINTER (LIST_STORE_STD_STATS)); // STD stats
                gtk_label_set_text (UI->statistics_period_label, CSTR_STAT_CURRENT_PERIOD);
            }
            else
                gtk_spin_button_set_value (spinbutton, statdata->get_listing);
                // or
                // void                gtk_spin_button_update              (GtkSpinButton *spin_button);
            break;
*/
        case STATDATA_GET_LISTING_RANGE:
            #ifdef DEBUG_GTK
                DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "listing_range", statdata->get_listing_range)
                DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "listing", statdata->get_listing)
                DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "num_of_listings", num_of_listings)
            #endif
            //if ((statdata->get_listing_range + statdata->get_listing) < num_of_listings)
            if ((guint) get_value < statdata->get_listing) { // if less than current lisitng (range < listing)
                get_value = gtk_spin_button_get_value (spinbutton);
                statdata->get_listing_range = get_value;
                cb_update_treeview (NULL, GINT_TO_POINTER (LIST_STORE_STD_STATS));
                gtk_label_set_text (UI->statistics_period_label, CSTR_STAT_CURRENT_PERIOD);
            }
            else
                gtk_spin_button_set_value (spinbutton, statdata->get_listing_range);
            break; 
/*
        case STATDATA_GET_SCALE_LISTING:
            if ((guint) get_value > statdata->get_listing_range) { // (listing > range)
                get_value = gtk_adjustment_get_value (spinbutton);
                statdata->get_listing = get_value;
                cb_update_treeview (NULL, GINT_TO_POINTER (LIST_STORE_STD_STATS)); // STD stats
                gtk_label_set_text (UI->statistics_period_label, CSTR_STAT_CURRENT_PERIOD);
                gtk_label_set_text (UI->statistics_listing_adjustment_label, CSTR_STAT_CURRENT_PERIOD);
            } 
            else
                gtk_adjustment_set_value (spinbutton, statdata->get_listing);
                // or
                // void                gtk_spin_button_update              (GtkSpinButton *spin_button);
            break;
*/ 
/*
        case STATDATA_GET_SCALE_LISTING_RANGE:
            #ifdef DEBUG_GTK
                DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "listing_range", statdata->get_listing_range)
                DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "listing", statdata->get_listing)
                DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "num_of_listings", num_of_listings)
            #endif
            //if ((statdata->get_listing_range + statdata->get_listing) < num_of_listings)
            if ((guint) get_value < statdata->get_listing) { // if less than current lisitng (range < listing)
                get_value = gtk_adjustment_get_value (spinbutton);
                statdata->get_listing_range = get_value;
                cb_update_treeview (NULL, GINT_TO_POINTER (LIST_STORE_STD_STATS));
                gtk_label_set_text (UI->statistics_period_label, CSTR_STAT_CURRENT_PERIOD);
            }
            else
                gtk_adjustment_set_value (spinbutton, statdata->get_listing_range);
            break;
*/
        case STATDATA_GET_LABEL:
            statdata->get_label = get_value; 
            break;

        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_chgval_statistics_data", "no callback defined")
            #endif
            break;
    } 
    #ifdef DEBUG_GTK
        DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "get_value", get_value)
    #endif
}
 
  
  
//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_chgval_statistics_parameters
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_statistics_parameters (GtkWidget *spinbutton, gpointer data) {

    t_cb_statistics_parameters index = GPOINTER_TO_INT (data);
    gdouble get_value = gtk_spin_button_get_value (GTK_SPIN_BUTTON (spinbutton));

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_chgval_statistics_parameters", "statistic parameters value change")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
        DEBUG_LOG_FLOAT     (DEBUG_GTK, " ", "get_value", get_value)
    #endif 

    switch (index) {
        case STATPAR_T1:
            if ((guint16) get_value < T1_PERIOD_MAX + 1)
                statparams->t1_period_len = (guint16) get_value;
            break;
        case STATPAR_T2:
            if ((guint16) get_value < T2_PERIOD_MAX + 1)
                statparams->t2_period_len = (guint16) get_value;
            break;
        case STATPAR_T3:
            if ((guint16) get_value < T3_PERIOD_MAX + 1)
                statparams->t3_period_len = (guint16) get_value;
            break;
 
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_chgval_statistics_parameters", "no callback defined")
            #endif
            break;
    }   
    #ifdef DEBUG_GTK
        DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "get_value", get_value)
/*
        g_prnt (" d GTK     chgval: t%d = %d\n", index + 1, (guint16) get_value);
*/
    #endif
}
  

//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_chgval_debug_data
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_debug_data (GtkWidget *spinbutton, gpointer data) {

    t_cb_debug_data index = GPOINTER_TO_INT (data);
    gdouble get_value = gtk_spin_button_get_value (GTK_SPIN_BUTTON (spinbutton));

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_chgval_debug_data", "debug data value change")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
        DEBUG_LOG_FLOAT     (DEBUG_GTK, " ", "get_value", get_value)
    #endif 

    switch (index) {
        case DEBUG_PRINT_LISTING:
            dbg_data->print_listing = get_value;
            break;
        case DEBUG_PRINT_LABEL:
            dbg_data->print_label = get_value;
            break;
        // #endif
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_chgval_debug_data", "no callback defined")
            #endif
            break;
    }
    // g_prnt (" d   listing = %d \t label = %d\n", dbg_data->print_listing, dbg_data->print_label);




/*
    g_prnt (" d   ll = %d  %d %s (%d) %f %f %f %f %d\n",
             dbg_data->print_listing,
             newconnect->daily[dbg_data->print_listing]->int_date,
             newconnect->labels[dbg_data->print_label]->name,
             dbg_data->print_label,
             newconnect->daily[dbg_data->print_listing]->listed[dbg_data->print_label]->v_open,
             newconnect->daily[dbg_data->print_listing]->listed[dbg_data->print_label]->v_high,
             newconnect->daily[dbg_data->print_listing]->listed[dbg_data->print_label]->v_low,
             newconnect->daily[dbg_data->print_listing]->listed[dbg_data->print_label]->v_close,
             newconnect->daily[dbg_data->print_listing]->listed[dbg_data->print_label]->volume);
*/




/*
    redisplay_glgraph (gl_area_main);
*/
}







//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_chgval_glgraph_properties
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_glgraph_properties (GtkWidget *spinbutton, gpointer data) {

    t_cb_glgraph_properties index = GPOINTER_TO_INT (data);
    gdouble get_value = gtk_spin_button_get_value (GTK_SPIN_BUTTON (spinbutton));

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_chgval_glgraph_properties", "glgraph properties value change")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
        DEBUG_LOG_FLOAT     (DEBUG_GTK, " ", "get_value", get_value)
    #endif 

    switch (index) {

        case SCENE_GLTRANSLATE_X:
            scene->gltranslate [0] = get_value;
            break;
        case SCENE_GLTRANSLATE_Y:
            scene->gltranslate [1] = get_value;
            break;
        case SCENE_GLTRANSLATE_Z:
            scene->gltranslate [2] = get_value;
            break;

        case SCENE_GLROTATE_ANGLE:
            scene->glrotate [0] = get_value;
            break;
        case SCENE_GLROTATE_X:
            scene->glrotate [1] = get_value;
            break;
        case SCENE_GLROTATE_Y:
            scene->glrotate [2] = get_value;
            break;
        case SCENE_GLROTATE_Z:
            scene->glrotate [3] = get_value;
            break;

        case PLANE_THICKNESS:
            properties->plane_thickness = get_value;
            break;
        case PLANE_ALTITUDE:
            properties->plane_altitude = get_value;
            break;
        case LINE_Z_LAYER:
            properties->line_Z_layer = get_value;
            break;
        case LINE_THICKNESS:
            properties->line_thickness = get_value;
            break;
        case LINE_ALTITUDE:
            properties->line_altitude = get_value;
            break;
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_chgval_glgraph_properties", "no callback defined")
            #endif
            break;
    }
 
    redisplay_glgraph (gl_area_main);
}

 
    
// need call


//
// callback connected without a call as data is initialized here !!!!!!!!!

//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_glgraph_update_display_data
//~ --------------------------------------------------------------------------------------------------------------------

void cb_glgraph_update_display_data (GtkWidget *widget, gpointer data) {

    t_display_datatype_enum display_mode = GPOINTER_TO_INT (data);

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_glgraph_update_display_data", "glgraph display data update")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "display_mode", display_mode)
        DEBUG_LOG_POINTER   (DEBUG_GTK, "(glgraph_display_data *)", "displaydata", displaydata)
        DEBUG_LOG_POINTER   (DEBUG_GTK, "(glgraph_display_data *)", "current", current)
    #endif 

  
    // prototype:  structures_glgraph.h
    glgraph_update_display_data (displaydata, current, display_mode);
 
    // prototype:  glarea_callbacks.h
    // flow:       glarea_callbacks.h -> glgraph.h -> glgraph_drawing_procedures.h


    // BOOLEAN: ALWAYS | ON DEMAND
    redisplay_glgraph (gl_area_main, (gpointer) displaydata);

}

   
 
//~ --------------------------------------------------------------------------------------------------------------------
//~  miscellaneous callbacks -- DEPRECATED
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_sierp_gl_LookAt (GtkAdjustment *adjustment, gpointer data) {

    gint index = GPOINTER_TO_INT (data);
    sierp_gl_LookAt [(index-1)/3][(index-1)%3] = gtk_adjustment_get_value (GTK_ADJUSTMENT (adjustment));
    redisplay_sierpinski (gl_area_sierpinski);
//     realize (gl_area, NULL);
}

gboolean cb_graph_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data) {

//     gint graph_Yscale = 100;
//     gint units = 100;
    gint XMAX = widget->allocation.width;
    gint YMAX = widget->allocation.height;
//     gint X12 = widget->allocation.width / 2;

    /* filling drawing_area with white rect */
    gdk_draw_rectangle (widget->window, widget->style->white_gc, TRUE,
                        0, 0, XMAX, YMAX);
    return TRUE;
}
