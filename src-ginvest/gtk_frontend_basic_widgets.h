/*
 *      gtk_frontend_basic_widgets.h
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


#ifndef __gtk_frontend_basic_widgets_h_
#define __gtk_frontend_basic_widgets_h_



/*
    GtkWidget *create_adjustment (const char *name, float min, float max, float step, float value,
                                  void callback (), gpointer data);
*/
    GtkWidget *create_scale_adjustment (const char *name, double min, double max, double step, double value,
                                        gboolean horiz, void callback (), gpointer data);
    GtkWidget *create_spin_button (const char *name, float min, float max, float step, float value,
                                   void callback (), gpointer data);


#endif // __gtk_frontend_basic_widgets_h_
