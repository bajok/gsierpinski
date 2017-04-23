/*
 *      configuration.c
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
#include "configuration.h"



//~ --------------------------------------------------------------------------------------------------------------------
//~ * initializing configuration
//~ --------------------------------------------------------------------------------------------------------------------

gboolean initialize_configuration () {

    config = g_malloc (sizeof (configuration));
    if (config == NULL) {
        LOG_ERROR ("*config: memory could not be allocated")
        return FALSE;
    } else {
        config->config_filename = g_strdup ("./ginvest.conf");
/*
        config->data_directory  = "./data";
*/
        config->data_directory_default              = g_strdup ("./data/default");
        config->data_directory_newconnect           = g_strdup ("./data/newconnect");
        config->data_directory_wig                  = g_strdup ("./data/wig");
        config->data_pattern_filename_default       = g_strdup ("{int:YYYY}{int:MM}{int:DD}{.ext}");
        config->data_pattern_filename_newconnect    = g_strdup ("{int:YYYY}{int:MM}{int:DD}{.prn}");

/*
        config->data_pattern_data_default           = g_strdup ("{int:666},{int:date},{int:value}");
        * a number in {int:number} means - this field is not present in input file: fill it with - gint number;
*/

        config->window_size_x                       = 1000;
        config->window_size_y                       =  600;
        config->settings_window_size_x              =  200;
        config->settings_window_size_y              =  200;
        config->diagnostic_window_size_x            =  300;
        config->diagnostic_window_size_y            =  400;
        config->statistics_window_size_x            =  900;
        config->statistics_window_size_y            =  777;

        config->graph_width     =  800;
        config->graph_height    =  600;


        config->get_listing = 1;
        config->get_label = 1;

    }

    return TRUE;
}

 

//~ --------------------------------------------------------------------------------------------------------------------

static const gint FIELDNAME_LEN = 20;
//~ .
//~ this function extracts fieldname from a line
static gchar *conf_line_get_fieldname (const gchar *line) {

    gchar **splitted = g_malloc (sizeof (gchar) * FIELDNAME_LEN * 2);
    gchar *fieldname = g_malloc (sizeof (gchar) * FIELDNAME_LEN);
    splitted = g_strsplit (line, "=", 2);
    fieldname = g_strchomp (g_strchug (splitted [0]));
    g_free (splitted);

    return fieldname;
}
//~ .
//~ and this one extracts value
static gchar *conf_line_get_value (const gchar *line) {

    gchar **splitted = g_malloc (sizeof (gchar) * FIELDNAME_LEN * 2);
    gchar *value     = g_malloc (sizeof (gchar) * FIELDNAME_LEN);
    splitted = g_strsplit (line, "=", 2);
    value = g_strchomp (g_strchug (splitted [1]));
    g_free (splitted);

    return value;
}
//~ --------------------------------------------------------------------------------------------------------------------

gboolean conf_check_and_assign_variable (const gchar *line) {

    //~ gchar *
    #ifdef DEBUG_DATA_READ
        #ifdef DEBUG_WITH_EXTENDED_OUTPUT
        DEBUG_LOG_FLOW    (DEBUG_DATA_READ, "conf_check_and_assign_variable", "..")
        #endif
    DEBUG_LOG_STRING  (DEBUG_DATA_READ, " ", "line", line)
    #endif
    
    //~ main window size
    if (g_str_has_prefix (line, "window_size")) {

        gchar *fieldname = g_malloc (sizeof (gchar) * FIELDNAME_LEN);
        gchar *value     = g_malloc (sizeof (gchar) * FIELDNAME_LEN);
        fieldname = g_strdup (conf_line_get_fieldname (line));
        value     = g_strdup (conf_line_get_value (line));

        gchar **splitted = g_malloc (sizeof (gchar) * FIELDNAME_LEN * 2);
        splitted = g_strsplit (value, "x", 2);

        gint width = (gint) g_strtod (splitted [0], NULL);
        gint height = (gint) g_strtod (splitted [1], NULL);

        #ifdef DEBUG_DATA_READ
        DEBUG_LOG_STRING  (DEBUG_DATA_READ, " ", "fieldname", fieldname)
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, " ", "width", width)
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, " ", "height", height)
        #endif

        config->window_size_x = width;
        config->window_size_y = height;

        g_free (splitted);
        g_free (fieldname);
        g_free (value);
 
        return TRUE;
    }
    if (g_str_has_prefix (line, "settings_window_size")) {

        gchar *fieldname = g_malloc (sizeof (gchar) * FIELDNAME_LEN);
        gchar *value     = g_malloc (sizeof (gchar) * FIELDNAME_LEN);
        fieldname = g_strdup (conf_line_get_fieldname (line));
        value     = g_strdup (conf_line_get_value (line));

        gchar **splitted = g_malloc (sizeof (gchar) * FIELDNAME_LEN * 2);
        splitted = g_strsplit (value, "x", 2);

        gint width = (gint) g_strtod (splitted [0], NULL);
        gint height = (gint) g_strtod (splitted [1], NULL);

        #ifdef DEBUG_DATA_READ
        DEBUG_LOG_STRING  (DEBUG_DATA_READ, " ", "fieldname", fieldname)
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, " ", "width", width)
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, " ", "height", height)
        #endif

        config->settings_window_size_x = width;
        config->settings_window_size_y = height;

        g_free (splitted);
        g_free (fieldname);
        g_free (value);

        return TRUE;
    }
    if (g_str_has_prefix (line, "graph_size")) {

        gchar *fieldname = g_malloc (sizeof (gchar) * FIELDNAME_LEN);
        gchar *value     = g_malloc (sizeof (gchar) * FIELDNAME_LEN);
        fieldname = g_strdup (conf_line_get_fieldname (line));
        value     = g_strdup (conf_line_get_value (line));

        gchar **splitted = g_malloc (sizeof (gchar) * FIELDNAME_LEN * 2);
        splitted = g_strsplit (value, "x", 2);

        gint width = (gint) g_strtod (splitted [0], NULL);
        gint height = (gint) g_strtod (splitted [1], NULL);

        #ifdef DEBUG_DATA_READ
        DEBUG_LOG_STRING  (DEBUG_DATA_READ, " ", "fieldname", fieldname)
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, " ", "width", width)
        DEBUG_LOG_INTEGER (DEBUG_DATA_READ, " ", "height", height)
        #endif

        config->graph_width = width;
        config->graph_height = height;

        g_free (splitted);
        g_free (fieldname);
        g_free (value);

        return TRUE;
    }


    //~ else {
        //~ g_prnt ("window_size variable not found in config file, using default %dx%d",
                 //~ conf_window_size_x, conf_window_size_y);
    //~ }
    //~ data directory path
    if (g_str_has_prefix (line, "data_directory")) {

        return TRUE;
    }
    //~ else {
        //~ g_prnt ("data_directory variable not found in config file, using default %s",
                 //~ DATA_DIRECTORY);
    //~ }
    else return FALSE;

    return TRUE; // FALSE - no configurable variable found in given line
}
//~ --------------------------------------------------------------------------------------------------------------------

