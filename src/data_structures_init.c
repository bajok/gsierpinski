/*
 *      data_structures_init.c
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


#include <glib.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include "data_structures_init.h"



//~ --------------------------------------------------------------------------------------------------------------------
//~ * initializing memory
//~ --------------------------------------------------------------------------------------------------------------------

current_data               *current;

gldisplay_display_data     *displaydata;
gldisplay_scene            *scene;
 
gthread_refs               *gthreads;
 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * initializing gl_structures
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_gl_structures () {
 
    /*
     * scene
     */
    scene = g_malloc0 (sizeof (gldisplay_scene));
    if (scene == NULL) {
        LOG_ERROR ("gldisplay_scene *scene: memory could not be allocated")
        return FALSE;
    } else {

        scene->Z_layer = 0.00; // higher is further

        scene->dimensions [0] = -0.01;
        scene->dimensions [1] = 1.01;
        scene->dimensions [2] = -0.10;
        scene->dimensions [3] = 1.01;

        scene->color [0] = 0.125;
        scene->color [1] = 0.025;
        scene->color [2] = 0.005;
        scene->color [3] = 1.000;

        scene->clearcolor [0] = 0.125;
        scene->clearcolor [1] = 0.025;
        scene->clearcolor [2] = 0.005;
        scene->clearcolor [3] = 0.500;

        scene->backgroundcolor [0] = 0.525;
        scene->backgroundcolor [1] = 0.025;
        scene->backgroundcolor [2] = 0.005;
        scene->backgroundcolor [3] = 0.800;

        scene->gltranslate [0] = 0.0;
        scene->gltranslate [1] = 0.0;
        scene->gltranslate [2] = -7.0;


/*
        scene->glrotate [0] = 20.0;
        scene->glrotate [1] = 60.0;
        scene->glrotate [2] = -120.0;
        scene->glrotate [3] = 60.0;
*/
        scene->glrotate [0] = 0.0;
        scene->glrotate [1] = 0.0;
        scene->glrotate [2] = 0.0;
        scene->glrotate [3] = 0.0;

    }
  
  
    displaydata = g_malloc0 (sizeof (gldisplay_display_data));
    if (displaydata == NULL) {
        LOG_ERROR ("gldisplay_display_data *displaydata: memory could not be allocated")
        return FALSE;
    } else { 
        displaydata->sierpinski_color           = (GLfloat *) g_malloc0 ((sizeof (GLfloat)) * 4);
        displaydata->sierpinski_color [0] = 0.1;
        displaydata->sierpinski_color [1] = 0.9;
        displaydata->sierpinski_color [2] = 0.5;
        displaydata->sierpinski_color [3] = 1.0;

        displaydata->sierpinski_color_fade = 0.44;
 
/*
        displaydata->sierpinski_color_fade      = (GLfloat *) g_malloc0 ((sizeof (GLfloat)) * 4);
        displaydata->sierpinski_color_fade [0] = 0.950;
        displaydata->sierpinski_color_fade [1] = 0.980;
        displaydata->sierpinski_color_fade [2] = 0.995;
        displaydata->sierpinski_color_fade [3] = 1.0;
*/
  
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
 
        displaydata->sierpinski_depth = 5;

        displaydata->animate = FALSE;

    //
    // init view

        displaydata->view_quat [0] = 0.0;
        displaydata->view_quat [1] = 0.0;
        displaydata->view_quat [2] = 0.0;
        displaydata->view_quat [3] = 1.0;
        displaydata->view_quat_diff [0] = 0.0;
        displaydata->view_quat_diff [1] = 0.0;
        displaydata->view_quat_diff [2] = 0.0;
        displaydata->view_quat_diff [3] = 1.0;
        displaydata->view_scale = 1.0;
        displaydata->begin_x = 0.0;
        displaydata->begin_y = 0.0; 
        displaydata->dx = 0.0;
        displaydata->dy = 0.0;

        displaydata->display_width = 1.0;
        displaydata->display_height = 1.0;
 

        displaydata->frame_counter = 0;
        displaydata->frames_per_second = 0;


 
    }

    return TRUE;
}

 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * gboolean initialize_current_data ()
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_current_data () {

    current = g_malloc0 (sizeof (current_data));
    if (current == NULL) {
        LOG_ERROR ("current_data *current: memory could not be allocated")
        return FALSE;
    }

    current->sierpinski_color [0] = 0.0;
    current->sierpinski_color [1] = 0.0;
    current->sierpinski_color [2] = 1.0;
    current->sierpinski_color [3] = 0.0;
    
    current->sierpinski_depth = 4;

    return TRUE;
}

//~ --------------------------------------------------------------------------------------------------------------------
//~ * miscellaneous
//~ --------------------------------------------------------------------------------------------------------------------

gboolean *initialize_gboolean_array_null (guint size) {

    gboolean *array = g_malloc0 ((sizeof (gboolean)) * size);
    return array;
}

guint gboolean_array_get_enabled (gboolean *array, guint size) {

    guint counter = 0;
    for (guint iter = 0; iter < size; iter++)
        if (array [iter] == TRUE) counter++;
    return counter;
}
 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * freeing memory
//~ --------------------------------------------------------------------------------------------------------------------

void finalize_struct (gpointer pointer) {   // gint t_struct_type  if (t_struct_type == gldisplay_PLANE) ....
    #ifdef DEBUG_MEM_ALLOC
    DEBUG_LOG_INTEGER (DEBUG_MEM_ALLOC, "finalize_struct", \
                                         "memory freed for: GPOINTER_TO_INT (%d)", GPOINTER_TO_INT (pointer))
    #endif
    g_free (pointer);
}


void finalize_struct_array (gpointer *pointer, gint array_size) {
    for (gint i = 0; i < array_size; i++) {
        #ifdef DEBUG_MEM_ALLOC
/*
        DEBUG_LOG_INTEGER (DEBUG_MEM_ALLOC, "finalize_struct", \
                                            "memory freed for: GPOINTER_TO_INT (%d)", GPOINTER_TO_INT (pointer))
*/
        #endif
        g_free (pointer [i]);
    }
/*
    g_prnt ("memory freed for array of structures: GPOINTER_TO_INT (%p) = %d\n", pointer, GPOINTER_TO_INT (pointer));
*/
}
