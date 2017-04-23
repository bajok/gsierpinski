/*
 *      file_io_read.c
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
#include <gio/gio.h>
#include <stdlib.h> /* exit */

#include "data_structures_init.h"
//#include "structures_papers.h"
//#include "configuration.h"

#include "file_io.h"
#include "file_io_read.h"


// may be easily read from configuration file

//~ --------------------------------------------------------------------------------------------------------------------
//~            get_csv_fields
//~ --------------------------------------------------------------------------------------------------------------------

static gchar **get_csv_fields (gint t_stock_enum, const gchar *line, int number_of_fields) {

    gchar **splitted = g_malloc0 (sizeof (gchar) * CSV_FIELDNAME_LEN * 2);
    splitted = g_strsplit (line, ",", 7);
    return splitted;
}



// error is here:

// checking for given label in available label array

//~ --------------------------------------------------------------------------------------------------------------------
//~ read_csv_from_pattern (line read) -- one day summary for one LABEL (share)
//~ --------------------------------------------------------------------------------------------------------------------
/*
static gint find_gchar_in_gchar_array  (gconstpointer data1, gconstpointer data2) {
    return g_strcmp0 (
        (const gchar *) data1,
        (const gchar *) data2);
}
*/

/*
    void                g_log                           (const gchar *log_domain,
                                                         GLogLevelFlags log_level,
                                                         const gchar *format,
                                                         ...);
*/




//~ --------------------------------------------------------------------------------------------------------------------
//~      read_set_csv_values_from_line
//~ --------------------------------------------------------------------------------------------------------------------

static
gboolean read_set_csv_values_from_line (gint t_stock_enum, std_entire_data *destination,
                                             const gchar *line, gint current_listing, guint line_no) {

    // get array of fields from line
    gchar **fields          = get_csv_fields (t_stock_enum, line, 7);
    gfloat *float_values    = g_malloc0 (sizeof (gfloat)   *      7);
    float_values [2] = (gfloat) g_ascii_strtod (fields [2], NULL);
    float_values [3] = (gfloat) g_ascii_strtod (fields [3], NULL);
    float_values [4] = (gfloat) g_ascii_strtod (fields [4], NULL);
    float_values [5] = (gfloat) g_ascii_strtod (fields [5], NULL);
    float_values [6] = (gfloat) g_ascii_strtod (fields [6], NULL);


    // first field is a date
    guint32 int_date        = (guint32) g_strtod (fields [1], NULL);
    guint16 get_listing     = get_std_listing_index (t_stock_enum, destination,
                                                     int_date, destination->num_of_listings);

    // and for label from current line
    gchar  *label_name      = g_strdup (fields [0]);
    guint16 get_label       = get_std_label_index   (t_stock_enum, destination,
                                                     label_name, destination->num_of_labels);

    // if listing is new
    if (get_listing == 65535) { // write new listing date
        get_listing = current->iter_ll;
        destination->daily[get_listing]->int_date = int_date;
        current->iter_ll++;
    }

    // if label is new? -- labels were initialized while searching for parameters
    if (get_label == 65535) return FALSE; // unidentified label is rather not welcome here as they were initialized
 
    current->get_listing = get_listing;   // as listing has been found

 
    if (initialize_std_daily_result   (destination->daily[get_listing]->listed[get_label],
                                       float_values [2],
                                       float_values [3],
                                       float_values [4],
                                       float_values [5],
                                       float_values [6],
                                       0));

    #ifdef DEBUG_DATA_READ
        #ifdef DEBUG_WITH_EXTENDED_OUTPUT
        gchar *line_no_string = g_strdup_printf ("%d", (guint) line_no);
        DEBUG_LOG_FLOAT_ARRAY (DEBUG_DATA_READ, " ", "float_values [7] = ", float_values, 7)
        g_free (line_no_string);
        #endif
    #endif

 
    g_free (label_name);
    g_free (float_values);
    g_strfreev (fields);

    return TRUE;
} 

/*
// change megastock name to generic?
*/
//~ --------------------------------------------------------------------------------------------------------------------
//~      read_csv_file
//~ --------------------------------------------------------------------------------------------------------------------
 
gboolean read_csv_file (gint t_stock_enum, std_entire_data *destination,
                        GFile *file, guint file_index) {

    #ifdef DEBUG_DATA_READ
        #ifdef DEBUG_WITH_EXTENDED_OUTPUT
        DEBUG_LOG_FLOW    (DEBUG_DATA_READ, "read_csv_file", "reading data from file...")
        DEBUG_LOG_STRING  (DEBUG_DATA_READ, " ", "g_file_get_basename (file)", g_file_get_basename (file))
        // DEBUG_LOG_INTEGER (DEBUG_DATA_READ, "read_csv_file", "file_index", file_index)
        #endif
    #endif 

    GFileInputStream *fis;
    GDataInputStream *dis;
    GError *err = NULL;
    gchar *line;
    gsize readlen = READLEN;
    guint current_line = 0; // valid_label

    fis = g_file_read (file, NULL, &err);
    dis = g_data_input_stream_new (G_INPUT_STREAM (fis));
    if (!fis || !dis) {
        LOG_ERROR ("Failed to open GFileInputStream or GDataInputStream")
        LOG_ERROR (err->message)
        g_object_unref (file);
        return FALSE;
    }

    while ((line = g_data_input_stream_read_line (dis, &readlen, NULL, &err)) != NULL) {

        // skip comment lines
        if (g_str_has_prefix (line, "#") == TRUE || readlen == 0) {
            g_free (line);
            readlen = READLEN;
            continue;
        }
 
        // reading and setting global variables
        if (read_set_csv_values_from_line (t_stock_enum, destination, line, file_index, current_line)) {
            g_free (line);
            readlen = READLEN;
            current_line++;
            continue;
        }
        g_free (line);
        readlen = READLEN;
    }
    g_object_unref (dis);
    g_object_unref (fis);


    // converting date to cstring
    g_ascii_dtostr (destination->daily[file_index]->char_date, CSV_FIELDNAME_LEN,
                    (gdouble) destination->daily[file_index]->int_date);
    // more operations on input date shall be made here...

    #ifdef DEBUG_DATA_READ
    #ifdef DEBUG_WITH_EXTENDED_OUTPUT
    DEBUG_LOG_STRING  (DEBUG_DATA_READ, " ", "destination->daily[file_index]->char_date", \
                                              destination->daily[file_index]->char_date)
    // DEBUG_LOG_INTEGER (DEBUG_DATA_READ, "read_csv_file", "file_index", file_index)
    #endif
    #endif
 
    return TRUE;
}



/*
static gint get_or_append_label_index_from_line (const gchar *line) {
    gint index = 0;
}
*/


/*
// change megastock name to generic? 
*/
//~ --------------------------------------------------------------------------------------------------------------------
//~      read_csv_file_for_parameters - OK
//~ --------------------------------------------------------------------------------------------------------------------

gboolean read_csv_file_for_parameters (gint t_stock_enum, std_entire_data *destination,
                                       GFile *file, guint file_index) {

    #ifdef DEBUG_DATA_READ
    DEBUG_LOG_FLOW      (DEBUG_DATA_READ, "read_csv_file_for_parameters", "reading file structure...")
    #endif
   
    GFileInputStream *fis;
    GDataInputStream *dis;
    GError *err = NULL;
    gchar *line;
    //~ GString *gsline;
    gsize readlen = READLEN;

    fis = g_file_read (file, NULL, &err);
    dis = g_data_input_stream_new (G_INPUT_STREAM (fis));

    if (!fis || !dis) {
        LOG_ERROR ("Failed to open GFileInputStream or GDataInputStream")
        LOG_ERROR (err->message)
        g_object_unref (file);
        return FALSE;
    }

    guint32 integer_date;

    while ((line = g_data_input_stream_read_line (dis, &readlen, NULL, &err)) != NULL) {
        /*
            looking for new labels and possibly for other params
        */
        gchar **fields      = get_csv_fields (t_stock_enum, line, 7);
        gchar  *read_label  = g_strdup (fields [0]);
        guint16 index       = get_std_label_index (t_stock_enum, destination, read_label, current->labels_max + 1);

        if (index == LABEL_NOT_FOUND) { // no such one: create new one

            index = (guint16) current->labels_max;
            if (t_stock_enum == NEWCONNECT) {

                destination->labels[index]->name         = g_strdup (read_label);
                //newconnect->labels [index]->name_len    = g_strdup (read_label);
            }
/*
            if (t_stock_enum == WIG20)
                LOG_INFO ("wig20label")
            else // should not happen
                return FALSE;
*/ 

            index++; // label added, increasing max
            current->labels_max = index;
        }
        else { // index is present:

            // do nothing?
        }

        g_free (read_label);
        g_strfreev (fields);
        g_free (line);
        readlen = READLEN;
    }


/*
    guint get_listing = get_std_listing_index (t_stock_enum, destination, integer_date, current->listings_max + 1);
    g_prnt ("get listing = %d\n", get_listing);
*/

    // if none - create new one

    g_object_unref (dis);
    g_object_unref (fis);

    return TRUE;
}


// preceding function shall not have acces to below SORTING function!

/*
static gint sort_gchar_array_ascending  (gconstpointer data1, gconstpointer data2) {
    return g_strcmp0 ((const gchar *) data1, (const gchar *) data2);
}
*/

