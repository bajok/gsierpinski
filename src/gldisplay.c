/*
 *      gldisplay.c
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
#include "data_structures_init.h"
#include "gldisplay.h"
#include "gldisplay_drawing_functions.h"
#include "trackball.h"




//~ --------------------------------------------------------------------------------------------------------------------
//~  gldisplay_update_display_data
//~ --------------------------------------------------------------------------------------------------------------------
 
void gldisplay_update_display_data (gldisplay_display_data *destination,
                                    current_data *source_param) {

/*
    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW      (DEBUG_GL, "gldisplay_update_display_data", "updating display data")
    #endif 


    // conversions, checks, etc.


    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW      (DEBUG_GL, "color copied", "color copied")
    #endif 
*/

 
    // some other actions here....

}


typedef struct _MaterialProp
{
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} MaterialProp;

static MaterialProp mat_emerald = {
  {0.0215, 0.1745, 0.0215, 1.0},
  {0.07568, 0.61424, 0.07568, 1.0},
  {0.633, 0.727811, 0.633, 1.0},
  0.6
};
  
  
//~ --------------------------------------------------------------------------------------------------------------------
//~  gldisplay_realize_main_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------
 
void gldisplay_realize_main_gldisplay (gldisplay_display_data *data) {

/*
    gldisplay_drawfunc_delete_buffer ((gldisplay_display_data *) data);
*/
/*
    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW      (DEBUG_GL, "gldisplay_realize_main_gldisplay", " . ")
    #endif 
*/

    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {0.0, 3.0, 3.0, 0.0};

    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat local_view[] = {0.0};

/*
    glClearColor (0.5, 0.5, 0.8, 1.0);
*/
    glClearColor (scene->clearcolor [0], scene->clearcolor [1], scene->clearcolor [2], scene->clearcolor [3]); // background color

    glClearDepth (1.0);

    glLightfv (GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, position);
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv (GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glFrontFace (GL_CW);
/*
    glEnable (GL_LIGHTING);
*/
    glEnable (GL_LIGHT0);
    glEnable (GL_AUTO_NORMAL);
    glEnable (GL_NORMALIZE);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
 
    gluPerspective(45.0f, data->display_width / data->display_height, 0.1f, 100.0f);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();



    gldisplay_drawfunc_ready_buffer ((gldisplay_display_data *) data);

}

 
 
//~ --------------------------------------------------------------------------------------------------------------------
//~         gldisplay_reshape, view transformation.
//~ --------------------------------------------------------------------------------------------------------------------
 
static void gldisplay_reshape (gldisplay_display_data *data) {

    data->frame_counter++;
    float m[4][4];

    glTranslated (scene->gltranslate [0], scene->gltranslate [1], scene->gltranslate [2]);
    glRotatef    (scene->glrotate [0], scene->glrotate [1], scene->glrotate [2], scene->glrotate [3]);
 
/*
    glTranslatef (0.0, 0.0, -10.0);
*/
    glScalef (data->view_scale, data->view_scale, data->view_scale);
    add_quats (data->view_quat_diff, data->view_quat, data->view_quat);
    build_rotmatrix (m, data->view_quat);
    glMultMatrixf (&m[0][0]);

}
   
    
//~ --------------------------------------------------------------------------------------------------------------------
//~  gldisplay_expose_main_gldisplay
//~ --------------------------------------------------------------------------------------------------------------------
   
void gldisplay_expose_main_gldisplay (gldisplay_display_data *data) {
 
/*
 *  THIS MAY BE LOGGED
 * 
    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW      (DEBUG_GL, "gldisplay_expose_main_gldisplay", " . ")
    #endif 
*/ 
 
/*
    glTranslated (scene->gltranslate [0], scene->gltranslate [1], scene->gltranslate [2]);
    glRotatef    (scene->glrotate [0], scene->glrotate [1], scene->glrotate [2], scene->glrotate [3]);
*/ 
 
/*
    glClearDepth (1.0);
    glClearColor (scene->clearcolor [0], scene->clearcolor [1], scene->clearcolor [2], scene->clearcolor [3]); // background color
*/
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();


    // reshape
    gldisplay_reshape ((gldisplay_display_data *) data);

    GLfloat LightAmbient[]  = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat LightDiffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
/*
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};
*/
    GLfloat LightSpecular[] = {0.0f, 0.0f, 2.0f, 1.0f};
    GLfloat LightShininess  = 0.6;

    glMaterialfv (GL_FRONT, GL_AMBIENT, LightAmbient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, LightDiffuse);
    glMaterialfv (GL_FRONT, GL_SPECULAR, LightSpecular);
    glMaterialf (GL_FRONT, GL_SHININESS, LightShininess * 128.0);

/*
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glShadeModel(GL_SMOOTH);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scene->color);

    glDepthFunc (GL_LESS);
    glEnable (GL_DEPTH_TEST);
 
    glCullFace (GL_FRONT_AND_BACK);
*/

/*
    GLfloat rotate_angle = scene->glrotate [0];
    glTranslated (scene->gltranslate [0], scene->gltranslate [1], scene->gltranslate [2]);
    glRotatef (rotate_angle, scene->glrotate [1], scene->glrotate [2], scene->glrotate [3]);
*/

/*
    glTranslated (scene->gltranslate [0], scene->gltranslate [1], scene->gltranslate [2]);
    glRotatef    (scene->glrotate [0], scene->glrotate [1], scene->glrotate [2], scene->glrotate [3]);
*/

    // calling buffer
    gldisplay_drawfunc_call_buffer ((gldisplay_display_data *) data);
 
}

