/*
 *      gldisplay_drawing_functions.c
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


#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <gtk/gtkgl.h>
#include "data_structures_init.h"


/*
static GLvoid GLvoid_draw_quad_fixed (GLfloat *color,
                                      GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2, GLdouble Z);

static GLuint GLuint_draw_plane (GLsizei range, GLfloat *color,
                                 GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2, GLdouble Z);
*/


static GLuint gl_sierpinski_tetrahedron (GLsizei range, gldisplay_display_data *data);




//~ --------------------------------------------------------------------------------------------------------------------
//~ creating and calling lists 
//~ --------------------------------------------------------------------------------------------------------------------

void gldisplay_drawfunc_ready_buffer (gldisplay_display_data *data) {

    // 
    // creating lists 

    GLsizei glsizei_range = (GLuint) GLDISPLAY_LISTS;


/*
    #ifdef DEBUG_GL
    DEBUG_LOG_FLOW    (DEBUG_GL, "gldisplay_ready_buffer", " . ")
    DEBUG_LOG_POINTER (DEBUG_GL, " ", "data", data)
    DEBUG_LOG_INTEGER (DEBUG_GL, " ", "elements", elements)
    #endif
*/


/*
    gldisplay [1] = GLuint_draw_graph_plane      (glsizei_range, plane->color,
                                                               plane->dimensions [0],
                                                               plane->dimensions [1],
                                                               plane->dimensions [2],
                                                               plane->dimensions [3],
                                                               plane->Z_layer);
*/
  
    data->gldisplay [0] = gl_sierpinski_tetrahedron (glsizei_range, data); // sierpinski.c
   


}
    
    
void gldisplay_drawfunc_call_buffer (gldisplay_display_data *data) {

    //
    // calling lists

    for (GLuint iter = 0; iter < GLDISPLAY_LISTS; iter++) {

        glCallList (data->gldisplay [iter]);
/*
        glDeleteLists (data->gldisplay [iter], 1);
*/
    }
}

void gldisplay_drawfunc_delete_buffer (gldisplay_display_data *data) {

    //
    // calling lists

    for (GLuint iter = 0; iter < GLDISPLAY_LISTS; iter++) {

/*
        glCallList (data->gldisplay [iter]);
*/
        glDeleteLists (data->gldisplay [iter], 1);
    }
}

     

//~ --------------------------------------------------------------------------------------------------------------------
//~ draw sierpinski
//~ --------------------------------------------------------------------------------------------------------------------

GLuint gl_sierpinski_tetrahedron (GLsizei range, gldisplay_display_data *data) {

    GLuint list = glGenLists (range);

/*
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, data->sierpinski_color);
*/


/*
    #ifdef DEBUG_GL
    DEBUG_LOG_FLOW    (DEBUG_GL, "gl_sierpinski_tetrahedron", "drawing object")
    DEBUG_LOG_POINTER (DEBUG_GL, " ", "data", data)
    DEBUG_LOG_FLOAT_ARRAY (DEBUG_GL," ","data->sierpinski_color [4] = ",data->sierpinski_color,4)
    DEBUG_LOG_INTEGER (DEBUG_GL, " ", "data->sierpinski_depth", data->sierpinski_depth)
    #endif
*/



    glNewList (list, GL_COMPILE);
        glPushMatrix ();
/*
        glScalef (1.2, 1.2, 1.2);
*/
 
        /* drawing sierpinski - vertices: A (x1, y1, z1), B, C, D. */
        draw_sierpinski (
            data->sierpinski_vertice_A,
            data->sierpinski_vertice_B,
            data->sierpinski_vertice_C,
            data->sierpinski_vertice_D,
            data->sierpinski_color, data->sierpinski_depth);

        glPopMatrix ();
    glEndList ();
   
    return list;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~ GLvoid_draw_quad_fixed
//~ --------------------------------------------------------------------------------------------------------------------

static GLvoid GLvoid_draw_quad_fixed (GLfloat *color,
                                      GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2, GLdouble Z) {

    glBegin (GL_QUADS);
        glColor4fv (color);
        glVertex3f (x1, y1, Z);
        glVertex3f (x2, y1, Z);
        glVertex3f (x2, y2, Z);
        glVertex3f (x1, y2, Z);
    glEnd();
}


 
//~ --------------------------------------------------------------------------------------------------------------------
//~ GLuint_draw_plane
//~ --------------------------------------------------------------------------------------------------------------------

static GLuint GLuint_draw_plane (GLsizei range, GLfloat *color,
                                 GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2, GLdouble Z) {

    GLuint list = glGenLists (range);
    glNewList (list, GL_COMPILE);

        GLvoid_draw_quad_fixed (color, x1, x2, y1, y2, Z);

    glEndList ();

    return list;
}



