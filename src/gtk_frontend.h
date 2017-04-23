/*
 *      gtk_frontend.h
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


#ifndef __gtk_frontend_h_
#define __gtk_frontend_h_



typedef enum {

    MAIN_WINDOW,
    MAIN_WINDOW_TITLE,
    MAIN_WINDOW_SETTINGS,

    // add more widget enum here to have a integer reference to them when passing GPOINTER to callback
 
} t_frontend_widgets_enum;


//~ --------------------------------------------------------------------------------------------------------------------
//~ USER INTERFACE GLOBAL WIDGET POINTERS
//~ --------------------------------------------------------------------------------------------------------------------

typedef struct _frontend_widgets frontend_widgets;

struct _frontend_widgets {

    //~ ----------------------------------------------------------------------------
    //~ main_window
    //~ ----------------------------------------------------------------------------
    GtkWidget *main_window;
    gchar     *main_window_title;
    GtkWidget *main_window_settings;

    guint      window_size_x;
    guint      window_size_y;
    
};
   
  
extern frontend_widgets *UI;


//~ --------------------------------------------------------------------------------------------------------------------
//~ once append_main_window is called it starts every child widget creation
//~ --------------------------------------------------------------------------------------------------------------------

// main window standard widgets
GtkWidget *append_main_window (const gchar *title);




#endif // __gtk_frontend_h
