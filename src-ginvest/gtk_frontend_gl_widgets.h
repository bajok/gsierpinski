/*
 *      gtk_frontend_gl_widgets.h
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


#ifndef __gtk_frontend_gl_widgets_h_
#define __gtk_frontend_gl_widgets_h_


    GtkWidget *main_gtkglext_context_widget ();
    //~ GtkWidget *gtkglext_context_widget (GdkGLConfig *glconfig);

    GtkWidget *menu_item_about ();

    GtkWidget *main_about_window (GdkGLConfig *glconfig);


#endif // __gtk_frontend_gl_widgets_h_
