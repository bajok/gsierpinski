/*
 *      glarea_callbacks.c
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
#include "gtk_callbacks.h"
#include "data_structures_init.h"
#include "trackball.h"


/**************************************
        open gl functions
**************************************/
 
 
void redisplay_gldisplay (gpointer drawing_area, gpointer data, gpointer params) {

    // this function looks like it does not need to log anything 
    realize_main_gldisplay (drawing_area, data);
    expose_main_gldisplay (drawing_area, NULL, data);
} 
 

//
// all below functions are used in:      gtk_frontend_gl_widgets.c
//
//                                       as callbacks


//
// it does what it means, however it must be called within gdk_gl_drawable_gl_begin and end

    
//~ --------------------------------------------------------------------------------------------------------------------
//~  realize_main_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------

void realize_main_gldisplay (GtkWidget *widget, gpointer data) {

    #ifdef DEBUG_GL_CB
    DEBUG_LOG_FLOW (DEBUG_GL_CB, "realize_main_gldisplay", " ")
    #endif

    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
            return;

    //~ ---------------------
    //~ setting scene begin
    //~ ---------------------
    // prototype:  gldisplay.h 
    gldisplay_realize_main_gldisplay   ((gldisplay_display_data *) data); // prepare GL lists
  
    //~ ---------------------
    //~ setting scene end
    //~ ---------------------
   
    gdk_gl_drawable_gl_end          (gldrawable);

}
 
  
//~ --------------------------------------------------------------------------------------------------------------------
//~      configure_main_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------
 
gboolean configure_main_gldisplay (GtkWidget *widget, GdkEventConfigure *event, gpointer data) {

    #ifdef DEBUG_GL_CB
    DEBUG_LOG_FLOW (DEBUG_GL_CB, "configure_main_gldisplay", " ")
    #endif

    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    GLfloat width = widget->allocation.width;
    GLfloat height = widget->allocation.height;
    GLfloat aspect;

    displaydata->display_width             = width;
    displaydata->display_height            = height;

    /*** OpenGL BEGIN ***/
    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
    return FALSE;

    glViewport (0, 0, width, height);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if (width > height) {
        aspect = width / height;
        glFrustum (-aspect, aspect, -1.0, 1.0, 5.0, 60.0);
    }
    else {
        aspect = height / width;
        glFrustum (-1.0, 1.0, -aspect, aspect, 5.0, 60.0);
    }

    glMatrixMode (GL_MODELVIEW);
 
    gdk_gl_drawable_gl_end (gldrawable);
    /*** OpenGL END ***/

    #ifdef DEBUG_GL_CB
    DEBUG_LOG_FLOW (DEBUG_GL_CB, "configure_main_gldisplay", " display configured ")
    #endif
    
    return TRUE;
}

   
//~ --------------------------------------------------------------------------------------------------------------------
//~      expose_main_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------

gboolean expose_main_gldisplay (GtkWidget *widget, GdkEventExpose *event, gpointer data) {

    #ifdef DEBUG_GL_CB
    DEBUG_LOG_FLOW      (DEBUG_GL_CB, "expose_main_gldisplay", " ")
    #endif

    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
    return FALSE;
 
    //~ ---------------------
    //~ drawing begin
    //~ ---------------------
    // prototype:  gldisplay.h  
  
    gldisplay_expose_main_gldisplay       ((gldisplay_display_data *) data); // call GL lists
 
    if (gdk_gl_drawable_is_double_buffered (gldrawable))
            gdk_gl_drawable_swap_buffers (gldrawable);
    else
            glFlush ();
 
    //~ ---------------------
    //~ drawing end
    //~ ---------------------

    gdk_gl_drawable_gl_end          (gldrawable);

/*
    #ifdef DEBUG_GL
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_POINTER   (DEBUG_GL, " ", "data", data)
    #endif
    #endif
*/

    return TRUE;
}

  
//~ --------------------------------------------------------------------------------------------------------------------
//~      button_press_main_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------

gboolean button_press_main_gldisplay (GtkWidget *widget, GdkEventButton *event, gpointer data) {

    gldisplay_display_data *dispdata = (gldisplay_display_data *) data;

    #ifdef DEBUG_GL_CB
    DEBUG_LOG_FLOW      (DEBUG_GL_CB, "button_press_main_gldisplay", " ")
    #endif
  
    if (dispdata->animate) {
        if (event->button == 1)
            cb_toggle_animation (widget);
    }
    else {
        dispdata->view_quat_diff[0] = 0.0;
        dispdata->view_quat_diff[1] = 0.0;
        dispdata->view_quat_diff[2] = 0.0;
        dispdata->view_quat_diff[3] = 1.0;
    }
 
    dispdata->begin_x = event->x / CBGL_MOUSE_MOVE_RATIO;
    dispdata->begin_y = event->y / CBGL_MOUSE_MOVE_RATIO;
 
/*
    #ifdef DEBUG_GL
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_POINTER   (DEBUG_GL, " ", "dispdata", dispdata)
    #endif
    #endif
*/

    return FALSE;
} 
   
//~ --------------------------------------------------------------------------------------------------------------------
//~      button_release_main_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------
gboolean button_release_main_gldisplay (GtkWidget *widget, GdkEventButton *event, gpointer data) {
    
    gldisplay_display_data *dispdata = (gldisplay_display_data *) data;

    #ifdef DEBUG_GL_CB
    DEBUG_LOG_FLOW      (DEBUG_GL_CB, "button_release_main_gldisplay", " ")
    #endif
 
    if (!(dispdata->animate)) {

        if (event->button == 1 &&
            (((dispdata->dx)*(dispdata->dx) + (dispdata->dy)*(dispdata->dy)) > ANIMATE_THRESHOLD))
        cb_toggle_animation (widget);
    }
 
    dispdata->dx = 0.0;
    dispdata->dy = 0.0;

/*
    #ifdef DEBUG_GL
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_POINTER   (DEBUG_GL, " ", "dispdata", dispdata)
    #endif
    #endif
*/

    return FALSE;
}   
      
//~ --------------------------------------------------------------------------------------------------------------------
//~      motion_notify_main_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------
gboolean motion_notify_main_gldisplay (GtkWidget *widget, GdkEventMotion *event, gpointer data) {
    
    gldisplay_display_data *dispdata = (gldisplay_display_data *) data;

    gfloat width                = dispdata->display_width;
    gfloat height               = dispdata->display_height;
    gfloat x                    = event->x / CBGL_MOUSE_MOVE_RATIO;
    gfloat y                    = event->y / CBGL_MOUSE_MOVE_RATIO;
    gfloat trackball_data [4]   = {0, 0, 0, 0};

    gboolean redraw = FALSE;

    #ifdef DEBUG_GL_CB
    DEBUG_LOG_FLOW      (DEBUG_GL_CB, "motion_notify_main_gldisplay", " ")
    #endif
  

    // Rotation.
    if (event->state & GDK_BUTTON1_MASK) {

        trackball_data [0] = (2.0 * (dispdata->begin_x) - width) / width;
        trackball_data [1] = (height - 2.0 * (dispdata->begin_y)) / height;
        trackball_data [2] = (2.0 * x - width) / width;
        trackball_data [3] = (height - 2.0 * y) / height;

        // change to vector function ?
        trackball (dispdata->view_quat_diff,
                   trackball_data [0], trackball_data [1], trackball_data [2], trackball_data [3]);

/*
                     (2.0 * (dispdata->begin_x) - width) / width,
                     (height - 2.0 * (dispdata->begin_y)) / height,
                     (2.0 * x - width) / width,
                     (height - 2.0 * y) / height);
*/
 
/*
                     (0.2 * (dispdata->begin_x) - w) / w,
                     (h - 0.2 * (dispdata->begin_y)) / h,
                     (0.2 * x - w) / w,
                     (h - 0.2 * y) / h);
*/
 
 
        dispdata->dx = x - dispdata->begin_x;
        dispdata->dy = y - dispdata->begin_y;

        redraw = TRUE;
    }

    // Scaling
    if (event->state & GDK_BUTTON2_MASK) {
        
        dispdata->view_scale = dispdata->view_scale * (1.0 + (y - dispdata->begin_y) / height);
        if (dispdata->view_scale > VIEW_SCALE_MAX)
            dispdata->view_scale = VIEW_SCALE_MAX;
        else
        if (dispdata->view_scale < VIEW_SCALE_MIN)
            dispdata->view_scale = VIEW_SCALE_MIN;
        redraw = TRUE;
    }

    dispdata->begin_x = x;
    dispdata->begin_y = y;

    #ifdef DEBUG_GL_CB
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    // DEBUG_LOG_POINTER   (DEBUG_GL, " ", "dispdata", dispdata)
    DEBUG_LOG_INTEGER       (DEBUG_GL_CB, " ", "widget->allocation.width ", width)
    DEBUG_LOG_INTEGER       (DEBUG_GL_CB, " ", "widget->allocation.height ", height)
    DEBUG_LOG_INTEGER       (DEBUG_GL_CB, " ", "displaydata->display_width ", displaydata->display_width)
    DEBUG_LOG_INTEGER       (DEBUG_GL_CB, " ", "displaydata->display_height ", displaydata->display_height)
    DEBUG_LOG_INTEGER       (DEBUG_GL_CB, " ", "event->x", x)
    DEBUG_LOG_INTEGER       (DEBUG_GL_CB, " ", "event->y", y)
    DEBUG_LOG_FLOAT_ARRAY   (DEBUG_GL_CB, " ", "trackball_data [4] = ", trackball_data, 4)
    #endif
    #endif

    if (redraw && !(dispdata->animate))
    gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);
  
    return TRUE;
}



