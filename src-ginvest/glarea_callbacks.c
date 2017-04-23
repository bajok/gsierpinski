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

/*
#include "glarea_callbacks.h"
#include "glgraph.h"
#include "sierpinski.h"
*/



/**************************************
        open gl functions
**************************************/


void redisplay_glgraph (gpointer drawing_area, gpointer data) {
 
    //~ these functions should be called -- first realize, then expose ,,, but there is glulookat in realize

    realize_main_glgraph (drawing_area, data);
    expose_main_glgraph (drawing_area, NULL, data);
 
} 


void redisplay_sierpinski (gpointer drawing_area) {

    realize_sierpinski (drawing_area, NULL);
    expose_event_sierpinski (drawing_area, NULL, NULL);
}
 
  

//~ --------------------------------------------------------------------------------------------------------------------
//~ main glgraph widget functions
//~ --------------------------------------------------------------------------------------------------------------------

gboolean expose_main_glgraph (GtkWidget *widget, GdkEventExpose *event, gpointer data) {

    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW (DEBUG_GL, "expose_main_glgraph", " ")
    #endif
    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
            return FALSE;

    // prototype:  glgraph.h
    glgraph_draw_main_glgraph       (gldrawable, (gpointer) data);
    gdk_gl_drawable_gl_end          (gldrawable);
    return TRUE;
}
 

void realize_main_glgraph (GtkWidget *widget, gpointer data) {

    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW (DEBUG_GL, "realize_main_glgraph", " ")
    #endif
    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
            return;

    glViewport (0, 0, widget->allocation.width, widget->allocation.height);

    // prototype:  glgraph.h
    glgraph_realize_main_gl_graph   (widget, data);
    gdk_gl_drawable_gl_end          (gldrawable);
}
 

gboolean configure_main_glgraph (GtkWidget *widget, GdkEventConfigure *event, gpointer data) {

    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW (DEBUG_GL, "configure_main_glgraph", " ")
    #endif
    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    /*** OpenGL BEGIN ***/
    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
            return FALSE;

    glViewport (0, 0, widget->allocation.width, widget->allocation.height);

    gdk_gl_drawable_gl_end (gldrawable);
    /*** OpenGL END ***/

    return TRUE;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~ sierpinski widget functions
//~ --------------------------------------------------------------------------------------------------------------------

gboolean expose_event_sierpinski (GtkWidget *widget, GdkEventExpose *event, gpointer data) {

    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    /*** OpenGL BEGIN ***/
    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
            return FALSE;

    /* *************** */
    gl_draw_sierpinski (gldrawable);

    gdk_gl_drawable_gl_end (gldrawable);
    /*** OpenGL END ***/

    return TRUE;
}
 


void realize_sierpinski (GtkWidget *widget, gpointer data) {

    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
            return;

    glViewport (0, 0, widget->allocation.width, widget->allocation.height);

    /* *************** */
    gl_realize_sierpinski (widget, data);

    gdk_gl_drawable_gl_end (gldrawable);
}


gboolean configure_event_sierpinski (GtkWidget *widget, GdkEventConfigure *event, gpointer data) {

    GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

    /*** OpenGL BEGIN ***/
    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
            return FALSE;

    glViewport (0, 0, widget->allocation.width, widget->allocation.height);

    gdk_gl_drawable_gl_end (gldrawable);
    /*** OpenGL END ***/

    return TRUE;
}


