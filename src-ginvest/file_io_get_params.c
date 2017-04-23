/*
 *      file_io_get_params.c
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

#include "file_io_read.h"



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

 

// preceding function shall not have acces to below SORTING function!

static gint *sort_gchar_array_ascending  (gconstpointer data1, gconstpointer data2) {
    return g_strcmp0 ((const gchar *) data1, (const gchar *) data2);
}
  
//~ --------------------------------------------------------------------------------------------------------------------
//~ get_current_data_structure_parameters
//~ --------------------------------------------------------------------------------------------------------------------

gboolean get_current_data_structure_parameters (gint t_stock_enum, std_entire_data *destination, gchar *path) {

    #ifdef DEBUG_DATA_READ
        DEBUG_LOG_FLOW  (DEBUG_DATA_READ, "get_current_data_structure_parameters", \
                                          "counting files (total listings), looking for labels (total labels)")
    #endif
  
    GFile *directory;
    GFileEnumerator *enumerator;
    GFileInfo *info;
    GError *error;
    gint valid_filenum = 0;

    current->listings_max = valid_filenum;
    current->labels_max = 0;        // initial value, increased each time new label is being found.
                                    // then its final value is being copied to newconnect->num_of_labels
    current->iter_ll            = 0;



    #ifdef DEBUG_DATA_READ
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, "get_current_data_structure_parameters", "t_stock_enum", t_stock_enum)
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, " ", "STANDARD_LABELS_MAX", STANDARD_LABELS_MAX)
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, " ", "STANDARD_LISTINGS_MAX", STANDARD_LISTINGS_MAX)
    #endif

// ---------------------------------------------------------------------------------------------------
// INITIALIZE ALL DATA POINTERS HERE --- ONLY POINTERS WITH PREDEFINED MAX CURRENTLY
// ---------------------------------------------------------------------------------------------------
 
        if (!(destination->labels = (standard_label **)
            g_malloc0 ((sizeof (gpointer)) * STANDARD_LABELS_MAX))) return FALSE;
        for (guint16 iter = 0; iter < STANDARD_LABELS_MAX; iter++) {
            // creating pointer for each label
            if (!(destination->labels[iter] = (standard_label *)
                g_malloc0 ((sizeof (gpointer))))) return FALSE;
            if (!(destination->labels[iter]->name = (gchar *)
                g_malloc0 ((sizeof (gpointer))))) return FALSE;
        }
 
        if (!(destination->daily = (std_daily_listing **)
            g_malloc0 ((sizeof (gpointer)) * STANDARD_LISTINGS_MAX))) return FALSE;
        for (guint16 iter = 0; iter < STANDARD_LISTINGS_MAX; iter++) {

            // allocating predefined number of pointers
            // data structures (to pointers) are initialized only for real total number of read data
            if (!(destination->daily[iter] = (std_daily_listing *)
                g_malloc0 ((sizeof (gpointer))))) return FALSE;
/*
            if (!(destination->daily[iter]->char_date = (gchar *)
                g_malloc0 ((sizeof (gpointer))))) return FALSE;
*/
        } 
    
    // initializing data structure parameters:
    if (!g_uri_parse_scheme (path))     directory = g_file_new_for_path (path);
    else                                directory = g_file_new_for_uri (path);

    if (directory == NULL)              return FALSE;

    error = NULL;
    enumerator = g_file_enumerate_children (directory, "standard::*", 0, NULL, &error);

    if (enumerator == NULL) {
        LOG_ERROR (error->message)
        g_error_free (error);
        error = NULL;
        return FALSE;
    }

    while ((info = g_file_enumerator_next_file (enumerator, NULL, &error)) != NULL) {

        // getting filename
        gchar *name = NULL;
        if ((name                 = g_strdup (g_file_info_get_name (info))) == NULL)
            continue; // skip, no filename

        gchar *file_uri_parrent     = g_strdup (config->data_directory_newconnect);
        gchar *full_filename        = g_strconcat (file_uri_parrent, "/", name, NULL);

        current->data_filename = (GList *) g_list_insert_sorted (current->data_filename,
                                                                (gpointer *) g_strdup (full_filename),
                                                                 sort_gchar_array_ascending);
        // reading file and adding new labels
        GFile *file;
        if (!g_uri_parse_scheme (full_filename)) file = g_file_new_for_path (full_filename);
        else                                     file = g_file_new_for_uri  (full_filename);
        if (file == NULL)                        return FALSE;

        // reading...
        if (read_csv_file_for_parameters (t_stock_enum, destination, file, valid_filenum));
        else return FALSE;
 
        valid_filenum++;  // do something with labels max -- can just count non empty csv lines in each file
        current->listings_max = valid_filenum;

        g_free (name);
        g_free (file_uri_parrent);
        g_free (full_filename);
        g_object_unref (file);
        g_object_unref (info);
    }

    if (error) {
        LOG_ERROR (error->message)
        g_error_free (error);
        error = NULL;
        return FALSE;
    }

    if (!g_file_enumerator_close (enumerator, NULL, &error)) {
        LOG_ERROR (error->message)
        LOG_ERROR ("Error closing enumerator:")
        g_error_free (error);
        error = NULL;
        return FALSE;
    }

    if (valid_filenum < 3) {
        LOG_ERROR ("there should be at least 3 .csv files in data directory")
        return FALSE;
    }

 
    //
    // writing to current parameters:

    destination->num_of_listings    = current->listings_max;
    destination->num_of_labels      = current->labels_max;

    return TRUE;
}







