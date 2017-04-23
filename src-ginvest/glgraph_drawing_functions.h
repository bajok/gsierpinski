/*
 *      glgraph_drawing_functions.h
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


#ifndef __glgraph_drawing_functions_h_
#define __glgraph_drawing_functions_h_

#include <GL/gl.h>
#include <GL/glu.h>
#include <gtk/gtkgl.h>



GLuint GLuint_draw_graph_plane (GLsizei range, GLfloat *color,
                                GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2, GLdouble Z);

GLuint GLuint_draw_graph_background (GLsizei range, GLfloat *color,
                                     GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2, GLdouble Z);

GLuint GLuint_draw_share_graph_std   (GLsizei range, GLfloat *color,
                                      GLfloat *Y_data, GLuint data_size, GLfloat Z);



#endif // __glgraph_drawing_functions_h_
