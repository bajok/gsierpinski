/*
 *      gtk_frontend_child_windows.h
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


#ifndef __gtk_frontend_child_windows_c_
#define __gtk_frontend_child_windows_c_


#include "data_structures_init.h"
#include "configuration.h"



GtkWidget *append_child_window_settings (const gchar *name);
GtkWidget *append_child_window_statistics (const gchar *name, gint t_stock_enum, std_entire_data *source);
GtkWidget *append_child_window_diagnostic (const gchar *name, gint t_stock_enum, std_entire_data *source);




#endif // __gtk_frontend_child_windows_c_
