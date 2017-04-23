/*
 *      structures_glgraph.h
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


#ifndef __structures_glgraph_h_
#define __structures_glgraph_h_

#include <GL/gl.h>
#include <GL/glu.h>
#include "data_structures_init.h"
 
 


#define ANGLE_MAX  360.0
#define ANGLE_MIN -360.0

#define FIXED_Z   -4

 
#define GLGRAPH_MAX_LINE_COLORS 16


#define GLGRAPH_MAX_YDATA   2048
#define GLGRAPH_MAX_LAYERS  16


 
typedef enum {

    DISPLAY_DATA,
    DISPLAY_STATISTICS,
    DISPLAY_COMBINED,
  
} t_display_datatype_enum;

 

//~ --------------------------------------------------------------------------------------------------------------------
//~ *                                glgraph_display_data
//~ --------------------------------------------------------------------------------------------------------------------
 
typedef struct _glgraph_display_data glgraph_display_data;

struct _glgraph_display_data  {
 
    // this structure be explicitly initialized
    GLfloat Ydata [GLGRAPH_MAX_LAYERS][GLGRAPH_MAX_YDATA];       // graph highest point 
    // GLfloat Xmax  [GLGRAPH_MAX_LAYERS];
    GLfloat Xnum  [GLGRAPH_MAX_LAYERS];
    GLfloat color [GLGRAPH_MAX_LAYERS][4];
 
    // all display parameters (glgraph required!) shall be stored here

 

  
}; 

 
//~ --------------------------------------------------------------------------------------------------------------------
//~ *                              glgraph_properties
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _glgraph_properties glgraph_properties;

struct _glgraph_properties  {

    GLfloat plane_thickness;
    GLfloat plane_altitude;
  
    GLfloat line_Z_layer;           // this should be line_Z [GLGRAPH_MAX_LAYERS]
    GLfloat line_thickness;
    GLfloat line_altitude;
    GLfloat line_color_R [GLGRAPH_MAX_LINE_COLORS];
    GLfloat line_color_G [GLGRAPH_MAX_LINE_COLORS];
    GLfloat line_color_B [GLGRAPH_MAX_LINE_COLORS];
    GLfloat line_color_A [GLGRAPH_MAX_LINE_COLORS];

};

//~ --------------------------------------------------------------------------------------------------------------------
//~ *                         glgraph_scene
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _glgraph_scene glgraph_scene;

struct _glgraph_scene {

    GLdouble dimensions [4];
    GLdouble Z_layer;

    // here may be also FIXED_Z

    GLdouble glupersp [4];

/*
    GLfloat aspect_x;
    GLfloat aspect_y;
*/

    GLfloat color [4];
    GLfloat clearcolor [4];
    GLfloat backgroundcolor [4];


    GLdouble gltranslate [3];
    GLdouble glrotate [4];


};
 

//~ --------------------------------------------------------------------------------------------------------------------
//~ *                              glgraph_main_plane
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _glgraph_main_plane glgraph_main_plane;

struct _glgraph_main_plane {

    GLdouble dimensions [4];
    GLdouble Z_layer;

    GLfloat  color [4];

    GLdouble glclearcolor [4];

};


//~ --------------------------------------------------------------------------------------------------------------------
//~ *                               glgraph_main_rulers
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _glgraph_main_rulers glgraph_main_rulers;

struct _glgraph_main_rulers {

    GLdouble dimensions [4];
    GLdouble dimension_z;

    GLfloat  color [4];

    GLdouble gltranslate [3];
    GLdouble glupersp [4];
    GLdouble glclearcolor [4];

};



/*
besides of that:

typedef struct _glgraph_plane glgraph_plane;
struct _glgraph_plane {
}

typedef struct _glgraph_rulers glgraph_rulers;
struct _glgraph_rulers {
}
*/
 
 

/*
int x;
x = x+1;
*/
 

void glgraph_update_display_data (glgraph_display_data *destination, 
                                  current_data *source_params, GLuint t_display_datatype_enum);

 

#endif // __structures_glgraph_h_
