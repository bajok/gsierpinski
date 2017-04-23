/*
 *      data_structures_init.c
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


#include <glib.h>
#include <gtk/gtkgl.h>


#include "data_structures_init.h"
#include "file_io.h"



//~ --------------------------------------------------------------------------------------------------------------------
//~ * initializing memory
//~ --------------------------------------------------------------------------------------------------------------------

/*
current data
*/
configuration           *config;
current_data            *current;
statistics_data         *statdata;
statistics_parameters   *statparams;
debug_data              *dbg_data;


/*
glgraph data
*/

glgraph_display_data    *displaydata;
glgraph_properties      *properties;
glgraph_scene           *scene;
glgraph_main_plane      *plane;
 
/*
GLfloat *GLfloat_array_buffer;
*/


/*
stock data
*/
std_entire_data         *newconnect;





//~ --------------------------------------------------------------------------------------------------------------------
//~ * initializing gl_structures
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_gl_structures () {

    /*
     * properties
     */
    properties = g_malloc (sizeof (glgraph_properties));
    if (properties == NULL) {
        LOG_ERROR ("glgraph_properties *properties: memory could not be allocated")
        return FALSE;
    } else {
        properties->line_thickness = 0.003;
        properties->line_altitude = 0.002;
        properties->plane_thickness = 0.001;
        properties->plane_altitude = 0.002;
        properties->line_Z_layer = -0.0115;

        for (gint iter = 0; iter < GLGRAPH_MAX_LINE_COLORS; iter++) {
            properties->line_color_R [iter] = (GLfloat) iter * 0.03f;
            properties->line_color_G [iter] = (GLfloat) iter * 0.02f;
            properties->line_color_B [iter] = (GLfloat) iter * 0.01f;
            properties->line_color_A [iter] = 1.0f;
        }
    }

    /*
     * scene
     */
    scene = g_malloc (sizeof (glgraph_scene));
    if (scene == NULL) {
        LOG_ERROR ("glgraph_scene *scene: memory could not be allocated")
        return FALSE;
    } else {
/*
        scene->aspect_x = 1;
        scene->aspect_y = 1;
*/
        scene->Z_layer = 0.00; // higher is further

        scene->dimensions [0] = -0.01;
        scene->dimensions [1] = 1.01;
        scene->dimensions [2] = -0.10;
        scene->dimensions [3] = 1.01;

        scene->color [0] = 0.125;
        scene->color [1] = 0.025;
        scene->color [2] = 0.005;
        scene->color [3] = 1.000;

        scene->clearcolor [0] = 0.125;
        scene->clearcolor [1] = 0.025;
        scene->clearcolor [2] = 0.005;
        scene->clearcolor [3] = 0.500;

        scene->backgroundcolor [0] = 0.525;
        scene->backgroundcolor [1] = 0.025;
        scene->backgroundcolor [2] = 0.005;
        scene->backgroundcolor [3] = 0.800;

        scene->gltranslate [0] = -0.490;
        scene->gltranslate [1] = -0.470;
        scene->gltranslate [2] = -0.690;

        scene->glrotate [0] = 6;
        scene->glrotate [1] = 60;
        scene->glrotate [2] = 120;
        scene->glrotate [3] = 60;
    }

    /*
     * plane
     */
    plane = g_malloc (sizeof (glgraph_main_plane));
    if (plane == NULL) {
        LOG_ERROR ("glgraph_main_plane *plane: memory could not be allocated")
        return FALSE;
    } else {
        plane->dimensions [0] = 0; // x1
        plane->dimensions [1] = 1; // x2
        plane->dimensions [2] = 0; // y1
        plane->dimensions [3] = 1; // y2

        plane->Z_layer = -0.00001;

        plane->color [0] = 1;
        plane->color [1] = 1;
        plane->color [2] = 0.8;
        plane->color [3] = 0.5;

        plane->glclearcolor [0] = 0.3;
        plane->glclearcolor [1] = 0.2;
        plane->glclearcolor [2] = 0.0;
        plane->glclearcolor [3] = 1.0;

/*
        plane->gltranslate [0] = -0.5;
        plane->gltranslate [1] = -0.5;
        plane->gltranslate [2] = 8.9;

        plane->glrotate [0] = 0;
        plane->glrotate [1] = 0;
        plane->glrotate [2] = 0;
        plane->glrotate [3] = 0;
*/
    }

    return TRUE;
}



//~ --------------------------------------------------------------------------------------------------------------------
//~ * gboolean initialize_current_data ()
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_current_data () {

    current = g_malloc0 (sizeof (current_data));
    if (current == NULL) {
        LOG_ERROR ("current_data *current: memory could not be allocated")
        return FALSE;
    }
    current->data_directory = g_malloc ((sizeof (gchar)) * FILENAME_LENGTH_MAX);

    return TRUE;
}

//~ --------------------------------------------------------------------------------------------------------------------
//~ * gboolean initialize_statistics_data ()
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_statistics_data () {

    statdata = g_malloc (sizeof (statistics_data));
    if (statdata == NULL) {
        LOG_ERROR ("statistics_data *statdata: memory could not be allocated")
        return FALSE;
    }
    return TRUE;
}

//~ --------------------------------------------------------------------------------------------------------------------
//~ * gboolean initialize_statistics_parameters ()
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_statistics_parameters () {

    statparams = g_malloc (sizeof (statistics_parameters));
    if (statparams == NULL) {
        LOG_ERROR ("statistics_parameters *statparams: memory could not be allocated")
        return FALSE;
    }
    return TRUE;
}

 
//~ --------------------------------------------------------------------------------------------------------------------
//~ * gboolean initialize_debug_data ()
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_debug_data () {

    dbg_data = g_malloc (sizeof (debug_data));
    if (dbg_data == NULL) {
        LOG_ERROR ("debug_data *dbg_data: memory could not be allocated")
        return FALSE;
    }
    return TRUE;
}  

//~ --------------------------------------------------------------------------------------------------------------------
//~ * initializing papers
//~ --------------------------------------------------------------------------------------------------------------------

//~ --------------------------------------------------------------------------------------------------------------------
//~ * initialize_data_pointers
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_stage2_data_pointers (gint t_stock_enum, std_entire_data *destination) {

    guint num_of_listings = current->listings_max;
    guint num_of_labels = current->labels_max;
 
/*
    g_try_malloc ();
*/ 

        for (gint iter = 0; iter < num_of_listings; iter++) {
            // creating pointer for each daily listing
 
            if (!(destination->daily[iter]->char_date = (gchar*)
                g_malloc0 ((sizeof (gchar)) * CSV_FIELDNAME_LEN))) return FALSE;


            if (!(destination -> daily[iter] -> listed = (std_daily_result **)
                g_malloc0 ((sizeof (gpointer)) * num_of_labels))) return FALSE;

            for (gint iter2 = 0; iter2 < num_of_labels; iter2++) {

                if (!(destination -> daily[iter] -> listed[iter2] = (std_daily_result *)
                    //creating pointer for each listed in every listing
                    create_std_daily_result ())) return FALSE;
                
/*
                if (!(destination -> daily[iter] -> listed[iter2] = (std_daily_result *)
                    //creating pointer for each listed in every listing
                    g_malloc0 ((sizeof (gpointer))))) return FALSE;
*/
 
            }
        }
 

        /*newconnect->labels != NULL || */
        if (destination->daily != NULL) {
            destination->num_of_listings = current->listings_max;
            destination->num_of_labels = current->labels_max;
            return TRUE;
        }
        else return FALSE;
/*
    }
*/

/*
    if (t_stock_enum == WIG20) {


        return TRUE;

    }
    else return FALSE;
*/

    return TRUE;
}

  

//~ --------------------------------------------------------------------------------------------------------------------
//~ * flags_operations
//~ --------------------------------------------------------------------------------------------------------------------
 


/*
gboolean *initialize_gboolean_array (guint size) {

    gboolean *array = g_malloc0 ((sizeof (gboolean)) * size);
    return array;
}
*/

/*
#define GBOOLEAN_ARRAY_NULL (array, size) \
        array = g_malloc0 ((sizeof (gboolean)) * size)

#define GBOOLEAN_ARRAY_ENABLE_ALL (array, size) \
        for (gint iter = 0; iter < size; iter++) array [iter] = TRUE
*/
 
 

gboolean *initialize_gboolean_array_null (guint size) {

    gboolean *array = g_malloc0 ((sizeof (gboolean)) * size);
    return array;
}



guint gboolean_array_get_enabled (gboolean *array, guint size) {

    guint counter = 0;
    for (guint iter = 0; iter < size; iter++)
        if (array [iter] == TRUE) counter++;
    return counter;
}
 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * freeing memory
//~ --------------------------------------------------------------------------------------------------------------------

void finalize_struct (gpointer pointer) {   // gint t_struct_type  if (t_struct_type == GLGRAPH_PLANE) ....
    #ifdef DEBUG_MEM_ALLOC
    DEBUG_LOG_INTEGER (DEBUG_MEM_ALLOC, "finalize_struct", \
                                         "memory freed for: GPOINTER_TO_INT (%d)", GPOINTER_TO_INT (pointer))
    #endif
    g_free (pointer);
}


void finalize_struct_array (gpointer *pointer, gint array_size) {
    for (gint i = 0; i < array_size; i++) {
        #ifdef DEBUG_MEM_ALLOC
/*
        DEBUG_LOG_INTEGER (DEBUG_MEM_ALLOC, "finalize_struct", \
                                            "memory freed for: GPOINTER_TO_INT (%d)", GPOINTER_TO_INT (pointer))
*/
        #endif
        g_free (pointer [i]);
    }
/*
    g_prnt ("memory freed for array of structures: GPOINTER_TO_INT (%p) = %d\n", pointer, GPOINTER_TO_INT (pointer));
*/
}
