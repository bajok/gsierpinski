/*
 *      sierpinski.c
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
#include <math.h>

#include "sierpinski.h"
#include "data_structures_init.h"


#define  sierp_COLOR_FADE               (displaydata->sierpinski_color_fade)
#define  sierp_CENTER_X                 (displaydata->sierpinski_center [0])
#define  sierp_CENTER_Y                 (displaydata->sierpinski_center [1])
#define  sierp_CENTER_Z                 (displaydata->sierpinski_center [2])
#define  sierp_DEPTH                    (displaydata->sierpinski_depth)


/******************
    subfunctions
 ******************/

static double midp (double a, double b) {

    return 0.5 * (a + b);
}

static double midp3 (double a, double b, double c) {

    return 0.5 * (a + b);
}
 

static void gl_draw_pyramid (double x1, double y1, double z1,
                             double x2, double y2, double z2,
                             double x3, double y3, double z3,
                             double x4, double y4, double z4) {

        glVertex3f (x1, y1, z1);
        glVertex3f (x2, y2, z2);
        glVertex3f (x3, y3, z3);

        glVertex3f (x4, y4, z4);
        glVertex3f (x1, y1, z1);

        glVertex3f (x4, y4, z4);
        glVertex3f (x2, y2, z2);

        glVertex3f (x4, y4, z4);
        glVertex3f (x3, y3, z3);
}
 
/*
GLuint sierpinski_depth = 4;
*/
 


/*
#define FADE_COLORS     for (GLuint channel = 0; channel < 4; channel++) \
                        fadecolor [channel] = color [channel] * (1.0 + (GLfloat) iterations * SIERP_COLOR_FADE)
*/
 

//~ --------------------------------------------------------------------------------------------------------------------
//~  draw_sierpinski
//~ --------------------------------------------------------------------------------------------------------------------

static GLfloat fadecolor [4] = {0.0, 0.0, 0.0, 0.0}; // the color that is actually used
static GLfloat fade_value [4] = {0.0, 0.0, 0.0, 0.0};

static GLuint  sierp_global_iterations = 0;


static void draw_sierp_triangles (int iterations, double x1, double y1, double z1,
                                  double x2, double y2, double z2,
                                  double x3, double y3, double z3,
                                  double x4, double y4, double z4,
                                  GLfloat *color) {


    if (iterations == sierp_DEPTH) {

        GLfloat fade_factor = 0.0;

        fade_value [0] =
            fabs (sierp_CENTER_X - x1) + fabs (sierp_CENTER_Y - y1) + fabs (sierp_CENTER_Z - z1);
        fade_value [1] =
            fabs (sierp_CENTER_X - x2) + fabs (sierp_CENTER_Y - y2) + fabs (sierp_CENTER_Z - z2);
        fade_value [2] =
            fabs (sierp_CENTER_X - x3) + fabs (sierp_CENTER_Y - y3) + fabs (sierp_CENTER_Z - z3);
        fade_value [3] =
            fabs (sierp_CENTER_X - x4) + fabs (sierp_CENTER_Y - y4) + fabs (sierp_CENTER_Z - z4);

        for (int iter = 0; iter < 4; iter++) 
            fade_factor += fade_value [iter];

        fade_factor /= 4;

        for (int channel = 0; channel < 4; channel++) 
            fadecolor [channel] = color [channel] - (fade_factor * sierp_COLOR_FADE);
 
        #ifdef DEBUG_GL
            if (sierp_DEPTH < 4) {
                DEBUG_LOG_FLOW          (DEBUG_GL, "draw_sierp_triangles", "drawing a triangle")
                DEBUG_LOG_FLOAT_ARRAY   (DEBUG_GL, " ", "fadecolor [4] = ", fadecolor, 4)
                DEBUG_LOG_FLOAT_ARRAY   (DEBUG_GL, " ", "sierpinski_center [3] = ", displaydata->sierpinski_center, 3)
            }
        #endif 
 
        glBegin (GL_POLYGON);           // a pyramid

            glColor4fv (fadecolor);
 
            gl_draw_pyramid (x1, y1, z1,
                             x2, y2, z2,
                             x3, y3, z3,
                             x4, y4, z4);

        glEnd();

        sierp_global_iterations++;
    }

 
    if (iterations < sierp_DEPTH) {  // recursively draws smaller and smaller triangles..

         
        draw_sierp_triangles (iterations + 1,
            x1, y1, z1,
            midp (x1, x2), midp (y1, y2), midp (z1, z2),
            midp (x1, x3), midp (y1, y3), midp (z1, z3),
            midp (x1, x4), midp (y1, y4), midp (z1, z4),
            color);
          
        draw_sierp_triangles (iterations + 1,
            x2, y2, z2,
            midp (x1, x2), midp (y1, y2), midp (z1, z2),
            midp (x2, x4), midp (y2, y4), midp (z2, z4),
            midp (x2, x3), midp (y2, y3), midp (z2, z3),
            color);

        draw_sierp_triangles (iterations + 1,
            x3, y3, z3,
            midp (x1, x3), midp (y1, y3), midp (z1, z3),
            midp (x3, x4), midp (y3, y4), midp (z3, z4),
            midp (x3, x2), midp (y3, y2), midp (z3, z2),
            color);

        draw_sierp_triangles (iterations + 1,
            x4, y4, z4,
            midp (x1, x4), midp (y1, y4), midp (z1, z4),
            midp (x2, x4), midp (y2, y4), midp (z2, z4),
            midp (x3, x4), midp (y3, y4), midp (z3, z4),
            color);
    }

}


 
 
  
 
//~ --------------------------------------------------------------------------------------------------------------------
//~  draw_sierpinski
//~ --------------------------------------------------------------------------------------------------------------------

void draw_sierpinski (GLfloat vertice_A [3],
                      GLfloat vertice_B [3],
                      GLfloat vertice_C [3],
                      GLfloat vertice_D [3],
                      GLfloat *color, GLuint sierpinski_depth) {

    #ifdef DEBUG_GL
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    LOG_INFO        ("draw_sierpinski")
    #endif
    #endif

/*
    get center
*/

 
    sierp_CENTER_X = 0.25 * (vertice_A [0] + vertice_B [0] + vertice_C [0] + vertice_D [0]);
    sierp_CENTER_Y = 0.25 * (vertice_A [1] + vertice_B [1] + vertice_C [1] + vertice_D [1]);
    sierp_CENTER_Z = 0.25 * (vertice_A [2] + vertice_B [2] + vertice_C [2] + vertice_D [2]);


/*
    #ifdef DEBUG_EXTREME
    #ifdef DEBUG_GL
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_FLOW        (DEBUG_GL, "draw_sierpinski", " ")
    DEBUG_LOG_INTEGER     (DEBUG_GL, " ", "sierpinski_depth", sierpinski_depth)
    DEBUG_LOG_FLOAT_ARRAY (DEBUG_GL, " ", "vertice_A [3] = ", vertice_A, 3)
    DEBUG_LOG_FLOAT_ARRAY (DEBUG_GL, " ", "vertice_B [3] = ", vertice_B, 3)
    DEBUG_LOG_FLOAT_ARRAY (DEBUG_GL, " ", "vertice_C [3] = ", vertice_C, 3)
    DEBUG_LOG_FLOAT_ARRAY (DEBUG_GL, " ", "vertice_D [3] = ", vertice_D, 3)
    DEBUG_LOG_FLOAT_ARRAY (DEBUG_GL, " ", "color [4] = ", color, 4)
    #endif
    #endif
    #endif
*/
 
    /* a call of a recursive function, that draws first "black" pyramid, and then
       recursively calls itself to draw smaller and smaller pyramids */

    /* co-ordinates of the first black pyramid (halves lengths of pyramid sides) */


    // reset counter
    sierp_global_iterations = 0;
     
    draw_sierp_triangles (1, vertice_A [X__0], vertice_A [Y__1], vertice_A [Z__2],
                             vertice_B [X__0], vertice_B [Y__1], vertice_B [Z__2],
                             vertice_C [X__0], vertice_C [Y__1], vertice_C [Z__2],
                             vertice_D [X__0], vertice_D [Y__1], vertice_D [Z__2],
                             color);


/*
    #ifdef DEBUG_GL
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    LOG_INFO_VALUE   ("global iterations: ", sierp_global_iterations)
    #endif
    #endif
*/

    LOG_INFO_VALUE   ("global iterations: ", sierp_global_iterations)

}



