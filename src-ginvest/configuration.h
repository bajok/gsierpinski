/*
 *      configuration.h
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


#ifndef __configuration_h_
#define __configuration_h_


#include <glib.h>
#include "file_io.h"


gboolean conf_check_and_assign_variable (const gchar *line);

gboolean initialize_configuration ();


typedef struct _configuration configuration;

struct _configuration {

    gchar *config_filename;
/*
    gchar *data_directory;
*/
    gchar *data_directory_default;
    gchar *data_directory_newconnect;
    gchar *data_directory_wig;
    gchar *data_pattern_filename_default;
    gchar *data_pattern_filename_newconnect;

    guint window_size_x;
    guint window_size_y;
    guint settings_window_size_x;
    guint settings_window_size_y;
    guint diagnostic_window_size_x;
    guint diagnostic_window_size_y;
    guint statistics_window_size_x;
    guint statistics_window_size_y;

    guint graph_width;
    guint graph_height;


    guint16 get_listing;
    guint16 get_label;

};


#endif // __configuration_h_

