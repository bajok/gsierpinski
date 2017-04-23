/*
 *      data_structures_init.h
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


#ifndef __data_structures_init_h_
#define __data_structures_init_h_

#include <glib.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "macros_debug.h"
#include "gthread_functions.h"
 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * main structure for data exchange
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _current_data current_data;

struct _current_data {

    GLfloat  sierpinski_color [4];
    GLuint   sierpinski_depth;

};


#include "gldisplay.h"


//~ --------------------------------------------------------------------------------------------------------------------
//~ * externs
//~ --------------------------------------------------------------------------------------------------------------------

extern current_data               *current;
extern gldisplay_display_data     *displaydata;
extern gldisplay_scene            *scene;  // should contain available planes

extern gthread_refs               *gthreads;
 

/*
extern double sierp_gl_LookAt [3][3];
*/


//~ --------------------------------------------------------------------------------------------------------------------
//~ * functions
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_gl_structures ();
gboolean initialize_current_data ();
gboolean initialize_debug_data ();


gboolean    *initialize_gboolean_array_null (guint size);
guint        gboolean_array_get_enabled (gboolean *array, guint size);


void finalize_struct (gpointer pointer);
void finalize_struct_array (gpointer *pointer, gint array_size);


#endif //__data_structures_init_h_
