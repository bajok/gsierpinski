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
//~  cb_redisplay_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------

void cb_redisplay_gldisplay (guint reference) {

    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW      (DEBUG_GL, "cb_redisplay_gldisplay", " ")
        DEBUG_LOG_INTEGER   (DEBUG_GL, " ", "reference", reference)
    #endif
 
    
    redisplay_gldisplay ((gpointer) gl_area_main, (gpointer) displaydata, (gpointer) current);
}


//~ --------------------------------------------------------------------------------------------------------------------
gboolean cb_idle (GtkWidget *widget)
{
    /* Invalidate the whole window. */
    gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);

    /* Update synchronously. */
    gdk_window_process_updates (widget->window, FALSE);

    return TRUE;
}

static guint idle_id = 0;

//~ --------------------------------------------------------------------------------------------------------------------
void cb_idle_add (GtkWidget *widget)
{
  if (idle_id == 0) {
      idle_id = g_idle_add_full (GDK_PRIORITY_REDRAW,
                                 (GSourceFunc) cb_idle,
                                 widget,
                                 NULL);
    }
}
  
//~ --------------------------------------------------------------------------------------------------------------------
void cb_idle_remove (GtkWidget *widget) {

    if (idle_id != 0) {
        g_source_remove (idle_id);
        idle_id = 0;
    }
}

//~ --------------------------------------------------------------------------------------------------------------------
gboolean cb_map_event (GtkWidget *widget, GdkEvent  *event, gpointer   data) {

    if (displaydata->animate)
        cb_idle_add (widget);

    return TRUE;
}

//~ --------------------------------------------------------------------------------------------------------------------
gboolean cb_unmap_event (GtkWidget *widget, GdkEvent  *event, gpointer data) {

    cb_idle_remove (widget);
    return TRUE;
}

//~ --------------------------------------------------------------------------------------------------------------------
gboolean cb_visibility_notify_event (GtkWidget *widget, GdkEventVisibility *event, gpointer data) {

    if (displaydata->animate) {

        if (event->state == GDK_VISIBILITY_FULLY_OBSCURED)
            cb_idle_remove (widget);
        else
            cb_idle_add (widget);
    }
    return TRUE;
}
 
   
 
//~ --------------------------------------------------------------------------------------------------------------------
/* Toggle animation.*/
void cb_toggle_animation (GtkWidget *widget)
{
    displaydata->animate = !(displaydata->animate);

    if (displaydata->animate) {
        cb_idle_add (widget);
    }
    else {
        cb_idle_remove (widget);
        displaydata->view_quat_diff[0] = 0.0;
        displaydata->view_quat_diff[1] = 0.0;
        displaydata->view_quat_diff[2] = 0.0;
        displaydata->view_quat_diff[3] = 1.0;
        gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);
    }
}

//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_reset_data
//~ --------------------------------------------------------------------------------------------------------------------

void cb_reset_data (GtkWidget *widget, gpointer data) {

    t_cb_reset_data index = GPOINTER_TO_INT (data);

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_reset_data", " ")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
    #endif 
 
    switch (index) {
 
        case    SIERPINSKI_VERTICES:
            displaydata->sierpinski_vertice_A [0] = -1.000;
            displaydata->sierpinski_vertice_A [1] = -1.000;
            displaydata->sierpinski_vertice_A [2] = -1.000;
            displaydata->sierpinski_vertice_B [0] =  1.000;
            displaydata->sierpinski_vertice_B [1] = -1.000;
            displaydata->sierpinski_vertice_B [2] = -1.000;
            displaydata->sierpinski_vertice_C [0] =  0.000;
            displaydata->sierpinski_vertice_C [1] =  0.732;
            displaydata->sierpinski_vertice_C [2] = -1.000;
            displaydata->sierpinski_vertice_D [0] =  0.000;
            displaydata->sierpinski_vertice_D [1] = -0.423;
            displaydata->sierpinski_vertice_D [2] =  0.633;
            break;
 
        default: 
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_reset_data", "no callback defined")
            #endif
            break;
    }
  
    cb_redisplay_gldisplay (0);
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
        case MAIN_WINDOW_SETTINGS:
            if (button_active_state == TRUE)
                gtk_widget_show_all (GTK_WIDGET (UI->main_window_settings));
            else
                gtk_widget_hide_all (GTK_WIDGET (UI->main_window_settings));
            break;
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_toggle_widget_display_state", "no such widget!")
            #endif
            break;
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
//~  cb_chgval_gldisplay_properties
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_gldisplay_spinbutton (GtkWidget *spinbutton, gpointer data) {

    t_cb_gldisplay_properties index = GPOINTER_TO_INT (data);
    gdouble get_value = gtk_spin_button_get_value (spinbutton);
 
    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_chgval_gldisplay_spinbutton", "gldisplay properties value change")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
        DEBUG_LOG_FLOAT     (DEBUG_GTK, " ", "get_value", get_value)
    #endif 
 
    switch (index) {
 
        case    DATA_SIERP_DEPTH:
            displaydata->sierpinski_depth = (guint) get_value;
            break;
        case    DATA_SIERP_COLOR_R:
            displaydata->sierpinski_color [0] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_COLOR_G:
            displaydata->sierpinski_color [1] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_COLOR_B:
            displaydata->sierpinski_color [2] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_COLOR_A:
            displaydata->sierpinski_color [3] = (GLfloat) get_value;
            break;

        case    DATA_SIERP_COLOR_FADE:
            displaydata->sierpinski_color_fade = (GLfloat) get_value;
            break;
        case    DATA_SIERP_COLOR_FADE_TYPE:
            displaydata->sierpinski_color_fade_type = (GLuint) get_value;
            break;
  
 

 
  
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_chgval_gldisplay_spinbutton", "no callback defined")
            #endif
            break;
    }
 
 
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
    cb_redisplay_gldisplay (0);
}
 
   
  

//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_chgval_gldisplay_adjustment
//~ --------------------------------------------------------------------------------------------------------------------

void cb_chgval_gldisplay_adjustment (GtkAdjustment *adjustment, gpointer data) {

    t_cb_gldisplay_properties index = GPOINTER_TO_INT (data);
    gdouble get_value = gtk_adjustment_get_value (adjustment);
 
    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_chgval_gldisplay_adjustment", "gldisplay properties value change")
        DEBUG_LOG_INTEGER   (DEBUG_GTK, " ", "index", index)
        DEBUG_LOG_FLOAT     (DEBUG_GTK, " ", "get_value", get_value)
    #endif 
 
    switch (index) {
 
        case    SCENE_GLTRANSLATE_X:
            scene->gltranslate [0] = get_value;
            break;
        case    SCENE_GLTRANSLATE_Y:
            scene->gltranslate [1] = get_value;
            break;
        case    SCENE_GLTRANSLATE_Z:
            scene->gltranslate [2] = get_value;
            break;

        case    SCENE_GLROTATE_ANGLE:
            scene->glrotate [0] = get_value;
            break;
        case    SCENE_GLROTATE_X:
            scene->glrotate [1] = get_value;
            break;
        case    SCENE_GLROTATE_Y:
            scene->glrotate [2] = get_value;
            break;
        case    SCENE_GLROTATE_Z:
            scene->glrotate [3] = get_value;
            break;

         case    DATA_SIERP_VERTICE_AX:
            displaydata->sierpinski_vertice_A [0] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_AY:
            displaydata->sierpinski_vertice_A [1] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_AZ:
            displaydata->sierpinski_vertice_A [2] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_BX:
            displaydata->sierpinski_vertice_B [0] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_BY:
            displaydata->sierpinski_vertice_B [1] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_BZ:
            displaydata->sierpinski_vertice_B [2] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_CX:
            displaydata->sierpinski_vertice_C [0] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_CY:
            displaydata->sierpinski_vertice_C [1] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_CZ:
            displaydata->sierpinski_vertice_C [2] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_DX:
            displaydata->sierpinski_vertice_D [0] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_DY:
            displaydata->sierpinski_vertice_D [1] = (GLfloat) get_value;
            break;
        case    DATA_SIERP_VERTICE_DZ:
            displaydata->sierpinski_vertice_D [2] = (GLfloat) get_value;
            break;


  
        default:
            #ifdef DEBUG_GTK
                DEBUG_LOG_ERROR (DEBUG_GTK, "cb_chgval_gldisplay_adjustment", "no callback defined")
            #endif
            break;
    }
 
 
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
    cb_redisplay_gldisplay (0);
}
 
  
 
// need call


//
// callback connected without a call as data is initialized here !!!!!!!!!

//~ --------------------------------------------------------------------------------------------------------------------
//~  cb_gldisplay_update_display_data
//~ --------------------------------------------------------------------------------------------------------------------

/*
void cb_gldisplay_update_display_data (GtkWidget *widget, gpointer data) {

    #ifdef DEBUG_GTK
        DEBUG_LOG_FLOW      (DEBUG_GTK, "cb_gldisplay_update_display_data", "gldisplay display data update")
        DEBUG_LOG_POINTER   (DEBUG_GTK, "(gldisplay_display_data *)", "displaydata", displaydata)
        DEBUG_LOG_POINTER   (DEBUG_GTK, "(gldisplay_display_data *)", "current", current)
    #endif 

  
    // prototype:  structures_gldisplay.h
    gldisplay_update_display_data (displaydata, current);
 
    // prototype:  glarea_callbacks.h
    // flow:       glarea_callbacks.h -> gldisplay.h -> gldisplay_drawing_procedures.h


    // BOOLEAN: ALWAYS | ON DEMAND
    redisplay_gldisplay (gl_area_main, (gpointer) displaydata);

}
*/

   
 
//~ --------------------------------------------------------------------------------------------------------------------
//~  miscellaneous callbacks -- DEPRECATED
//~ --------------------------------------------------------------------------------------------------------------------

/*
void cb_chgval_sierp_gl_LookAt (GtkAdjustment *adjustment, gpointer data) {

    gint index = GPOINTER_TO_INT (data);
    sierp_gl_LookAt [(index-1)/3][(index-1)%3] = gtk_adjustment_get_value (GTK_ADJUSTMENT (adjustment));
    redisplay_sierpinski (gl_area_sierpinski);
//     realize (gl_area, NULL);
}
*/

