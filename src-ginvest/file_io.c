/*
 *      file_io.c
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
#include "structures_papers.h"
#include "configuration.h"

#include "file_io.h"
#include "file_io_read.h"
#include "file_io_get_params.h"


//~ --------------------------------------------------------------------------------------------------------------------
//~ reading bossa.pl prn daily file
//~ --------------------------------------------------------------------------------------------------------------------


/*
const gint READLEN = 1024;
*/


//~ data reading handlers for: newconnect, wig, wig20, etc
//~ ..
//~ each one is another function and takes proper pattern from config file
//~ ..
//~ config file stores number of indexes or data display types
//~ ..
//~ each defined index has its own patten
//~ ..
//~ indexes names are defined like that:                    index_1_name = "newconnect"
//~ ..
//~ for this name is used pattern defined in:               index_1_pattern = "[date], [value], [value], [etc]"
//~ ..
//~ and path for data:                                      index_1_datapath = "./data/newconnect"
//~ ..


//~ --------------------------------------------------------------------------------------------------------------------
//~ reading all data
//~ --------------------------------------------------------------------------------------------------------------------

/*
static void list_file_attributes_from_file_info (GFileInfo *info) {

    gchar **attributes = NULL;
    attributes = g_file_info_list_attributes (info, NULL);
    for (int iter = 0; attributes [iter] != NULL; iter++)
        g_prnt ("%s ", attributes [iter]);
}
*/ 


static gboolean file_io_read_std_data (gint t_stock_enum, std_entire_data *destination) {

    #ifdef DEBUG_DATA_READ
    DEBUG_LOG_FLOW      (DEBUG_DATA_READ, "file_io_read_std_data", "reading data...")
    DEBUG_LOG_INTEGER   (DEBUG_DATA_READ, " ", "t_stock_enum", t_stock_enum)
    DEBUG_LOG_POINTER   (DEBUG_DATA_READ, " ", "(std_entire_data *)", destination)
    #endif

    GFile *directory;
    GError *error = NULL;
    // data directory:

    current->t_stock_enum = t_stock_enum;       // at the beginning of reading (or end) setting current stock data type

    if (t_stock_enum == NEWCONNECT)
        current->data_directory = g_strdup (config->data_directory_newconnect);



    if (!g_uri_parse_scheme (current->data_directory))    directory = g_file_new_for_path (current->data_directory);
    else                                                  directory = g_file_new_for_uri (current->data_directory);

    if (directory == NULL)
    return FALSE;

    if  (get_current_data_structure_parameters (t_stock_enum, destination, current->data_directory)) {

        // additinal structure params:
/*
        current->listing_older  = 0;
        current->listing_newer  = current->listings_max;
*/

        current->get_listing = 0;
        current->get_label = 0;

        current->color [0] = 0;
        current->color [1] = 0.5;
        current->color [2] = 0.8;
        current->color [3] = 0.9;

        #ifdef DEBUG_DATA_READ
        DEBUG_LOG_FLOW      (DEBUG_DATA_READ, "file_io_read_std_data", "pointers initialized with params:")
        DEBUG_LOG_STRING    (DEBUG_DATA_READ, " ", "data_directory", current->data_directory)
        DEBUG_LOG_INTEGER   (DEBUG_DATA_READ, " ", "listings_max", current->listings_max)
        DEBUG_LOG_INTEGER   (DEBUG_DATA_READ, " ", "labels_max", current->labels_max)
        DEBUG_LOG_INTEGER   (DEBUG_DATA_READ, " ", "t_stock_enum", current->t_stock_enum)
        #endif
    }
    else {
        LOG_ERROR ("data parameters cannot be determined")
        return FALSE;
    }
 
    if (initialize_stage2_data_pointers (t_stock_enum, destination)) {
        #ifdef DEBUG_DATA_READ
            DEBUG_LOG_FLOW (DEBUG_DATA_READ, "file_io_read_megastock_data", "data pointers initialized")
        #endif
    }
    else return FALSE;
  
    // assuming file list is sorted properly
    for (gint iter = 0; iter < current->listings_max; iter++) {

        gchar *filename = g_list_nth_data ((GList *) current->data_filename, iter);

        GFile *data_file;
        if (!g_uri_parse_scheme (filename))
            data_file = g_file_new_for_path (filename);
        else
            data_file = g_file_new_for_uri (filename);
        if (data_file == NULL) continue;

        if (read_csv_file (t_stock_enum, destination, data_file, iter));
        else {
            gchar *error_string = g_strdup_printf ("data reading terminated: %s", error->message);
            LOG_ERROR (error_string)
            g_free (error_string);
            return FALSE;  // this breaks reading data!
        }
        g_free (filename);
        g_object_unref (data_file);
    }
    g_object_unref (directory);

    return TRUE;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~
//~ --------------------------------------------------------------------------------------------------------------------

//~ --------------------------------------------------------------------------------------------------------------------
//~ file input - read data
//~ --------------------------------------------------------------------------------------------------------------------

gboolean file_io_read_data (void) {

/*
    for t_stock_enum read data
*/
    #ifdef DEBUG_DATA_READ
    DEBUG_LOG_FLOW      (DEBUG_DATA_READ, "file_io_read_data", "reading all data...")
    #endif


/* 
    config->current_t_stock_enum
*/

    if (!(newconnect = (std_entire_data *)
            g_malloc ((sizeof (std_entire_data))))) return FALSE;

    if  (file_io_read_std_data (NEWCONNECT, newconnect)) {

        newconnect->fill_data_with_values_from_previous_listings = TRUE;
 
        if (fill_data_with_values_from_previous_listings (NEWCONNECT, newconnect)) {
        #ifdef DEBUG_DATA_READ
            DEBUG_LOG_FLOW (DEBUG_DATA_READ, "file_io_read_data", \
                                             "fill_data_with_values_from_previous_listings () = TRUE")
        #endif
        }
        else {
        #ifdef DEBUG_DATA_READ
            DEBUG_LOG_FLOW (DEBUG_DATA_READ, "file_io_read_data", \
                                             "fill_data_with_values_from_previous_listings () = FALSE")
        #endif
        }
        LOG_INFO ("newconnect data succesfully read.")
    }
    else {
        LOG_ERROR ("reading of standard .csv file based data failed!")
        return FALSE;
    }

/*
    if  (file_io_read_std_data (WIG20, config->data_wig20_directory))
        g_prnt ("\n *  data succesfully read...\n");
    else
        g_prnt ("\n * there was an error during data reading...\n");
*/

    return TRUE;
}




//~ --------------------------------------------------------------------------------------------------------------------
//~ config file reading
//~ --------------------------------------------------------------------------------------------------------------------

gboolean file_io_read_configuration (void) {

    #ifdef DEBUG_DATA_READ
    DEBUG_LOG_FLOW      (DEBUG_DATA_READ, "file_io_read_configuration", "reading configuration file...")
    #endif

    GFile *file;
    GFileInputStream *fis;
    GDataInputStream *dis;
    GError *err = NULL;
    gchar *line;
    //~ GString *gsline;
    gsize readlen = READLEN;

    #ifdef DEBUG_DATA_READ
        DEBUG_LOG_STRING (DEBUG_DATA_READ, " ", "filename: ", CONFIG_FILE)
    #endif

    if (!g_uri_parse_scheme (CONFIG_FILE)) {
        file = g_file_new_for_path(CONFIG_FILE);
    } else {
        file = g_file_new_for_uri(CONFIG_FILE);
    }

    fis = g_file_read (file, NULL, &err);
    dis = g_data_input_stream_new (G_INPUT_STREAM (fis));

    if (!fis || !dis) {
        LOG_ERROR ("Cannot read configuration file!")
        LOG_ERROR (CONFIG_FILE)
        LOG_ERROR (err->message)
        g_object_unref (file);
        return FALSE;
    }

    gint line_num = 0;
    while ((line = g_data_input_stream_read_line (dis, &readlen, NULL, &err)) != NULL) {

        line_num++;
        /* skip comment lines */
        if (g_str_has_prefix (line, "#") == TRUE || readlen == 0) {
            g_free (line);
            readlen = READLEN;
            continue;
        }

        /* reading and setting global variables */
        if (conf_check_and_assign_variable (line)) {
            //~ g_prnt ("%d:\t%s, (readlen=%d)\n", line_num, line, (gint) readlen);
            //~ g_string_free (gsline, TRUE);
            g_free (line);
            readlen = READLEN;
            continue;
        }
        g_free (line);
        readlen = READLEN;
    }
    g_object_unref(dis);
    g_object_unref(fis);
    g_object_unref(file);

    return TRUE;
}

