/*
 *      structures_papers.h
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


#ifndef __structures_papers_h_
#define __structures_papers_h_

#include <glib.h>
#include <GL/gl.h>
#include <GL/glu.h>


/*
#include "structures_glgraph.h"
*/
// #include "configuration.h"




/*
name    type    units   tags
stock_symbol    str     entity.corporation.id.code.stocksymbol  entity.corporation.id
stock_exchange  str     entity.corporation.id.code.stocksymbol  entity.corporation.id entity.corporation.id.code.exchange
date    date    date.ISO    date
stock_price_open    float   currency.usd.nonadj     currency.usd

Opening price, not adjusted for Splits, Dividends or Inflation
stock_price_close   float   currency.usd.nonadj     currency.usd

Closing price, not adjusted for Splits, Dividends or Inflation
stock_price_lo  float   currency.usd.nonadj     currency.usd

Lowest daily traded price, not adjusted for Splits, Dividends or Inflation
stock_price_high    float   currency.usd.nonadj     currency.usd

Highest daily traded price, not adjusted for Splits, Dividends or Inflation
stock_price_adj_close   float   currency.usd.nonadj     currency.usd

Closing price, adjusted for Splits and Dividends but not for Inflation
stock_volume    int     thousand shares / day   rate.finance.trade.stocks

Number of shares traded that day




http://infochimps.org/dataset/stocks_yahoo_NASDAQ

 
*/


/*
#define NEWCONNECT_MAX_DAILY_LISTINGS
*/


//~ --------------------------------------------------------------------------------------------------------------------
//~ * constant defines
//~ --------------------------------------------------------------------------------------------------------------------

#define NEWCONNECT_MAX_DAILY_LISTINGS              (current->listings_max)

#define STANDARD_LABELS_MAX                         1024
#define STANDARD_LISTINGS_MAX                       4096


#define LABEL_NOT_FOUND                             65535
#define GFLOAT_VALUE_UNINITIALIZED                  -99999.0
//#define GFLOAT_VALUE_UNINITIALIZED                  ((-G_MAXFLOAT))

 
#define LISTING_NOT_FOUND                           11sfds4    fge5463

 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * function and function-like macros
//~ --------------------------------------------------------------------------------------------------------------------

#define CSTR_STAT_CURRENT_PERIOD \
        g_strconcat (" current period:  ", (current->data_source)->daily[statdata->get_listing]->char_date, \
                     "    id = ", g_strdup_printf ("%d ", statdata->get_listing), \
                     "    rng = ", g_strdup_printf ("%d ", statdata->get_listing_range), \
                     NULL)

  


/*
#define max(a,b) \
       ({ typeof (a) _a = (a); \
           typeof (b) _b = (b); \
         _a > _b ? _a : _b; })

#define MIN(a,b) ((a)>(b)?(b):(a))

#define GBOOLEAN_ARRAY_NULL (array, size) \
        array = g_malloc0 ((sizeof (gboolean)) * size)

#define GBOOLEAN_ARRAY_ENABLE_ALL (array, size) \
        for (gint iter = 0; iter < size; iter++) array [iter] = TRUE


#define NEWCONNECT_MAX_SHARES_IN_DAILY_LISTING    150
*/


/*
#define NEWCONNECT_MAX_DAILY_LISTINGS             num_of_listings
#define NEWCONNECT_MAX_SHARES_IN_DAILY_LISTING    num_of_labels
*/


/*
statdata->statistics [LABEL][t_statistic_type_enum]
*/ 

typedef enum {

    NEWCONNECT,
    WIG20,

} t_stock_enum;


typedef enum {

    V_OPEN,
    V_HIGH,
    V_LOW,
    V_CLOSE,
    VOLUME,
    DAILY_T_LAST_INDEX,

} t_std_daily_result;



typedef enum {

    YYYY,
    MM,
    DD,

} t_data_enum;
 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * label
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _standard_label standard_label;

struct _standard_label {

    gchar *name;
    guint16 name_len;
/*
    gchar *aux_info;
*/

};

//~ --------------------------------------------------------------------------------------------------------------------
//~ * standard daily listing of one share (open, high, low, close, volume)
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _std_daily_result std_daily_result;

struct _std_daily_result {

    GLfloat                 v_open;
    GLfloat                 v_high;
    GLfloat                 v_low;
    GLfloat                 v_close;
    GLfloat                 volume;
    GLint                   pad;
    // gpointer previous;
    // gpointer next;
};
 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * paper_newconnect_daily
//~ --------------------------------------------------------------------------------------------------------------------
 
typedef struct _std_daily_listing std_daily_listing;

struct _std_daily_listing {

    gint16                  num_of_listed;
    guint32                 int_date;
    gchar                  *char_date;
    std_daily_result      **listed;

};

//~ --------------------------------------------------------------------------------------------------------------------
//~ * all newconnect data
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _std_entire_data std_entire_data;

struct _std_entire_data {

    gboolean                fill_data_with_values_from_previous_listings; // besides first absent listings

    guint16                 num_of_labels;
    guint16                 num_of_listings;

    standard_label        **labels;
    std_daily_listing     **daily;   // pointer to daily listing pointer
};


  

//~ --------------------------------------------------------------------------------------------------------------------
//~ * function prototypes
//~ --------------------------------------------------------------------------------------------------------------------



std_daily_result *create_std_daily_result ();


gboolean initialize_std_daily_result (std_daily_result *share, gfloat v_open, gfloat v_high,
                                      gfloat v_low, gfloat v_close, gfloat volume, gint pad);

gboolean fill_data_with_values_from_previous_listings (gint t_stock_enum, std_entire_data *destination);


 

 
/*
void set_std_value_by_l_ll  (guint label_id, guint listing, gint t_std_daily_result,
                             gint t_stock_enum, std_entire_data *source, gfloat value);
*/


gfloat get_std_value_by_l_ll         (guint label_id, guint listing, gint t_std_daily_result,
                                      gint t_stock_enum, std_entire_data *source);
 
/*
gfloat get_std_value_by_l_ll_current (guint label_id, guint listing, guint t_std_daily_result);
*/
  

guint16 get_std_label_index (gint t_stock_enum, std_entire_data *destination,
                             const gchar *label_name, guint16 last_element);

guint16 get_std_listing_index (gint t_stock_enum, std_entire_data *destination,
                               guint32 integer_date, guint16 last_element);


 
 
gfloat *dup_data_array_by_l_ll_inverted (guint label_id, guint last_listing, guint range,
                                         gint t_std_daily_result, std_entire_data *source);


/*
GLfloat *GLfloat_get_data_array (GLuint size, GLuint t_std_daily_result, std_entire_data *source,
                                 GLuint get_ll, const GLuint label_id);
*/



 



/*
            IFDEF CALLBACKS OR SOMETHIN   TO INCLUDE WITH CALLBACKS.H          OR NOT?
*/


/*
void cb_fill_glgraph_display_data (glgraph_display_data *destination, std_entire_data *source);
*/







#endif //__structures_papers_h_
