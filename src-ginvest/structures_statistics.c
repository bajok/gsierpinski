/*
 *      structures_statistics.c
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


/*
#include "structures_statistics_func.h"
*/







 
/*
 *
 * same should be for labels!!!!!!!!!!!!!!!!!!!!!!!!!
 * 
 */




//        DURING FILE READ THERE SHALL BE (CONFIGURABLE, SET TO DEFAULT) OPTION TO:
//        IF THERE IS NO LISTING AT THIS DAY -- VALUE FROM LAST DAY SHALL BE STORED.


 

/*
 should correspond with:
 t_statistic_type_enum
*/

// it is good idea that this enumeration shall be no less than t_statistic_type_enum

const gchar t_stat_name_default [STAT_T_STATISTIC_LAST_INDEX][CSV_FIELDNAME_LEN] = {
    "EQL",
    "EQL1",
    "EQL2",

    "INC",
    "INC1",
    "INC2",

    "DEC",
    "DEC1",
    "DEC2",

    "MIN",
    "MAX",
    "AVG",
    "LEAGUE",
 
    "PAD-a",
    "PAD-b",
    "PAD-c",
    "PAD-d"
};

 
    

/*
wybudowanie miasta nie kosztuje 1000x wiecej niz stworzenie jego makiety w skali 1:1000
*/


// add destination pointer!!




/*

        DODAC RANKING LIGOWY   3 - wzrost, 1 - remis, 0 - spadek

*/
 
 
//  if (data_array [iter] == GFLOAT_VALUE_UNINITIALIZED) continue;

  
static gfloat calc_average (gfloat *data_array, guint data_size) {

    gfloat value = GFLOAT_VALUE_UNINITIALIZED;
    gfloat total = 0;
    for (guint iter = 0; iter < data_size; iter++) 
        total += data_array [iter];
    value = (gfloat) total / (gfloat) data_size;
    return value;
}


// next_iter in this functions means previous value as data_arrays are being read inverted

static gfloat calc_equals (gfloat *data_array, guint data_size, guint period_length) {
 
    gfloat value = 0.0;
    guint  next_iter = period_length;
    for (guint iter = 0; (iter < data_size - 1) && (data_size > next_iter); iter += period_length) {
        if ((data_array [iter]) == (data_array [next_iter]))
            value += 1.0;
        next_iter += period_length;
    }
    return value;
}
 

static gfloat calc_increases (gfloat *data_array, guint data_size, guint period_length) {
 
    gfloat value = 0.0;
    guint  next_iter = period_length;
    for (guint iter = 0; (iter < data_size - 1) && (data_size > next_iter); iter += period_length) {
        if ((data_array [iter]) > (data_array [next_iter]))
            value += 1.0;
        next_iter += period_length;
    }
    return value;
}

static gfloat calc_decreases (gfloat *data_array, guint data_size, guint period_length) {
 
    gfloat value = 0.0;
    guint  next_iter = period_length;
    for (guint iter = 0; (iter < data_size - 1) && (data_size > next_iter); iter += period_length) {
        if ((data_array [iter]) < (data_array [next_iter]))
            value += 1.0;
        next_iter += period_length;
    }
    return value;
}


static gfloat get_minimum (gfloat *data_array, guint data_size) {

    gfloat value = GFLOAT_VALUE_UNINITIALIZED;
    for (guint iter = 0; iter < data_size - 1; iter++) 
        if (data_array [iter] < data_array [iter + 1])
            value = data_array [iter];
    return value;
}

static gfloat get_maximum (gfloat *data_array, guint data_size) {

    gfloat value = GFLOAT_VALUE_UNINITIALIZED;
    for (guint iter = 0; iter < data_size - 1; iter++) 
        if (data_array [iter] < data_array [iter + 1])
            value = data_array [iter];
    return value;
}
 
// league points may be also --- for 3 points for highest % increase, 1 for any increase, 0 for loss. 
static gfloat calc_league_points (gfloat *data_array, guint data_size) {

    gfloat value = GFLOAT_VALUE_UNINITIALIZED;
    for (guint iter = 0; iter < data_size - 1; iter++) {
        if      (data_array [iter] < data_array [iter + 1])
            continue;
        else if (data_array [iter] == data_array [iter + 1])
            value += 1.0;
        else if (data_array [iter] > data_array [iter + 1])
            value += 3.0;
    }
    return value;
}

  
  

static void calculate_statistics_for_label (guint label_id, gint t_std_daily_result,
                                            gint t_stock_enum, std_entire_data *source) {

    #ifdef DEBUG_STATISTICS
    DEBUG_LOG_FLOW      (DEBUG_STATISTICS, "calculate_statistics_for_label", " . ")
    DEBUG_LOG_INTEGER   (DEBUG_STATISTICS, " ", "label_id", label_id)
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_INTEGER   (DEBUG_STATISTICS, " ", "t_std_daily_result", t_std_daily_result)
    DEBUG_LOG_INTEGER   (DEBUG_STATISTICS, " ", "t_stock_enum", t_stock_enum)
    DEBUG_LOG_POINTER   (DEBUG_STATISTICS, " ", "(std_entire_data *) source", source)
    #endif 
    #endif 

    //gfloat *data_array; // data may be initially extracted?
    t_statistic_type_enum stat_enum     = 0;    // MAX: STAT_T_STATISTIC_LAST_INDEX
    gint                  period_type   = -1;
    guint                 periods_total = 0;
    guint                 listing       = statdata->get_listing;
    guint                 listing_range = statdata->get_listing_range;
    if                   (listing_range > listing)
                          listing_range = listing;
    gfloat               *data_array    = dup_data_array_by_l_ll_inverted (label_id,
                                          listing, listing_range, t_stock_enum, source);

    #ifdef DEBUG_STATISTICS
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_INTEGER (DEBUG_STATISTICS, " ", "statdata->get_listing", statdata->get_listing)
    DEBUG_LOG_INTEGER (DEBUG_STATISTICS, " ", "statdata->get_listing_range", statdata->get_listing_range)
    DEBUG_LOG_STRING  (DEBUG_STATISTICS, " ", "source->labels[label_id]->name", source->labels[label_id]->name)        
    DEBUG_LOG_FLOAT_ARRAY (DEBUG_STATISTICS, "input", "data_array [] = ", data_array, listing_range)
    #endif
    #endif
 
    // for each column (period stats with separators - labels)
    // means for each statistic (separated with its label)
    for (guint stat_iter = 0; stat_iter < STAT_T_STATISTIC_LAST_INDEX; stat_iter++) {
 
        if (statdata->gui_columns_visible_arr [stat_iter] = TRUE) {

            gfloat output_value = GFLOAT_VALUE_UNINITIALIZED;

            switch (stat_enum) {
   
                //~  STAT_T_EQUALS
                case STAT_T_EQUALS: // for each period in range
                    output_value    = calc_equals (data_array, listing_range, 1);
                    break; 
                case STAT_T_EQUALS_T1: // for each period in range
                    output_value    = calc_equals (data_array, listing_range, statparams->t1_period_len);
                    break; 
                case STAT_T_EQUALS_T2: // for each period in range
                    output_value    = calc_equals (data_array, listing_range, statparams->t2_period_len);
                    break; 
 
                //~  STAT_T_INCREASES
                case STAT_T_INCREASES:
                    output_value    = calc_increases (data_array, listing_range, 1);
                    break;
                case STAT_T_INCREASES_T1:
                    output_value    = calc_increases (data_array, listing_range, statparams->t1_period_len);
                    break;
                case STAT_T_INCREASES_T2:
                    output_value    = calc_increases (data_array, listing_range, statparams->t2_period_len);
                    break;

                //~  STAT_T_DECREASES
                case STAT_T_DECREASES:
                    output_value    = calc_decreases (data_array, listing_range, 1);
                    break;
                case STAT_T_DECREASES_T1:
                    output_value    = calc_decreases (data_array, listing_range, statparams->t1_period_len);
                    break;
                case STAT_T_DECREASES_T2:
                    output_value    = calc_decreases (data_array, listing_range, statparams->t2_period_len);
                    break;
 
                //~  STAT_T_V_MIN
                case STAT_T_V_MIN:
                    output_value    = get_minimum (data_array, listing_range);
                    break;
 
                //~  STAT_T_V_MAX
                case STAT_T_V_MAX:
                    output_value    = get_maximum (data_array, listing_range);
                    break;

                //~  STAT_T_V_AVERAGE
                case STAT_T_V_AVERAGE:
                    output_value    = calc_average (data_array, listing_range);
                    break;

                //~  STAT_T_LEAGUE
                case STAT_T_LEAGUE:
                    output_value    = calc_league_points (data_array, listing_range);
                    break;

                default:
                    #ifdef DEBUG_STATISTICS
                    DEBUG_LOG_ERROR (DEBUG_STATISTICS, "calculate_statistics_for_label", \
                                                       "no such statistic!")
                    DEBUG_LOG_INTEGER (DEBUG_STATISTICS, "calculate_statistics_for_label", "stat_iter", stat_iter)
                    #endif
                    break;
            }
     
            // write acquired value:
            statdata->tn_stats[label_id][stat_enum] = output_value;
             
/*
            #ifdef DEBUG_STATISTICS_CALC
            if ((listing > 22) && (listing < 25)) {
                g_prnnt (" d   ll = %d  r = %d  pl (%d) = %d \n", listing, listing_range, period_type, period_length);  
                g_prnnt (" d    stat (%d) = %f\n", stat_enum, output_value);
            }
            #endif
*/
            // do a next statistic
            stat_enum++;
        }
    }

    g_free (data_array); // freeing data
}
 


//~ --------------------------------------------------------------------------------------------------------------------
//~ * initialize_daily_newconnect_share
//~ --------------------------------------------------------------------------------------------------------------------


void statistics_regenerate (gint t_stock_enum, std_entire_data *source) {

/*
    for (guint period_t_iter = 0; period_t_iter < TN_PERIOD_TYPES; period_t_iter++) {
*/


    // for each label
    for (guint index = 0; index < (source->num_of_labels); index++) {

/*
        if (index < 22) continue; // get only 2 ----- may be a MACRO
        if (index > 25) continue;
*/
    
        // there shall be UI integration flag -- DO or NOT -- count statistics for unused columns
        calculate_statistics_for_label (index, current->t_std_daily_result, t_stock_enum, source);
  
    }

 


    /*
            for (guint stat_enum = 0; stat_enum < STAT_T_STATISTIC_LAST_INDEX; stat_enum++) 
                statdata->t1_stats[index][stat_enum] = 
                    (gfloat) get_statistic (stat_enum, t1_period, t_stock_enum, source);
    */


/*
    statdata->t1_stats[index][stat_enum]
*/



}

