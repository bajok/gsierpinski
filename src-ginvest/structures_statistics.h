/*
 *      structures_statistics.h
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


#ifndef __structures_statistics_h_
#define __structures_statistics_h_

#include <glib.h>


/*
#include "file_io.h"
*/


/*
#include <GL/gl.h>
#include <GL/glu.h>
*/

 

// mapping to gchar array defined in .c file


//~ --------------------------------------------------------------------------------------------------------------------
//~ * enum available statistics
//~ --------------------------------------------------------------------------------------------------------------------


/*
statistic enumeration:

  only first (or first and two) columns have constant period length (equal to 1 e.g.)

  the gui is distinguishing also wether to display it or not.

  statistic distinguish is made on iterating to next value  (if iter > 2) continue; 
*/
 
 
typedef enum {
     
    STAT_T_EQUALS,          // int
    STAT_T_EQUALS_T1,       // int
    STAT_T_EQUALS_T2,       // int

    STAT_T_INCREASES,       // int
    STAT_T_INCREASES_T1,    // int
    STAT_T_INCREASES_T2,    // int
 
    STAT_T_DECREASES,       // int
    STAT_T_DECREASES_T1,    // int
    STAT_T_DECREASES_T2,    // int
   
    STAT_T_V_MIN,           // float
    STAT_T_V_MAX,           // float
    STAT_T_V_AVERAGE,       // float
    STAT_T_LEAGUE,          // int
  
    STAT_T_STATISTIC_LAST_INDEX,
  
} t_statistic_type_enum;

// corresponds to :

// const gchar t_stat_name_default [STAT_T_STATISTIC_LAST_INDEX][CSV_FIELDNAME_LEN]

  
 
/*


BOTH SHOULD BE LINKED SOMEHOW
 

*/

/*
typedef enum {

     
    GTYPE_EQUALS,      // int
    GTYPE_INCREASES,   // int
    GTYPE_DECREASES,   // int
    GTYPE_V_MIN,       // float
    GTYPE_V_MAX,       // float
    GTYPE_V_AVERAGE,   // float

    GTYPE_LEAGUE,      // int // has to be after EQU, INC, DEC -- depends on them!
  
    GTYPE_STATISTIC_LAST_INDEX,
  
} t_gtype_statistic_enum;
*/

 
  


//~ --------------------------------------------------------------------------------------------------------------------
//~ * defines 
//~ --------------------------------------------------------------------------------------------------------------------
  
/*
#define T1_PERIOD_MAX 5
*/
#define T1_PERIOD_MAX 22
#define T2_PERIOD_MAX 366
#define T3_PERIOD_MAX 366
  
/*
#define TN_PERIOD_TYPES 4
*/
/*
#define TN_PERIODS_TOTAL (TN_PERIOD_TYPES * STAT_T_STATISTIC_LAST_INDEX)
*/
//#define TN_PERIODS_TOTAL_L (TN_PERIODS_TOTAL + TN_PERIOD_TYPES)


   
//#define DEBUG_STATISTICS
 
  

//~ --------------------------------------------------------------------------------------------------------------------
//~ * structures
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _statistics_parameters statistics_parameters;

struct _statistics_parameters {

    // edge conditions
/*
    guint16     tn_period [4]; // period length value for each type of period
*/
    guint16     t1_period_len;
    guint16     t2_period_len;
    guint16     t3_period_len; // not useed currently
 
}; 
 
 
typedef struct _statistics_data statistics_data;

struct _statistics_data {

    guint16     get_listing;
    guint16     get_listing_range;
    guint16     get_label;

    gboolean    toggle_show_zeroes;

 
    guint16     num_of_t_statistics;

    // pointers are used for easier initialization with zeroes

    guint       gui_columns_total;
    gboolean   *gui_columns_visible_arr;
 
    gchar     **t_stat_name;
    gfloat      tn_stats [STANDARD_LABELS_MAX][STAT_T_STATISTIC_LAST_INDEX];
  
 
/*
    gfloat     *t2_stats [STANDARD_LABELS_MAX];
    gfloat     *t3_stats [STANDARD_LABELS_MAX];
    gfloat     *t4_stats [STANDARD_LABELS_MAX];
*/

};




 
//~ --------------------------------------------------------------------------------------------------------------------
//~ * global func
//~ --------------------------------------------------------------------------------------------------------------------

void statistics_regenerate (gint t_stock_enum, std_entire_data *source);

 


#endif //__structures_statistics_h_
