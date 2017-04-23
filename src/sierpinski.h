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


 
typedef enum {

    X__0,
    Y__1,
    Z__2,
    LAST_COORD,
    
};


    void draw_sierpinski (GLfloat vertice_A [3],
                          GLfloat vertice_B [3],
                          GLfloat vertice_C [3],
                          GLfloat vertice_D [3],
                          GLfloat *color, GLuint sierpinski_depth);
 

/*
    void draw_sierpinski (double x1, double y1, double z1,
                          double x2, double y2, double z2,
                          double x3, double y3, double z3,
                          double x4, double y4, double z4,
                          GLfloat *color, GLuint sierpinski_depth);
*/

 
 

#endif // __sierpinski_h_
