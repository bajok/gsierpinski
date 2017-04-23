/*
 *      gtk_frontend_treeview_widgets.h
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


#ifndef __gtk_frontend_treeview_widgets_h_
#define __gtk_frontend_treeview_widgets_h_



void append_gtkliststore_standard_stats (gint t_stock_enum, std_entire_data *source, guint ll);
void append_gtkliststore_advanced_stats (gint t_stock_enum, std_entire_data *source);
 

/*
GtkTreeView *append_gtktreeview_standard_stats ();
GtkTreeView *append_gtktreeview_advanced_stats ();
*/
  

GtkWidget   *create_std_statistics_treeview_widget    (gint t_stock_enum, std_entire_data *source);
GtkWidget   *create_adv_statistics_treeview_widget    (gint t_stock_enum, std_entire_data *source);
 

 

#endif // __gtk_frontend_treeview_widgets_h_
