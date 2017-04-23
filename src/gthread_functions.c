/*
 *      gthread_functions.c
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
#include <GL/gl.h>
#include <GL/glu.h>


#include "data_structures_init.h"

/*
#include "gtk_callbacks.h"
*/

/*
#include "glarea_callbacks.h"
#include "gtk_frontend_gl_widgets.h"
*/
 
  
//~ ----------------------------------------------------------------------------
//~ threads definitions and vars
//~ ----------------------------------------------------------------------------




/*
gulong dbg_sleep                = 10000 * 1000;     // 10  s
*/

gulong dbg_sleep_check_timer     =  100 * 1000;     // 100 ms
gfloat dbg_sleep_sec            =         10.0;     // 10  s 

 
gpointer *gthread_dbg (gpointer data) {

    #ifdef DEBUG_THREADS
    DEBUG_LOG_FLOW (DEBUG_THREADS, "debug thread attached. ", " - saying hello - ")
    #endif
 
    while (gthreads->debug_thread_runs) {
 
        displaydata->frames_per_second = (gfloat) displaydata->frame_counter / dbg_sleep_sec;
        displaydata->frame_counter = 0;

        // in debug thread there shall be no #ifdef for logging - as debug thread may be attached or not
        #ifdef DEBUG_THREADS
        DEBUG_LOG_FLOW      (DEBUG_THREADS, "gthread_dbg", "")
        DEBUG_LOG_INFO      (DEBUG_THREADS, "displaydata->")
        DEBUG_LOG_INTEGER   (DEBUG_THREADS, " ", "displaydata->animate", displaydata->animate)
        DEBUG_LOG_FLOAT_ARRAY (DEBUG_THREADS, " ", "displaydata->view_quat_diff [4] = ", displaydata->view_quat_diff, 4)
        DEBUG_LOG_FLOAT_ARRAY (DEBUG_THREADS, " ", "displaydata->view_quat [4] = ", displaydata->view_quat, 4)
        DEBUG_LOG_FLOAT     (DEBUG_THREADS, " ", "displaydata->view_scale", displaydata->view_scale)
        DEBUG_LOG_FLOAT     (DEBUG_THREADS, " ", "displaydata->begin_x", displaydata->begin_x)
        DEBUG_LOG_FLOAT     (DEBUG_THREADS, " ", "displaydata->begin_y", displaydata->begin_y)
        DEBUG_LOG_FLOAT     (DEBUG_THREADS, " ", "displaydata->dx", displaydata->dx)
        DEBUG_LOG_FLOAT     (DEBUG_THREADS, " ", "displaydata->dy", displaydata->dy)
        DEBUG_LOG_INFO      (DEBUG_THREADS, "scene->")
        DEBUG_LOG_FLOAT_ARRAY (DEBUG_THREADS, " ", "scene->gltranslate [3] = ", scene->gltranslate, 3)
        DEBUG_LOG_FLOAT_ARRAY (DEBUG_THREADS, " ", "scene->gltranslate [4] = ", scene->glrotate, 4)

        DEBUG_LOG_FLOAT     (DEBUG_THREADS, " ", "displaydata->frames_per_second", displaydata->frames_per_second)
        #endif

        // so wait
  
        gboolean WAIT = TRUE;
 
        gthreads->debug_timer = g_timer_new (); // starts timer
 
        while (WAIT) {

            if (g_timer_elapsed (gthreads->debug_timer, NULL) > dbg_sleep_sec
             || !(gthreads->debug_thread_runs))
                WAIT = FALSE;
 
            g_usleep (dbg_sleep_check_timer);
        }

        g_timer_destroy (gthreads->debug_timer);
    }



    LOG_INFO ("gthread_dbg terminated")
    return NULL;
}

 

/*
    GDK thread!!!!!!!
*/



