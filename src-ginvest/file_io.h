/*
 *      file_io.h
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


#ifndef __file_io_h_
#define __file_io_h_



#include <stdio.h>
#include "gthread_functions.h"


#define CONFIG_FILE         config->config_filename
#define DATA_DIRECTORY      config->data_directory

#define DATA_FILES_MAX      2048

/*
#define PATTERN_FILENAME "{date}.{ext}"
#define PATTERN_FILENAME_NEWCONNECT "{date}.prn"
*/


#define FILENAME_LENGTH_MAX 256
#define FILEPATH_LENGTH_MAX 2048

#define READLEN             1024
#define CSV_FIELDNAME_LEN   20
#define CSV_FILE_PATH_LEN   32


// used only for debugging

#define HANG_ON__LISTEN_TO_YOUR_MIND      gchar stdin_read_character = getchar ();


/*
#define MAX
*/




/*
after file read, data structures shall be read only
*/

gboolean file_io_read_configuration (void);
gboolean file_io_read_data (void);


/*
gboolean file_io_read_megastock_prn_newconnect (void);
*/


#endif //__file_io_h_
