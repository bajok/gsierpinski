/*
 *      gtk_frontend_settings_widgets.h
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


#ifndef __gtk_frontend_settings_widgets_c_
#define __gtk_frontend_settings_widgets_c_



    GtkWidget *verify_input_data_widget (gint t_stock_enum, std_entire_data *source);

    GtkWidget *statdata_settings_widget ();

    GtkWidget *current_settings_widget ();

    GtkWidget *glarea_settings_widget ();

    GtkWidget *gtk_graph_widget ();



#endif // __gtk_frontend_settings_widgets_c_
