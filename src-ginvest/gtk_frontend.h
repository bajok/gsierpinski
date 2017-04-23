/*
 *      gtk_frontend.h
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


#ifndef __gtk_frontend_h_
#define __gtk_frontend_h_

#include "gtk_frontend_child_windows.h"



typedef enum {

    MAIN_WINDOW,
    MAIN_WINDOW_TITLE,

    CHILD_WINDOW_SETTINGS,
    CHILD_WINDOW_DIAGNOSTIC,
    CHILD_WINDOW_STATISTICS,

    LIST_STORE_STD_STATS,
    LIST_STORE_ADV_STATS,
 
} t_frontend_widgets_enum;


//~ --------------------------------------------------------------------------------------------------------------------
//~ USER INTERFACE GLOBAL WIDGET POINTERS
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _frontend_widgets frontend_widgets;

struct _frontend_widgets {

    //~ ----------------------------------------------------------------------------
    //~ main_window
    //~ ----------------------------------------------------------------------------
    GtkWidget *main_window;

        gchar     *main_window_title;

    //~ ----------------------------------------------------------------------------
    //~ child_window_settings
    //~ ----------------------------------------------------------------------------
    GtkWidget *child_window_settings;


    //~ ----------------------------------------------------------------------------
    //~ child_window_diagnostic
    //~ ----------------------------------------------------------------------------
    GtkWidget *child_window_diagnostic;


    //~ ----------------------------------------------------------------------------
    //~ child_window_statistics
    //~ ----------------------------------------------------------------------------
    GtkWidget *child_window_statistics;
  
        GtkNotebook     *statistics_tabbed_view;
        GtkWidget       *statistics_period_label;
        GtkWidget       *statistics_listing_adjustment_label;

        GtkWidget       *statistics_tab1_box;
        GtkWidget       *statistics_std_treeview_widget;
        GtkTreeView     *treeview_std_stats;
        GtkListStore    *ls_std_stats;
        guint            std_columns_total;
        gboolean        *std_columns_visible_arr;  // [columns_total_adv]
   
        GtkWidget       *statistics_tab2_box;
        GtkWidget       *statistics_adv_treeview_widget;
        GtkTreeView     *treeview_adv_stats;
        GtkListStore    *ls_adv_stats;
        guint            adv_columns_total;
        gboolean        *adv_columns_visible_arr;
   
};
  
  

extern frontend_widgets *UI;



// main window standard widgets
GtkWidget *append_main_window (const gchar *title);





#endif // __gtk_frontend_h
