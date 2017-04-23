/*
 *      gtk_frontend_treeview_widgets.c
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
#include <glib/gprintf.h>
#include "data_structures_init.h"
#include "configuration.h"
#include "gtk_callbacks.h"

 
//~ --------------------------------------------------------------------------------------------------------------------
//~ generic table widget
//~ --------------------------------------------------------------------------------------------------------------------
 
  

/*
        wyjebac kolumne daty, na chuj ona tu jest i dac labelke z data!
*/

//~ --------------------------------------------------------------------------------------------------------------------
//~  append_gtkliststore_standard_stats -- this function shall be never called directly! -- use callback instead
//~ --------------------------------------------------------------------------------------------------------------------

void append_gtkliststore_standard_stats (gint t_stock_enum, std_entire_data *source, guint ll) {

    GtkTreeIter iter;
    gtk_list_store_clear ((GtkListStore *) UI->ls_std_stats); 

    // standard statistics
    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW    (DEBUG_GTK, "append_gtkliststore_standard_stats", "refreshing liststore...")
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_POINTER (DEBUG_GTK, " ", "(std_entire_data *) source", source)
    DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "t_stock_enum", t_stock_enum)
    DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "listing", ll)
    #endif
    #endif

    g_return_if_fail (ll < source->num_of_listings);

    for (guint index = 0; index < (source->num_of_labels); index++) {

        if (source->daily[ll]->listed[index] != NULL) {

            gboolean listed = TRUE;
            if (((gfloat) (source->daily[ll]->listed[index]->v_open) == 0.0) &&
                ((gfloat) (source->daily[ll]->listed[index]->v_close) == 0.0)) listed = FALSE;

            if (((statdata->toggle_show_zeroes) == FALSE) && (listed == FALSE)) continue;
            // else
            // data may be a vector also... 

            gchar *value_array [DAILY_T_LAST_INDEX];
            gchar *label        = g_strdup_printf ("%s", (gchar *) (source->labels[index]->name));

            if (listed == TRUE) {
                // converting float values to string 
                value_array [0] = g_strdup_printf ("%.2f", (gfloat) (source->daily[ll]->listed[index]->v_open));
                value_array [1] = g_strdup_printf ("%.2f", (gfloat) (source->daily[ll]->listed[index]->v_high));
                value_array [2] = g_strdup_printf ("%.2f", (gfloat) (source->daily[ll]->listed[index]->v_low));
                value_array [3] = g_strdup_printf ("%.2f", (gfloat) (source->daily[ll]->listed[index]->v_close));
                value_array [4] = g_strdup_printf ("%.2f", (gfloat) (source->daily[ll]->listed[index]->volume));
            }
            else {
                for (guint val = 0; val < DAILY_T_LAST_INDEX; val++)
                    value_array [val] = g_strdup_printf (".");
            }
 
            #ifdef DEBUG_GTK
            #ifdef DEBUG_WITH_EXTENDED_OUTPUT
            DEBUG_LOG_STRING_ARRAY (DEBUG_GTK," ","value_array [5] = ", value_array, DAILY_T_LAST_INDEX)
            #endif
            #endif

            gtk_list_store_append ((GtkListStore *) UI->ls_std_stats, &iter);

            // setting label
            gtk_list_store_set ((GtkListStore *) UI->ls_std_stats, &iter, 0, label, -1);
            // setting all values
            for (guint val = 0; val < DAILY_T_LAST_INDEX; val++)
                gtk_list_store_set ((GtkListStore *) UI->ls_std_stats, &iter, val + 1, value_array [val], -1);
 
            g_free (label);
            for (guint val = 0; val < DAILY_T_LAST_INDEX; val++)
                g_free (value_array [val]);
        }
    } 
   
} 
  
  
//~ --------------------------------------------------------------------------------------------------------------------
//~  append_gtkliststore_advanced_stats -- this function shall be never called directly! -- use callback instead
//~ --------------------------------------------------------------------------------------------------------------------

void append_gtkliststore_advanced_stats (gint t_stock_enum, std_entire_data *source) {
  

    GtkTreeIter iter;
    gtk_list_store_clear ((GtkListStore *) UI->ls_adv_stats); 

    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW    (DEBUG_GTK, "append_gtkliststore_advanced_stats", "refreshing liststore...")
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_POINTER (DEBUG_GTK, " ", "source", source)
    DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "t_stock_enum", t_stock_enum)
    #endif
    #endif
 
    // for each label append row in list store
    for (guint index = 0; index < (source->num_of_labels); index++) {

        gtk_list_store_append ((GtkListStore *) UI->ls_adv_stats, &iter);

        gchar *label        = g_strdup_printf ("%s", (gchar *) (source->labels[index]->name));
        gtk_list_store_set (UI->ls_adv_stats, &iter, 0, label, -1);

/*
        t_statistic_type_enum stat_enum = STAT_T_STATISTIC_LAST_INDEX;
*/
        t_statistic_type_enum stat_enum = 0;

 
        for (guint clmn_iter = 1; clmn_iter < UI->adv_columns_total; clmn_iter++) {
  
            if (UI->adv_columns_visible_arr [clmn_iter] == TRUE) {

                gchar *field_value  = ".";
       
                // get value as float or decimal
                if (stat_enum == (guint) STAT_T_EQUALS ||
                    stat_enum == (guint) STAT_T_EQUALS_T1 ||
                    stat_enum == (guint) STAT_T_EQUALS_T2 ||
                    stat_enum == (guint) STAT_T_INCREASES ||
                    stat_enum == (guint) STAT_T_INCREASES_T1 ||
                    stat_enum == (guint) STAT_T_INCREASES_T2 ||
                    stat_enum == (guint) STAT_T_DECREASES ||
                    stat_enum == (guint) STAT_T_DECREASES_T1 ||
                    stat_enum == (guint) STAT_T_DECREASES_T2 ||
                    stat_enum == (guint) STAT_T_LEAGUE)
                    field_value = g_strdup_printf ("%d", (gint) statdata->tn_stats[index][stat_enum]);
                else
                    field_value = g_strdup_printf ("%.2f", (gfloat) statdata->tn_stats[index][stat_enum]);
    
                // set value
                gtk_list_store_set ((GtkListStore *) UI->ls_adv_stats, &iter,
                    clmn_iter, field_value, -1);
                g_free (field_value);  
            }

            stat_enum++; 
        }
 
        g_free (label);
    } 
 
} 
  

//~ --------------------------------------------------------------------------------------------------------------------
//~        create_std_statistics_treeview_widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *create_std_statistics_treeview_widget (gint t_stock_enum, std_entire_data *source) {

    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW      (DEBUG_GTK, "create_std_statistics_treeview_widget", " ")
    DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "t_stock_enum", t_stock_enum)
    DEBUG_LOG_POINTER   (DEBUG_GTK, " ", "(std_entire_data *) source", source)
    #endif

    GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);  // scrolled window
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

//     scores_tree_view = gtk_widget_new (GTK_TYPE_TREE_VIEW, "even-row-color", &color1);
    UI->treeview_std_stats =  gtk_tree_view_new ();
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), GTK_WIDGET (UI->treeview_std_stats));


    GtkCellRenderer *cell, *cell1, *cell2;
    GtkTreeViewColumn *column;
    GdkColor color0, color1, color2;
    
    UI->ls_std_stats = (GtkListStore *) gtk_list_store_new (6,
                                                            G_TYPE_STRING,
                                                            G_TYPE_STRING,
                                                            G_TYPE_STRING,
                                                            G_TYPE_STRING,
                                                            G_TYPE_STRING,
                                                            G_TYPE_STRING);

    cell = gtk_cell_renderer_text_new ();
    cell1 = gtk_cell_renderer_text_new ();
    cell2 = gtk_cell_renderer_text_new ();

/*
    color0.pixel = 0xdddd; color0.red = 0xffff; color0.green = 0xffff; color0.blue = 0xdddd;
    color1.pixel = 0xdddd; color1.red = 0xdddd; color1.green = 0xdddd; color1.blue = 0xffff;
    color2.pixel = 0xdddd; color2.red = 0xffff; color2.green = 0xdddd; color2.blue = 0xdddd;

    g_object_set (cell, "scale", 1.0, NULL);
    g_object_set (cell, "background-gdk", &color0, NULL);
    g_object_set (cell, "foreground", "blue", NULL);

    g_object_set (cell1, "background-gdk", &color1, NULL);
    g_object_set (cell2, "background-gdk", &color2, NULL);
*/ 

    column = gtk_tree_view_column_new_with_attributes ("label", cell1, "text", 0, NULL);
    gtk_tree_view_append_column ((UI->treeview_std_stats), GTK_TREE_VIEW_COLUMN (column));

    column = gtk_tree_view_column_new_with_attributes ("v_open", cell2, "text", 1, NULL);
    gtk_tree_view_append_column ((UI->treeview_std_stats), (column));
    column = gtk_tree_view_column_new_with_attributes ("v_high", cell2, "text", 2, NULL);
    gtk_tree_view_append_column ((UI->treeview_std_stats), (column));
    column = gtk_tree_view_column_new_with_attributes ("v_low", cell2, "text", 3, NULL);
    gtk_tree_view_append_column ((UI->treeview_std_stats), (column));
    column = gtk_tree_view_column_new_with_attributes ("v_close", cell2, "text", 4, NULL);
    gtk_tree_view_append_column ((UI->treeview_std_stats), (column));
    column = gtk_tree_view_column_new_with_attributes ("volume", cell2, "text", 5, NULL);
    gtk_tree_view_append_column ((UI->treeview_std_stats), (column));
 
/*
    gtk_tree_view_column_set_min_width (column, 100);
*/ 
  
    // to be changed!
    gtk_tree_view_set_model (UI->treeview_std_stats, (UI->ls_std_stats));

    cb_update_treeview (NULL, GINT_TO_POINTER (LIST_STORE_STD_STATS));

/*
    g_signal_connect (G_OBJECT (tree_view), "row-activated", G_CALLBACK (cb_row_activated), NULL);
*/

//     g_signal_connect (G_OBJECT (scores_tree_view), "columns-changed", G_CALLBACK (cb_column_sort), NULL);

/*
void                gtk_tooltip_set_text                (GtkTooltip *tooltip,
                                                         const gchar *text);
*/
 
    g_object_set (UI->treeview_std_stats, "rules-hint", TRUE, NULL);
//     g_object_set (scores_tree_view, "headers-clickable", TRUE, NULL);
//     g_object_set (scores_tree_view, "reorderable", TRUE, NULL);


    return scrolled_window;

}



 

//~ --------------------------------------------------------------------------------------------------------------------
//~        create_adv_statistics_treeview_widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *create_adv_statistics_treeview_widget (gint t_stock_enum, std_entire_data *source) {

    #ifdef DEBUG_GTK
    DEBUG_LOG_FLOW      (DEBUG_GTK, "create_adv_statistics_treeview_widget", " ")
    DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "t_stock_enum", t_stock_enum)
    DEBUG_LOG_POINTER   (DEBUG_GTK, " ", "(std_entire_data *) source", source)
    #endif

    GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);  // scrolled window
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    UI->treeview_adv_stats =  gtk_tree_view_new ();
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), GTK_WIDGET (UI->treeview_adv_stats));

    GtkCellRenderer *cell, *cell1, *cell2;
    GtkTreeViewColumn *column;
    GdkColor color0, color1, color2;
  
    guint total_columns = UI->adv_columns_total;
 
    GType G_TYPE_STRING_ARRAY [total_columns];
    for (t_statistic_type_enum iter = 0; iter < total_columns; iter++)
         G_TYPE_STRING_ARRAY [iter] = G_TYPE_STRING;        // each type is string
 
    UI->ls_adv_stats = (GtkListStore *) gtk_list_store_newv (total_columns, G_TYPE_STRING_ARRAY);

    cell1 = gtk_cell_renderer_text_new ();
    cell2 = gtk_cell_renderer_text_new (); 

 
    t_statistic_type_enum stat_enum = 0;
/*
    guint                 column_set = -1;
*/
 
    // first is always label column
    column = gtk_tree_view_column_new_with_attributes ("label", cell1, "text", 0, NULL);
    gtk_tree_view_append_column ((UI->treeview_adv_stats), GTK_TREE_VIEW_COLUMN (column));
  
    for (guint clmn_iter = 1; clmn_iter < UI->adv_columns_total; clmn_iter++) {
 
/*
        if (stat_enum >= STAT_T_STATISTIC_LAST_INDEX) { // append label column every statistic set

            if (UI->adv_columns_visible_arr [clmn_iter] == TRUE) {
                column = gtk_tree_view_column_new_with_attributes ("label", cell1, "text", clmn_iter, NULL);
                gtk_tree_view_append_column ((UI->treeview_adv_stats), GTK_TREE_VIEW_COLUMN (column));
            }
            stat_enum = 0;
            column_set++;  // for string concatenation
            continue; // go next
        } 
*/

        if (UI->adv_columns_visible_arr [clmn_iter] == TRUE) {
            // concatenated string currently prints also value of statistic enum
            gchar *column_name = g_strconcat (t_stat_name_default [stat_enum],
                                              g_strdup_printf ("|%d|", stat_enum), NULL);
            column = gtk_tree_view_column_new_with_attributes
                        (column_name, cell2, "text", clmn_iter, NULL);
            gtk_tree_view_append_column ((UI->treeview_adv_stats), (column));
            g_free (column_name);
        }
        stat_enum++;
    }
 
    
    // to be changed!
    gtk_tree_view_set_model (UI->treeview_adv_stats, (UI->ls_adv_stats));

    cb_update_treeview (NULL, GINT_TO_POINTER (LIST_STORE_ADV_STATS));
 
    g_object_set (UI->treeview_adv_stats, "rules-hint", TRUE, NULL);
 
    return scrolled_window;
}
 
 

   
 
