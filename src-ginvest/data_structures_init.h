/*
 *      data_structures_init.h
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


#ifndef __data_structures_init_h_
#define __data_structures_init_h_

#include "structures_papers.h"
#include "structures_statistics.h"
 
#include "configuration.h"

// CONTENT SHALL BE MOVED TO LOG.C or sth
#include "macros_debug.h"





/*
change *daily* to *period*

data bounds are actually initialized during file read in 2 stages.

first stage is to get basic data parameters (get_current_data_structure_parameters)
  - counting data labels    = current->labels_max
  - counting the maximum of e.g. daily (or any other periodic type) data listings           = current->listings_max

creating data pointers for:
data type pointers,
                    --> periodic  *  listings_max
                                                    --> listing * labels_max            (this should be updated)
  
second stage is to read and store in memory read data
                                                    --> listing [0 .. labels_max] 

 
after file read is completed:
current-> [[:parameters:]]        are stored in         datatype-> [[:parameters:]]


*/

 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * statistics data
//~ --------------------------------------------------------------------------------------------------------------------

// 5 days/week * 52 weeks = 260 days per year


//~ --------------------------------------------------------------------------------------------------------------------
//~ * debug data
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _debug_data debug_data;

struct _debug_data {

    guint16 print_listing;
    guint16 print_label;


};

//~ --------------------------------------------------------------------------------------------------------------------
//~ * current_data - purely current, there shall be an array of default current settings for all types of stocks
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _current_data current_data;

struct _current_data {

    guint8 t_stock_enum;
    std_entire_data *data_source;
    guint8 t_std_daily_result;

    gchar  *data_directory;
    GList  *data_filename;
    guint16 listings_max;
    guint16 labels_max;

    // displaying:
/*
    guint16 listing_older;
    guint16 listing_newer;
    guint8  num_displayed; // num of labels to be displayed (0 .. GLGRAPH_MAX_LINE_COLORS)
*/

 
/*
    GList *elements_drawn;
*/

    // value is initialized / changed while creating GL display list
    guint16 iter_ll;
    guint16 get_listing;
    guint16 get_label;

    GLfloat color [4]; //[GLGRAPH_MAX_LINE_COLORS][4]

};


typedef struct _current_data current_data_surround;


 
// this may only be included AFTER structure definition!
#include "structures_glgraph.h"  // !!!!!


  

//~ --------------------------------------------------------------------------------------------------------------------
//~ * externs
//~ --------------------------------------------------------------------------------------------------------------------

extern configuration            *config;
extern current_data             *current;
extern statistics_data          *statdata;
extern statistics_parameters    *statparams;
extern debug_data               *dbg_data;

extern glgraph_display_data     *displaydata;
extern glgraph_properties       *properties;
extern glgraph_scene            *scene;  // should contain available planes
extern glgraph_main_plane       *plane;  // a plane should contain all layers, subplanes, and its properties.

 
extern const gchar t_stat_name_default [STAT_T_STATISTIC_LAST_INDEX][CSV_FIELDNAME_LEN];
  

/*
extern GLfloat *GLfloat_array_buffer;
*/
 
extern std_entire_data *newconnect;


extern double sierp_gl_LookAt [3][3];


//~ --------------------------------------------------------------------------------------------------------------------
//~ * functions
//~ --------------------------------------------------------------------------------------------------------------------

/*
guint16 get_std_label_index (gint t_stock_enum, const gchar *label_name, guint16 last_element);
*/

gboolean initialize_gl_structures ();
gboolean initialize_current_data ();
gboolean initialize_statistics_data ();
gboolean initialize_statistics_parameters ();
gboolean initialize_debug_data ();

gboolean initialize_stage2_data_pointers (gint t_stock_enum, std_entire_data *destination);



/*
GLfloat *initialize_data_array_GLfloat (GLuint size, std_entire_data *source);
*/
/*
std_daily_result *initialize_std_daily_result (gfloat v_open, gfloat v_high,
                                               gfloat v_low, gfloat v_close, gfloat volume, gint pad);
*/







gboolean    *initialize_gboolean_array_null (guint size);
guint        gboolean_array_get_enabled (gboolean *array, guint size);


void finalize_struct (gpointer pointer);
void finalize_struct_array (gpointer *pointer, gint array_size);


#endif //__data_structures_init_h_
