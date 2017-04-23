/*
 *      glgraph_drawing_functions.c
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
#include "glgraph.h"
*/
 

/*
GLvoid functions shall be in primitives.c
*/

//~ --------------------------------------------------------------------------------------------------------------------
//~ basic drawing procedures
//~ --------------------------------------------------------------------------------------------------------------------

/*
static void gl_draw_quad_z (GLfloat *color, GLfloat x, GLfloat y, GLfloat z, GLfloat side, GLfloat angle) {

    GLfloat x1, x2, y1, y2;
    x1 = x - (((side)/2.0) * sin (angle));
    x2 = x + (((side)/2.0) * sin (angle));
    y1 = y - (((side)/2.0) * sin (angle));
    y2 = y + (((side)/2.0) * sin (angle));

    glBegin(GL_POLYGON);
        glColor4fv (color);
        glVertex3f (x1, y2, z);
        glVertex3f (x1, y1, z);
        glVertex3f (x2, y1, z);
        glVertex3f (x2, y2, z);
    glEnd();
}
*/



/*
circle:

glBegin(GL_LINE_STRIP);
for (u32 i = 0; i < 32; i++)
{
    f32 t = (f32)i / (32.0f - 1.0f);
    f32 x = cosf(t*kPi)*4.0f;
    f32 y = sinf(t*kPi)*4.0f;

    glVertex2f(x, y);
}
glEnd();
*/

const GLfloat kPi = 3.14;

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
//~ GLvoid_draw_thick_connected_lines
//~ --------------------------------------------------------------------------------------------------------------------

static GLvoid GLvoid_draw_thick_connected_lines (GLfloat *color, GLfloat *Y_data, GLuint data_size, GLfloat Z) {

/*
    GLfloat color__1 [4];
    color__1 [0] = 0.5;
    color__1 [1] = 0.5;
    color__1 [2] = 0.5;
    color__1 [3] = 0.5;
*/

 

    GLfloat X_MAX = data_size;
/*
    GLfloat X_MIN = 0;
*/

    for (GLuint iter = 1; iter < X_MAX; iter++) {

        GLfloat X1 = (GLfloat) (iter-1) / X_MAX;
        GLfloat X2 = (GLfloat) iter / X_MAX;
        GLfloat Y1 = (GLfloat) Y_data [iter-1] / 10;
        GLfloat Y2 = (GLfloat) Y_data [iter] / 10;

        GLfloat thick = properties->line_thickness;

        glBegin (GL_QUADS);
            glColor4fv (color);
            glVertex3f (X1 - thick, Y1 - thick, Z);
            glVertex3f (X2 + thick, Y2 - thick, Z);
            glVertex3f (X2 + thick, Y2 + thick, Z);
            glVertex3f (X1 - thick, Y1 + thick, Z);
        glEnd();

    }


}



 


/*
static GLvoid GLvoid_draw_line_strip (GLuint label_id) {

    glBegin (GL_LINE_STRIP);

        GLfloat y = 1;

        for (GLuint iter = 0; iter < NEWCONNECT_MAX_DAILY_LISTINGS; iter++) {

            GLfloat t = (GLdouble) iter / (32.0f - 1.0f);
            GLfloat y = sinf(t*kPi)*4.0f;
            glVertex2f (newconnect->daily [iter]->listed[label_id]->v_close, y);
        }
    glEnd();
}
*/

/*
static GLvoid GLvoid_draw_line_strip (GLuint label_id, GLuint start, GLuint end) {

    glBegin (GL_QUADS);
        glColor4fv (color);
        glVertex3f (x1, y1, Z);
        glVertex3f (x2, y1, Z);
        glVertex3f (x2, y2, Z);
        glVertex3f (x1, y2, Z);
    glEnd();

}
*/

/*
static GLvoid GLvoid_draw_circle () {

    glBegin (GL_LINE_STRIP);
        for (GLuint i = 0; i < 32; i++) {

            GLfloat t = (GLdouble) i / (32.0f - 1.0f);
            GLfloat x = cosf(t*kPi)*4.0f;
            GLfloat y = sinf(t*kPi)*4.0f;

            glVertex2f (x, y);
        }
    glEnd();
}
*/


//~ --------------------------------------------------------------------------------------------------------------------
//~ main display functions
//~ --------------------------------------------------------------------------------------------------------------------

//~ --------------------------------------------------------------------------------------------------------------------
//~ GLuint_draw_graph_plane
//~ --------------------------------------------------------------------------------------------------------------------

GLuint GLuint_draw_graph_plane (GLsizei range, GLfloat *color,
                                       GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2, GLdouble Z) {

    GLuint list = glGenLists (range);
    glNewList (list, GL_COMPILE);

    GLvoid_draw_quad_fixed (color, x1, x2, y1, y2, Z);

/*
    GLfloat color__1 [4];
    color__1 [0] = color [0] - 0.2;
    color__1 [1] = color [1] - 0.2;
    color__1 [2] = color [2] - 0.2;
    color__1 [3] = color [3] - 0.2;

    GLvoid_draw_quad_fixed (color__1, x1, x2, y1, y2, Z - (properties->plane_thickness));
*/


/*
        (( GLvoid_draw_quad_fixed  X  6 to make thin  prostopadloscian (cube)
*/

    glEndList ();

    return list;
}
  
 
//~ --------------------------------------------------------------------------------------------------------------------
//~ GLuint_draw_graph_background
//~ --------------------------------------------------------------------------------------------------------------------

GLuint GLuint_draw_graph_background (GLsizei range, GLfloat *color,
                                     GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2, GLdouble Z) {

    GLuint list = glGenLists (range);
    glNewList (list, GL_COMPILE);

        GLvoid_draw_quad_fixed (color, x1, x2, y1, y2, Z);

    glEndList ();

    return list;
}

//~ --------------------------------------------------------------------------------------------------------------------
//~ GLuint_draw_share_graph_std
//~ --------------------------------------------------------------------------------------------------------------------
/*
 * standard share draw - assumes X coord most left is 0 and most right is 1, same with Y
 */
GLuint GLuint_draw_share_graph_std   (GLsizei range, GLfloat *color,
                                      GLfloat *Y_data, GLuint data_size, GLfloat Z) {

    GLuint list = glGenLists (range);
    glNewList (list, GL_COMPILE);

    GLuint start = 0;
    GLuint end = 10;

/*
    GLvoid_draw_line_strip (color, Y_data, data_size, Z);
*/

    GLvoid_draw_thick_connected_lines (color, Y_data, data_size, Z);


    glEndList ();

    return list;
}

 
/*
void draw_scene


GList draw something

*/


