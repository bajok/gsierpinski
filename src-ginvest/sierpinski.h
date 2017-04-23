/*
 *      sierpinski.h
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


#ifndef __sierpinski_h_
#define __sierpinski_h_


    void gl_realize_sierpinski (GtkWidget *widget, gpointer data);
    void gl_draw_sierpinski (GdkGLDrawable *gldrawable);

    GLvoid gl_sierpinski_triangle ();



    /* ********************** *
        fractal subfunctions
    * ********************** */

    double midp (double a, double b);

    void gl_draw_pyramid (double x1, double y1, double z1,
                          double x2, double y2, double z2,
                          double x3, double y3, double z3,
                          double x4, double y4, double z4);

    // sierpinski subfunctions

    void draw_sierpinski (double x1, double y1, double z1,
                          double x2, double y2, double z2,
                          double x3, double y3, double z3,
                          double x4, double y4, double z4,
                          GLfloat *color);

    void draw_sierp_triangles (int iterations, double x1, double y1, double z1,
                                               double x2, double y2, double z2,
                                               double x3, double y3, double z3,
                                               double x4, double y4, double z4,
                                               GLfloat *color);



#endif // __sierpinski_h_
