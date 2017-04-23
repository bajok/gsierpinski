/*
 *      structures_papers.c
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
#include "data_structures_init.h"



//~ --------------------------------------------------------------------------------------------------------------------
//~ *             create_std_daily_result
//~ --------------------------------------------------------------------------------------------------------------------

std_daily_result *create_std_daily_result () {

    std_daily_result *share;
    share = g_malloc0 (sizeof (share));
    if (share == NULL) {
        return NULL;
    } else {

        share->v_open   = GFLOAT_VALUE_UNINITIALIZED;
        share->v_high   = GFLOAT_VALUE_UNINITIALIZED;
        share->v_low    = GFLOAT_VALUE_UNINITIALIZED;
        share->v_close  = GFLOAT_VALUE_UNINITIALIZED;
        share->volume   = GFLOAT_VALUE_UNINITIALIZED;
        share->pad      = GFLOAT_VALUE_UNINITIALIZED;
    }

    return share;
}
 
    
//~ --------------------------------------------------------------------------------------------------------------------
//~ *    initialize_std_daily_result
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_std_daily_result (std_daily_result *share, gfloat v_open, gfloat v_high,
                                      gfloat v_low, gfloat v_close, gfloat volume, gint pad) {

    if (share == NULL) {
        return FALSE;
    } else {

        share->v_open   = v_open;
        share->v_high   = v_high;
        share->v_low    = v_low;
        share->v_close  = v_close;
        share->volume   = volume;
        share->pad      = pad;
    }

    return share;
}



//~ --------------------------------------------------------------------------------------------------------------------
//~ *  global GET, static SET value
//~ --------------------------------------------------------------------------------------------------------------------
 
gfloat get_std_value_by_l_ll  (guint label_id, guint listing, gint t_std_daily_result,
                               gint t_stock_enum, std_entire_data *source) {
  
    gfloat value = GFLOAT_VALUE_UNINITIALIZED;
  
    //t_std_daily_result field_type = t_std_daily_result;
    switch (t_std_daily_result) {  
        case V_OPEN:
            value = (gfloat) source->daily[listing]->listed[label_id]->v_open;
            break;
        case V_CLOSE:
            value = (gfloat) source->daily[listing]->listed[label_id]->v_close;
            break;
        case V_LOW:
            value = (gfloat) source->daily[listing]->listed[label_id]->v_low;
            break;
        case V_HIGH:
            value = (gfloat) source->daily[listing]->listed[label_id]->v_high;
            break;
        case VOLUME:
            value = (gfloat) source->daily[listing]->listed[label_id]->volume;
            break;
        default:
            break;
    }
    return value;
} 

 
static void set_std_value_by_l_ll  (guint label_id, guint listing, gint t_std_daily_result,
                             gint t_stock_enum, std_entire_data *destination, gfloat value) {

    #ifdef DEBUG_STATISTICS
        DEBUG_LOG_FLOW      (DEBUG_STATISTICS, "set_std_value_by_l_ll", " . ")
    #endif 

    //t_std_daily_result field_type = t_std_daily_result;

    switch (t_std_daily_result) {  
        case V_OPEN:
            destination->daily[listing]->listed[label_id]->v_open = (gfloat) value;
            break;
        case V_CLOSE:
            destination->daily[listing]->listed[label_id]->v_close = (gfloat) value;
            break;
        case V_LOW:
            destination->daily[listing]->listed[label_id]->v_low = (gfloat) value;
            break;
        case V_HIGH:
            destination->daily[listing]->listed[label_id]->v_high = (gfloat) value;
            break;
        case VOLUME:
            destination->daily[listing]->listed[label_id]->volume = (gfloat) value;
            break;
        default:
            // return NULL; // should be impossible :)
            break;
    //return value;
    }
} 
   
  
//~ --------------------------------------------------------------------------------------------------------------------
//~ *    fill_data_with_values_from_previous_listings --- all but not VOLUME!
//~ --------------------------------------------------------------------------------------------------------------------
 
gboolean fill_data_with_values_from_previous_listings (gint t_stock_enum, std_entire_data *destination) {


    if (destination->fill_data_with_values_from_previous_listings == TRUE) {

        guint total_labels = destination->num_of_labels;
        guint total_listings = destination->num_of_listings;


        for (guint listing = 1; listing < total_listings; listing++) {

            for (guint label_id = 0; label_id < total_labels; label_id++) {

                // for each field
                t_std_daily_result field_enum = 0;
                while (field_enum != (t_std_daily_result) VOLUME) {
  
                    // get previous value
                    gfloat prev_day_value =
                    get_std_value_by_l_ll (label_id, listing - 1, field_enum,
                                           t_stock_enum, destination);

                    gfloat curr_day_value =
                    get_std_value_by_l_ll (label_id, listing, field_enum,
                                           t_stock_enum, destination);
 
                    // when current value is uninitialized (this day share is not listed)
                    // so we can assume, that it has the same value as previous day
                    if (curr_day_value == GFLOAT_VALUE_UNINITIALIZED)
                        set_std_value_by_l_ll (label_id, listing, field_enum,
                                               t_stock_enum, destination, (gfloat) prev_day_value);
                    field_enum++;
                }
            }
        }
    }
    else
        return FALSE;

    return TRUE;

}






  
//~ --------------------------------------------------------------------------------------------------------------------
//~ * GET
//~ --------------------------------------------------------------------------------------------------------------------


guint16 get_std_label_index (gint t_stock_enum, std_entire_data *destination,
                             const gchar *label_name, guint16 last_element) {

    for (guint16 iter = 0; iter < last_element; iter++) {
        if ((g_strcmp0 (destination->labels[iter]->name, label_name)) == 0)
            return iter; // label found, breaking, returning
        else
            continue;
    }
    return LABEL_NOT_FOUND;  // when not found
}

guint16 get_std_listing_index (gint t_stock_enum, std_entire_data *destination,
                               guint32 integer_date, guint16 last_element) {

    for (guint16 iter = 0; iter < last_element; iter++) {
        if (integer_date == destination->daily[iter]->int_date)
            return iter; // label found, breaking, returning
        else
            continue;
    }
    return LABEL_NOT_FOUND;  // when not found
}


// this shall return data for all fields in: std_daily_result
 
/*
gfloat get_std_value_by_l_ll_current (guint label_id, guint listing, guint t_std_daily_result) {

    gfloat value = 0.0;
    std_entire_data *source = current->data_source;
 
    //t_std_daily_result field_type = t_std_daily_result;
    switch (t_std_daily_result) {  
        case V_OPEN:
            value = (gfloat) source->daily[listing]->listed[label_id]->v_open;
            break;
        case V_CLOSE:
            value = (gfloat) source->daily[listing]->listed[label_id]->v_close;
            break;
        case V_LOW:
            value = (gfloat) source->daily[listing]->listed[label_id]->v_low;
            break;
        case V_HIGH:
            value = (gfloat) source->daily[listing]->listed[label_id]->v_high;
            break;
        case VOLUME:
            value = (gfloat) source->daily[listing]->listed[label_id]->volume;
            break;
        default:
            // return NULL; // should be impossible :)
            break;
    return value;
    }
}
*/ 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * GLfloat *dup_data_array_by_l_ll_inverted
//~ --------------------------------------------------------------------------------------------------------------------
  
gfloat *dup_data_array_by_l_ll_inverted (guint label_id, guint last_listing, guint range,
                                         gint t_std_daily_result, std_entire_data *source) {

/*
    boundaries check shall be done here
*/
    
    // array elements with lower index are "newer"
    gfloat *gfloat_array = g_malloc0 ((sizeof (gfloat)) * range);
    guint current_listing = last_listing;
 
    switch (t_std_daily_result) {  
   
        case V_OPEN:
            for (guint iter = 0; iter < range; iter++) {
                current_listing = last_listing - iter; // goes "back"
                if (!(source->daily[current_listing]->listed[label_id])) {
                    gfloat_array [iter] = -1;
                    continue; }
                gfloat_array [iter] = (gfloat) source->daily[current_listing]->listed[label_id]->v_open;
            }
            break;
        case V_CLOSE:
            for (guint iter = 0; iter < range; iter++) {
                current_listing = last_listing - iter; // goes "back"
                if (!(source->daily[current_listing]->listed[label_id])) {
                    gfloat_array [iter] = -1;
                    continue; }
                gfloat_array [iter] = (gfloat) source->daily[current_listing]->listed[label_id]->v_close;
            }
            break;
        case V_LOW:
            for (guint iter = 0; iter < range; iter++) {
                current_listing = last_listing - iter; // goes "back"
                if (!(source->daily[current_listing]->listed[label_id])) {
                    gfloat_array [iter] = -1;
                    continue; }
                gfloat_array [iter] = (gfloat) source->daily[current_listing]->listed[label_id]->v_low;
            }
            break;
        case V_HIGH:
            for (guint iter = 0; iter < range; iter++) {
                current_listing = last_listing - iter; // goes "back"
                if (!(source->daily[current_listing]->listed[label_id])) {
                    gfloat_array [iter] = -1;
                    continue; }
                gfloat_array [iter] = (gfloat) source->daily[current_listing]->listed[label_id]->v_high;
            }
            break;
        case VOLUME:
            for (guint iter = 0; iter < range; iter++) {
                current_listing = last_listing - iter; // goes "back"
                if (!(source->daily[current_listing]->listed[label_id])) {
                    gfloat_array [iter] = -1;
                    continue; }
                gfloat_array [iter] = (gfloat) source->daily[current_listing]->listed[label_id]->volume;
            }
            break;
        default:
            // return NULL;
            break;
    }
  
    return gfloat_array;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~ * function for filling display data (uses current settings)    current->
//~ --------------------------------------------------------------------------------------------------------------------


/*
        FILL DISPLAY DATA SHOULD HAVE A SWITCH OF DATA TYPE:

        switch (datatype)
            case STATS:
            case LISTINGS:
            case ANYTHING:
*/
 


// a callbacks seems to be 'a here very okay....'' ?


// this may be moved to structures gl_graph callbacks or somethin

 
void fill_glgraph_display_data (glgraph_display_data *destination, std_entire_data *source) {
 

/*
    GLuint DATA_MAX = source->num_of_listings; // but filled only for each present. present number = Xmax

    GLuint get_ll    = current->get_listing;
    GLuint label_id  = current->get_label;
    
    switch (current->t_std_daily_result) {  

        case V_OPEN:

            for (GLuint iter = 0; (iter < DATA_MAX); iter++) {
                if (!(source->daily[iter+get_ll]->listed[label_id]) || (iter > DATA_MAX) ) {
                    //
                    // stores a value from prevoius day
                    // GLfloat_array [iter] = GLfloat_array [iter - 1];
                    //
                    // function for each type (store prev, store 0, store -1, shall be distinguished (another func)
                    destination [0][iter] = -1;
                    continue;
                }
                GLfloat value = source->daily[iter+get_ll]->listed[label_id]->v_open;

                GLfloat_array [iter] = value; //source->daily[iter+get_ll]->listed[get_l]->v_open;

            }
            break;
        case V_CLOSE:

            break;
        case V_LOW:

            break;
        case V_HIGH:

            break;
        case VOLUME:

            break;
        default:
            // return NULL;
            break;
    }
*/

}



void *GLfloat_get_data_array (GLuint size, GLuint t_std_daily_result, std_entire_data *source,
                              GLuint get_ll, const GLuint label_id) {

    GLfloat *GLfloat_array = g_malloc0 ((sizeof (GLfloat)) * size);

    GLuint DATA_LISTINGS_MAX = source->num_of_listings - get_ll; // iterations boundary

    switch (t_std_daily_result) {  

        case V_OPEN:

            for (GLuint iter = 0; (iter < size); iter++) {
                if (!(source->daily[iter+get_ll]->listed[label_id]) || (iter > DATA_LISTINGS_MAX) ) {
                    //
                    // stores a value from prevoius day
                    // GLfloat_array [iter] = GLfloat_array [iter - 1];
                    //
                    // function for each type (store prev, store 0, store -1, shall be distinguished (another func)
                    GLfloat_array [iter] = -1;
                    continue;
                }
                GLfloat value = source->daily[iter+get_ll]->listed[label_id]->v_open;

                GLfloat_array [iter] = value; //source->daily[iter+get_ll]->listed[get_l]->v_open;

            }
            break;
        case V_CLOSE:

            break;
        case V_LOW:

            break;
        case V_HIGH:

            break;
        case VOLUME:

            break;
        default:
            // return NULL;
            break;
    }


    return GLfloat_array;
}





