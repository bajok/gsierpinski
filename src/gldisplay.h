/*
 *      gldisplay.h
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


#ifndef __gldisplay_h_
#define __gldisplay_h_


#include <GL/gl.h>
#include <GL/glu.h>
#include "data_structures_init.h"
  

#define CBGL_MOUSE_MOVE_RATIO 1.0


#define GLTRANSLATE_MIN               -20.0
#define GLTRANSLATE_MAX                 5.0

#define SIERP_XMIN                     -2.0
#define SIERP_XMAX                      2.0
#define SIERP_YMIN                     -2.0
#define SIERP_YMAX                      2.0
#define SIERP_ZMIN                     -2.0
#define SIERP_ZMAX                      2.0
 

#define ANGLE_MAX                     360.0
#define ANGLE_MIN                    -360.0

/*
#define FIXED_Z                        -4.0
*/
#define GLDISPLAY_LISTS                  1

#define VIEW_SCALE_MAX                  2.0
#define VIEW_SCALE_MIN                  0.5

#define DIG_2_RAD            (G_PI / 180.0)
#define RAD_2_DIG            (180.0 / G_PI)

#define ANIMATE_THRESHOLD              25.0
  
 
 

 
  
//~ --------------------------------------------------------------------------------------------------------------------
//~ *                                  gldisplay_display_data
//~ --------------------------------------------------------------------------------------------------------------------
 
typedef struct _gldisplay_display_data gldisplay_display_data;

struct _gldisplay_display_data  {

    // display parameters
    GLfloat     display_width;
    GLfloat     display_height;

    // display lists references
    GLuint      gldisplay [GLDISPLAY_LISTS];

    // animation variables
    gboolean    animate;
    GLfloat     view_quat_diff [4];
    GLfloat     view_quat [4];
    GLfloat     view_scale;
    GLfloat     begin_x;
    GLfloat     begin_y; 
    GLfloat     dx;
    GLfloat     dy;

    // fps counting 
    guint       frame_counter;
    gfloat      frames_per_second;

    // sierpinski specific
    GLfloat    *sierpinski_color; 
    GLfloat     sierpinski_color_fade;
    GLfloat     sierpinski_color_fade_type; // linear, quadratic
    GLuint      sierpinski_depth;

    GLfloat     sierpinski_vertice_A [3];
    GLfloat     sierpinski_vertice_B [3];
    GLfloat     sierpinski_vertice_C [3];
    GLfloat     sierpinski_vertice_D [3];
    GLfloat     sierpinski_center    [3];



        /* drawing sierpinski - vertices: A (x1, y1, z1), B, C, D. */
 


    /*
    GLfloat *sierpinski_color_fade;
    */
 
 
    // all display parameters (gldisplay required!) shall be stored here

}; 

 

//~ --------------------------------------------------------------------------------------------------------------------
//~ *                         gldisplay_scene
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _gldisplay_scene gldisplay_scene;

struct _gldisplay_scene {

    GLdouble dimensions [4];
    GLdouble Z_layer;

    // here may be also FIXED_Z

    GLdouble glupersp [4];
    GLfloat color [4];
    GLfloat clearcolor [4];
    GLfloat backgroundcolor [4];

    GLdouble gltranslate [3];
    GLdouble glrotate [4];          // angle, x, y, z

};
 

 





void gldisplay_update_display_data          (gldisplay_display_data *destination, current_data *source_param);


//~ --------------------------------------------------------------------------------------------------------------------
//~ * prototypes
//~ --------------------------------------------------------------------------------------------------------------------

void gldisplay_realize_main_gldisplay       (gldisplay_display_data *data);
void gldisplay_expose_main_gldisplay        (gldisplay_display_data *data);

  


#endif // __gldisplay_h_
