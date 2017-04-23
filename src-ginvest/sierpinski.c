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

/* this file includes openGL implementation of several fractals.
 * mainly, it contains only GL LIST functions.
 */


/* ***********************
    FIXME   FIXME   FIXME
   *********************** */

// zreperowac nazwy zmiennych




// void glColor4fv (const GLfloat *v);
// void glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

GLint sierpinski;

int sierpinski_depth = 4;



float sierp_gltranslate [3] = {0, 0, 2};
float sierp_glupersp [4] = {60.0, 1.0, 1.0, 100.0}; 
GLfloat sierp_glclearcolor [4] = {0.3, 0.2, 0.0, 1.0};


double sierp_gl_LookAt [3][3] =   {{1.0, 1.0, 5.0},
                             {0.0, 0.0, 0.0},
                             {0.0, 1.0, 0.0}};



GLfloat sierp_color       [4] =    {1, 1, 0, 1};



void gl_realize_sierpinski (GtkWidget *widget, gpointer data) {
    
    /* the fractal display functions */
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //~ glOrtho (-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
    glOrtho (-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    //~ glOrtho (-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
     //~ gluPerspective (glupersp [0], glupersp [1], glupersp [2], glupersp [3]); // fovy, aspect, zNear, zFar
    GLfloat width = widget->allocation.width;
    GLfloat height = widget->allocation.height;
    gluPerspective(45.0f, width / height, 0.1f, 100.0f);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    
    
    //~ --------------------------
    //~ // there may be a function realize_sierpinski ();  from sierpinski.c
    //~ // with gluLookAt, glTranslatef 
    //~ --------------------------
    
    gluLookAt (sierp_gl_LookAt [0][0], sierp_gl_LookAt [0][1], sierp_gl_LookAt [0][2],
               sierp_gl_LookAt [1][0], sierp_gl_LookAt [1][1], sierp_gl_LookAt [1][2],
               sierp_gl_LookAt [2][0], sierp_gl_LookAt [2][1], sierp_gl_LookAt [2][2]);
    glTranslatef (sierp_gltranslate [0], sierp_gltranslate [1], sierp_gltranslate [2]);
}

void gl_draw_sierpinski (GdkGLDrawable *gldrawable) {
   
    glClearDepth (1.0);
    glClearColor (sierp_glclearcolor [0], sierp_glclearcolor [1], sierp_glclearcolor [2], sierp_glclearcolor [3]); // background color
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* drawing fractal */

    GLfloat LightAmbient[]  = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat LightDiffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT1);


    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glShadeModel(GL_SMOOTH);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sierp_color);

    glDepthFunc (GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glCullFace (GL_FRONT_AND_BACK);
    

    gl_sierpinski_triangle ();
    glCallList (sierpinski);

    #ifdef DEBUG_GL
        DEBUG_LOG_INTEGER (DEBUG_GL, "gl_draw_sierpinski", "sierpinski", sierpinski)
    #endif

    glDeleteLists(sierpinski, 1);
    
    if (gdk_gl_drawable_is_double_buffered (gldrawable))
            gdk_gl_drawable_swap_buffers (gldrawable);
    else
            glFlush ();
    
    
}

GLvoid gl_sierpinski_triangle () {

    sierpinski = glGenLists (1);
    glNewList (sierpinski, GL_COMPILE);

        /* drawing sierpinski - vertices: A (x1, y1, z1), B, C, D. */
        draw_sierpinski (-1.000,  -1.000,  -1.000,
                          1.000,  -1.000,  -1.000,
                          0.000,   0.732,  -1.000,
                          0.000,  -0.423,   0.633,
                          sierp_color);

    glEndList ();
}




/* ********************** *
    fractal subfunctions
 * ********************** */

double midp (double a, double b) {

    return 0.5 * (a + b);
}



void gl_draw_pyramid (double x1, double y1, double z1,
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


/* ************************** sierpinski **************************** */

void draw_sierpinski (double x1, double y1, double z1,
                      double x2, double y2, double z2,
                      double x3, double y3, double z3,
                      double x4, double y4, double z4,
                      GLfloat *color) {

//         glColor4f (color_red [0], color_red [1], color_red [2], color_red [3]);

    /* a call of a recursive function, that draws first "black" pyramid, and then
       recursively calls itself to draw smaller and smaller pyramids */

    /* co-ordinates of the first black pyramid (halves lengths of pyramid sides) */

    draw_sierp_triangles (1, x1, y1, z1,
                             x2, y2, z2,
                             x3, y3, z3,
                             x4, y4, z4,
                          color);
}


void draw_sierp_triangles (int iterations, double x1, double y1, double z1,
                                           double x2, double y2, double z2,
                                           double x3, double y3, double z3,
                                           double x4, double y4, double z4,
                                           GLfloat *color) {

    // sierpinski tetrahedron
                                               
    if (iterations == sierpinski_depth) {

        glBegin (GL_POLYGON);           // a pyramid

            glColor4fv (color);

            gl_draw_pyramid (x1, y1, z1,
                             x2, y2, z2,
                             x3, y3, z3,
                             x4, y4, z4);

        glEnd();
    }

    if (iterations < sierpinski_depth) {  // recursively draws smaller and smaller triangles..
                                          // but in that case justs finds coordinates to draw
                                          // the smallest ones

        // four smaller pyramids... and so on

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


const double PI = 3.141592;

struct _complex {



} complex;

