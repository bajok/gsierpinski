/*
 *      structures_glgraph.c
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
#include <gtk/gtkgl.h>
#include "data_structures_init.h"


  
  
//~ --------------------------------------------------------------------------------------------------------------------
//~ glgraph_update_display_data
//~ --------------------------------------------------------------------------------------------------------------------


 
 // THIS should be a callback or a function called from a callback


// these functions write glgraph_display_data struct

static void displaydata_write_std_data (glgraph_display_data *destination, std_entire_data *source,
                                        GLuint label_id, GLuint listing, GLuint range) {

    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW      (DEBUG_GL, "displaydata_write_std_data", "writing display data")
    #endif 

    // ekhm -- range boundaries are determined at GUI level..
    for (guint iter = 0; (iter < GLGRAPH_MAX_YDATA) && (iter < range); iter++) {
 
        // switch data : V_OPEN, V_CLOSE....
 
        destination->Ydata [0][iter] = source->daily[listing+iter]->listed[label_id]->v_open;
        #ifdef DEBUG_GL
            DEBUG_LOG_FLOAT (DEBUG_GL, "displaydata_write_std_data", \
                                       "destination->Ydata [0][iter]", destination->Ydata [0][iter])
        #endif

    }


    destination->Xnum [0] = range;

}

 
void glgraph_update_display_data (glgraph_display_data *destination,
                                  current_data *source_param, GLuint t_display_datatype_enum) {

    #ifdef DEBUG_GL
        DEBUG_LOG_FLOW      (DEBUG_GL, "glgraph_update_display_data", "updating display data")
    #endif 
  
    std_entire_data *data_source = source_param->data_source;
    statistics_data *stat_source = statdata;

    GLuint label_id = stat_source->get_label;
    GLuint listing  = stat_source->get_listing;
    GLuint range    = stat_source->get_listing_range;

    switch (t_display_datatype_enum) {  
        case DISPLAY_DATA:

            // cb_fill_glgraph_display_data (displaydata, current->data_source);
/*
    GLuint GLuint_draw_share_graph_std   (GLsizei range, GLfloat *color,
                                          GLfloat *Y_data, GLuint data_size, GLfloat Z) {

    GLvoid_draw_thick_connected_lines (color, Y_data, data_size, Z);

*/
            displaydata_write_std_data (destination, data_source, label_id, listing, range);

            #ifdef DEBUG_GL
                DEBUG_LOG_INTEGER (DEBUG_GL, "glgraph_update_display_data", "label_id", label_id)
                DEBUG_LOG_INTEGER (DEBUG_GL, "glgraph_update_display_data", "listing",  listing)
                DEBUG_LOG_INTEGER (DEBUG_GL, "glgraph_update_display_data", "range", range)
                DEBUG_LOG_POINTER (DEBUG_GL, "glgraph_update_display_data", "destination", destination)
                DEBUG_LOG_POINTER (DEBUG_GL, "glgraph_update_display_data", "data_source", data_source)
            #endif

  
/* 
    FILL WITH DATA PLEASE
*/
/*
            function call !!!!!!!!!111111111
*/
 
 

            break;
        case DISPLAY_STATISTICS:

            // acquires statistics data and copies it to display data


            break;
        case DISPLAY_COMBINED:

            break;
        default:
            break;
    }


}



/*
                t_std_daily_result field_enum = 0;
                while (field_enum != (t_std_daily_result) VOLUME) {

gfloat get_std_value_by_l_ll  (guint label_id, guint listing, gint t_std_daily_result,
                               gint t_stock_enum, std_entire_data *source) {
*/
