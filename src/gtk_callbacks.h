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
#include "gtk_frontend_gl_widgets.h"


#define ENUM_WIDGET_INDEX    GINT_TO_POINTER


 
/*
typedef enum {

    PREDEFINED_COLOR_1,
    PREDEFINED_COLOR_2,
    PREDEFINED_COLOR_3,
    PREDEFINED_COLOR_4,
    
} t_cb_current_data;
*/


typedef enum {

    SIERPINSKI_VERTICES,
    
} t_cb_reset_data;
  

typedef enum {
 
    SCENE_GLROTATE_ANGLE,
    SCENE_GLROTATE_X,
    SCENE_GLROTATE_Y,
    SCENE_GLROTATE_Z,
    SCENE_GLTRANSLATE_X,
    SCENE_GLTRANSLATE_Y,
    SCENE_GLTRANSLATE_Z,

    DATA_SIERP_DEPTH, 

    DATA_SIERP_COLOR_R,
    DATA_SIERP_COLOR_G,
    DATA_SIERP_COLOR_B,
    DATA_SIERP_COLOR_A,


    DATA_SIERP_COLOR_FADE,
    DATA_SIERP_COLOR_FADE_TYPE,


    DATA_SIERP_VERTICE_AX,
    DATA_SIERP_VERTICE_AY,
    DATA_SIERP_VERTICE_AZ,
    DATA_SIERP_VERTICE_BX,
    DATA_SIERP_VERTICE_BY,
    DATA_SIERP_VERTICE_BZ,
    DATA_SIERP_VERTICE_CX,
    DATA_SIERP_VERTICE_CY,
    DATA_SIERP_VERTICE_CZ,
    DATA_SIERP_VERTICE_DX,
    DATA_SIERP_VERTICE_DY,
    DATA_SIERP_VERTICE_DZ,

} t_cb_gldisplay_properties;




 

extern GdkGLConfig *glconfig;               // from gl_config.h

 

/*
void cb_chgval_sierp_gl_LookAt          (GtkAdjustment *adjustment, gpointer data);
*/


void cb_app_close ();
void cb_null ();
void cb_hide_widget_itself              (GtkWidget *widget, gpointer data);
gboolean widget_destroy                 (GtkWidget *widget);

 



//~ --------------------------------------------------------------------------------------------------------------------
//~ gl display callbacks
//~ --------------------------------------------------------------------------------------------------------------------
gboolean cb_idle                        (GtkWidget *widget);
void cb_idle_add                        (GtkWidget *widget);
void cb_idle_remove                     (GtkWidget *widget);
gboolean cb_map_event                   (GtkWidget *widget, GdkEvent  *event, gpointer data);
gboolean cb_unmap_event                 (GtkWidget *widget, GdkEvent  *event, gpointer data);
gboolean cb_visibility_notify_event     (GtkWidget *widget, GdkEventVisibility *event, gpointer data);
void cb_toggle_animation                (GtkWidget *widget);
void cb_redisplay_gldisplay             (guint reference);

void cb_reset_data                      (GtkWidget *widget, gpointer data);

   
//~ --------------------------------------------------------------------------------------------------------------------
//~ toggle callbacks
//~ --------------------------------------------------------------------------------------------------------------------
void cb_toggle_widget_display_state     (GtkWidget* widget, gpointer data);

//~ --------------------------------------------------------------------------------------------------------------------
//~ change value callbacks
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_gldisplay_spinbutton     (GtkWidget *spinbutton, gpointer data);
void cb_chgval_gldisplay_adjustment     (GtkAdjustment *adjustment, gpointer data);



/*
void cb_gldisplay_update_display_data (GtkWidget *widget, gpointer data);
*/




#endif // __gtk_callbacks_h
