/*
 *      gtk_callbacks.h
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


#ifndef __gtk_callbacks_h_
#define __gtk_callbacks_h_


#include "gtk_frontend.h"



// total columns shall be less than:  WIDGET
#define WIDGET_K 1024
 

#define ENUM_WIDGET_INDEX    GINT_TO_POINTER


 
typedef enum {

    CURRENT_T_STOCK,
    CURRENT_LISTINGS_MAX,
    CURRENT_LABELS_MAX,
    CURRENT_GET_LISTING,
    CURRENT_GET_LABEL,
    CURRENT_PRINT_LISTING,
    CURRENT_PRINT_LABEL,

} t_cb_current_data;


typedef enum {

    STATDATA_GET_LISTING,
    STATDATA_GET_LISTING_RANGE,
    STATDATA_GET_SCALE_LISTING,
    STATDATA_GET_SCALE_LISTING_RANGE,
    STATDATA_GET_LABEL,
    STATDATA_TOGGLE_SHOW_ZEROES,

} t_cb_statistics_data;

typedef enum {

    STATPAR_T1,
    STATPAR_T2,
    STATPAR_T3,

} t_cb_statistics_parameters;


typedef enum {

    DEBUG_PRINT_LISTING,
    DEBUG_PRINT_LABEL,

} t_cb_debug_data;


typedef enum {

    PLANE_THICKNESS,
    PLANE_ALTITUDE,
    LINE_Z_LAYER,
    LINE_THICKNESS,
    LINE_ALTITUDE,
    SCENE_GLROTATE_ANGLE,
    SCENE_GLROTATE_X,
    SCENE_GLROTATE_Y,
    SCENE_GLROTATE_Z,
    SCENE_GLTRANSLATE_X,
    SCENE_GLTRANSLATE_Y,
    SCENE_GLTRANSLATE_Z,

/*
    LINE_COLOR_R,
    LINE_COLOR_G,
    LINE_COLOR_B,
    LINE_COLOR_A,
*/

} t_cb_glgraph_properties;


 
extern GdkGLConfig *glconfig;               // from gl_config.h
extern gpointer gl_area_main, gl_area_sierpinski;


void cb_chgval_sierp_gl_LookAt          (GtkAdjustment *adjustment, gpointer data);
gboolean cb_graph_expose_event          (GtkWidget *widget, GdkEventExpose *event, gpointer data);

void cb_hide_widget_itself              (GtkWidget *widget, gpointer data);
void cb_toggle_widget_display_state     (GtkWidget* widget, gpointer data);
void cb_display_about_window ();


void cb_app_close ();
void cb_null ();
gboolean widget_destroy                 (GtkWidget *widget);



void cb_update_visible_columns          (GtkWidget *widget, gpointer data);
void cb_update_treeview                 (GtkWidget *button, gpointer liststore);

//~ --------------------------------------------------------------------------------------------------------------------
//~ generic callback
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_current_data             (GtkWidget *spinbutton, gpointer data);
void cb_chgval_debug_data               (GtkWidget *spinbutton, gpointer data);
void cb_toggle_statistics_data          (GtkWidget *button,     gpointer data);
void cb_chgval_statistics_data          (GtkWidget *spinbutton, gpointer data);
void cb_chgval_statistics_parameters    (GtkWidget *spinbutton, gpointer data);


void cb_chgval_glgraph_properties       (GtkWidget *spinbutton, gpointer data);



void cb_glgraph_update_display_data (GtkWidget *widget, gpointer data);


    //~ void cb_refresh_gl_drawable_sierpinski ();

    // value change (usually spinbuttons)





#endif // __gtk_callbacks_h
