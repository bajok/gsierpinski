/*
 *      glgraph_drawing_procedures.c
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
/*
#include <math.h>
*/
#include <gtk/gtkgl.h>
#include <glib.h>
#include "data_structures_init.h"
#include "glgraph_drawing_procedures.h"
#include "glgraph.h"


 
/*
 * procedures shall use current_data
 *
 * function shall not
 *
*/


//~ --------------------------------------------------------------------------------------------------------------------
//~ graph creation subfunctions (still __void__ functions)
//~ --------------------------------------------------------------------------------------------------------------------

void glgraph_draw_stock_index (glgraph_display_data *data) {

    GLuint elements = 3;
    GLuint glgraph [elements];

    //~ GLint glgraph;
    GLsizei glsizei_range = (GLuint) elements;

/*
    creating lists
*/

    glgraph [0] = GLuint_draw_graph_background (glsizei_range, scene->backgroundcolor,
                                                               scene->dimensions [0],
                                                               scene->dimensions [1],
                                                               scene->dimensions [2],
                                                               scene->dimensions [3],
                                                               scene->Z_layer);

    glgraph [1] = GLuint_draw_graph_plane      (glsizei_range, plane->color,
                                                               plane->dimensions [0],
                                                               plane->dimensions [1],
                                                               plane->dimensions [2],
                                                               plane->dimensions [3],
                                                               plane->Z_layer);
 

 

/*
    glgraph_update_display_data (DISPLAY_STATISTICS);   // this function should be called within a CALLBACK
*/

 
 
    GLuint layer = 0;

    // when is above okay
    // and for each LAYER
 
/*
    Ydata [GLGRAPH_MAX_LAYERS][GLGRAPH_MAX_YDATA];
    Xnum  [GLGRAPH_MAX_LAYERS];
*/



    // display data is updated in callback --- there shall be just calls

/*
    displaydata->Xnum [layer] = 100;
*/
 

    glgraph [2] = GLuint_draw_share_graph_std (glsizei_range,
                                               data->color [layer],
                                               data->Ydata [layer],
                                               data->Xnum [layer],
                                               properties->line_Z_layer);
  
/*
    glgraph [3] = GLvoid_draw_circle           (glsizei_range, plane->color,
                                                               plane->dimensions [0],
                                                               plane->dimensions [1],
                                                               plane->dimensions [2],
                                                               plane->dimensions [3],
                                                               plane->dimension_z);
*/

/*
    calling lists
*/

    for (GLuint iter = 0; iter < elements; iter++) {

        glCallList (glgraph [iter]);
        glDeleteLists (glgraph [iter], 1);
    }

}
 
