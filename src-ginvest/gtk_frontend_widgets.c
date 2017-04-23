/*
 *      gtk_frontend_widgets.c
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


#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gtk_frontend.h"
#include "gtk_callbacks.h"


//~ --------------------------------------------------------------------------------------------------------------------
//~        gtk_drawing_area_widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *main_drawing_area_widget () {

    GtkWidget *stats_above_graph, *stats_graph_yruler, *stats_graph_darea, *stats_graph_xruler;

    GtkWidget *hbox, *vbox = gtk_vbox_new (FALSE, 0);
    GtkWidget *mainbox = gtk_hbox_new (FALSE, 0);

    stats_above_graph = gtk_drawing_area_new ();
    gtk_widget_set_size_request (stats_above_graph, -1, 30);
    gtk_box_pack_start (GTK_BOX (vbox), stats_above_graph, FALSE, FALSE, 0);
//     g_signal_connect (G_OBJECT (stats_above_graph), "expose_event", G_CALLBACK (cb_draw_above_graph), NULL);
    g_signal_connect (G_OBJECT (stats_above_graph), "expose_event", G_CALLBACK (cb_null), NULL);

    /* y ruler and graph */
    hbox = gtk_hbox_new (FALSE, 0);
    stats_graph_yruler = gtk_drawing_area_new ();
    gtk_widget_set_size_request (stats_graph_yruler, 40, -1);
    gtk_box_pack_start (GTK_BOX (hbox), stats_graph_yruler, FALSE, FALSE, 0);
//     g_signal_connect (G_OBJECT (stats_graph_yruler), "expose_event", G_CALLBACK (cb_draw_yruler), NULL);
    g_signal_connect (G_OBJECT (stats_graph_yruler), "expose_event", G_CALLBACK (cb_null), NULL);

    stats_graph_darea = gtk_drawing_area_new ();
    gtk_box_pack_start (GTK_BOX (hbox), stats_graph_darea, TRUE, TRUE, 0);
//     g_signal_connect (G_OBJECT (stats_graph_darea), "expose_event", G_CALLBACK (cb_graph_expose_event), NULL);
    g_signal_connect (G_OBJECT (stats_graph_darea), "expose_event", G_CALLBACK (cb_graph_expose_event), NULL);

    gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);

    /* empty darea and x ruler */
    hbox = gtk_hbox_new (FALSE, 0);
    GtkWidget *clean_darea = gtk_drawing_area_new ();
    gtk_widget_set_size_request (clean_darea, 40, 30);
    gtk_box_pack_start (GTK_BOX (hbox), clean_darea, FALSE, FALSE, 0);
//     g_signal_connect (G_OBJECT (clean_darea), "expose_event", G_CALLBACK (cb_clear_darea), NULL);
    g_signal_connect (G_OBJECT (clean_darea), "expose_event", G_CALLBACK (cb_null), NULL);

    stats_graph_xruler = gtk_drawing_area_new ();
    gtk_widget_set_size_request (stats_graph_xruler, -1, 30);
    gtk_box_pack_start (GTK_BOX (hbox), stats_graph_xruler, TRUE, TRUE, 0);
//     g_signal_connect (G_OBJECT (stats_graph_xruler), "expose_event", G_CALLBACK (cb_draw_xruler), NULL);
    g_signal_connect (G_OBJECT (stats_graph_xruler), "expose_event", G_CALLBACK (cb_null), NULL);

    gtk_box_pack_end (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (mainbox), vbox, TRUE, TRUE, 0);

/*
    // layer switch check buttons
    vbox = gtk_vbox_new (FALSE, 0);

    GtkWidget *checkbt;

    for (int i = 0; i < il_statystyk; i++) {

//         if (i == 0) create a label

        checkbt = gtk_check_button_new_with_label (stat_name [i]);
        if (toggle_graph_layer [i] == TRUE)
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbt), TRUE);
        else
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbt), FALSE);
        g_signal_connect (G_OBJECT (checkbt), "toggled", G_CALLBACK (cb_toggle_graph_layer), GINT_TO_POINTER (i));
        g_object_set (checkbt, "relief", GTK_RELIEF_NONE, NULL);
        gtk_box_pack_start (GTK_BOX (vbox), checkbt, TRUE, TRUE, 0);

        if (i == 0)
            gtk_tooltips_set_tip (GTK_TOOLTIPS (tooltips), checkbt,
                            "mediana pierwszych 4 liczb", "private text");
        else if (i > 0 && i < 5)
            gtk_tooltips_set_tip (GTK_TOOLTIPS (tooltips), checkbt,
                            "mediana kolejnych 4 liczb", "private text");
        else if (i == 5)
            gtk_tooltips_set_tip (GTK_TOOLTIPS (tooltips), checkbt,
                            "mediana parzystych liczb w losowaniu", "private text");
        else if (i == 6)
            gtk_tooltips_set_tip (GTK_TOOLTIPS (tooltips), checkbt,
                            "mediana nieparzystych liczb w losowaniu", "private text");
    }

    gtk_box_pack_start (GTK_BOX (mainbox), vbox, FALSE, FALSE, 0);
*/
    return mainbox;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~ toolbar widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *main_window_toolbar () {

    GtkWidget *toolbar = gtk_toolbar_new ();
    GtkWidget *tool_button;
    GtkWidget *button;
    GtkWidget *separator;

    gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH_HORIZ);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    separator = gtk_vseparator_new ();
    gtk_widget_set_size_request (separator, 60, 0);
    gtk_container_add (GTK_CONTAINER (tool_button), separator);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label ("update database");
//     GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_null), NULL);
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label ("sayonara");
//     GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_app_close), NULL);
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    return toolbar;
}

//~ --------------------------------------------------------------------------------------------------------------------
//~ auxillary toolbar widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *main_window_toolbar_aux () {

    GtkWidget *toolbar = gtk_toolbar_new ();
    GtkWidget *tool_button;
    GtkWidget *button;
    GtkWidget *separator;

    gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH_HORIZ);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_toggle_button_new_with_label ("settings window");
/*
    gtk_toggle_button_new_with_mnemonic ()
*/
//     GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
/*
    gboolean
*/
/*
    gtk_toggle_button_get_active
*/

/*
    g_signal_connect (G_OBJECT (button), "toggled", G_CALLBACK (toggleSwitch), replaygainType);
*/

    g_signal_connect (G_OBJECT (button), "toggled", G_CALLBACK (cb_toggle_widget_display_state),
                                                    GINT_TO_POINTER (CHILD_WINDOW_SETTINGS));
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    // separator
    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    separator = gtk_vseparator_new ();
    gtk_widget_set_size_request (separator, 60, 0);
    gtk_container_add (GTK_CONTAINER (tool_button), separator);

    // button
    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_toggle_button_new_with_label ("statistics window");
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    g_signal_connect (G_OBJECT (button), "toggled", G_CALLBACK (cb_toggle_widget_display_state),
                                                    GINT_TO_POINTER (CHILD_WINDOW_STATISTICS));
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    // separator
    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    separator = gtk_vseparator_new ();
    gtk_widget_set_size_request (separator, 60, 0);
    gtk_container_add (GTK_CONTAINER (tool_button), separator);

    // button
    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_toggle_button_new_with_label ("diagnostic window");
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    g_signal_connect (G_OBJECT (button), "toggled", G_CALLBACK (cb_toggle_widget_display_state),
                                                    GINT_TO_POINTER (CHILD_WINDOW_DIAGNOSTIC));
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    return toolbar;
}
 
//~ --------------------------------------------------------------------------------------------------------------------
//~ statistics window toolbar widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *child_window_statistics_toolbar () {
 
    GtkWidget *toolbar = gtk_toolbar_new ();
    GtkWidget *tool_button;
    GtkWidget *button;
    GtkWidget *separator;
    GtkWidget *hbox; 

    gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH_HORIZ);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label (" update advanced stats ");
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_update_treeview),
                                                    GINT_TO_POINTER (LIST_STORE_ADV_STATS));
    gtk_container_add (GTK_CONTAINER (tool_button), button);
 
    // testing items...

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label ("cb_glgraph_update_display_data (btn) : ");
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_null),
                                                    NULL);
    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label (" DATA");
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_glgraph_update_display_data),
                                                    GINT_TO_POINTER (DISPLAY_DATA));
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label (" STATISTICS");
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_glgraph_update_display_data),
                                                    GINT_TO_POINTER (DISPLAY_STATISTICS));
    gtk_container_add (GTK_CONTAINER (tool_button), button);
 
    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label (" COMBINED");
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_glgraph_update_display_data),
                                                    GINT_TO_POINTER (DISPLAY_COMBINED));
    gtk_container_add (GTK_CONTAINER (tool_button), button);
 
    // 

  
    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    separator = gtk_vseparator_new ();
    gtk_widget_set_size_request (separator, 60, 0);
    gtk_container_add (GTK_CONTAINER (tool_button), separator);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_check_button_new_with_label (" print zeroes ");
 
    gtk_toggle_button_set_active ((GtkToggleButton *) button, GPOINTER_TO_INT (statdata->toggle_show_zeroes));

    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT); 
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_toggle_statistics_data),
                                                    GINT_TO_POINTER (STATDATA_TOGGLE_SHOW_ZEROES));
    gtk_container_add (GTK_CONTAINER (tool_button), button);
 
    
    return toolbar;
}  
 
//~ --------------------------------------------------------------------------------------------------------------------
//~ diagnostic window toolbar widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *child_window_diagnostic_toolbar () {

    GtkWidget *toolbar = gtk_toolbar_new ();
    GtkWidget *tool_button;
    GtkWidget *button;
    GtkWidget *separator;

    gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH_HORIZ);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label ("sayonara");
//     GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_app_close), NULL);
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    separator = gtk_vseparator_new ();
    gtk_widget_set_size_request (separator, 60, 0);
    gtk_container_add (GTK_CONTAINER (tool_button), separator);

    return toolbar;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~ about window
//~ --------------------------------------------------------------------------------------------------------------------

static GtkWidget *menu_item_about () {

    GtkWidget *menu_item = gtk_menu_item_new_with_label ("about");
    g_signal_connect (G_OBJECT (menu_item), "activate", G_CALLBACK (cb_display_about_window), (gpointer) glconfig);

    return menu_item;
}


//~ --------------------------------------------------------------------------------------------------------------------
//~ main menu widget
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *main_window_menu () {

    GtkWidget *menu =                       gtk_menu_new ();
    GtkWidget *menu_bar =                   gtk_menu_bar_new ();
    GtkWidget *root_menu;
    GtkWidget *menu_item;
    GtkWidget *separator;

    /* main menu */
    root_menu = gtk_menu_item_new_with_label ("file");
            gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);
            gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
    separator = gtk_separator_menu_item_new ();
            gtk_container_add (GTK_CONTAINER (menu), separator);
            gtk_widget_set_sensitive (separator, FALSE);
    menu_item = gtk_menu_item_new_with_label ("sayonara");
            gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
            g_signal_connect (G_OBJECT (menu_item), "activate", G_CALLBACK (cb_app_close), NULL);

    /* analiza */
    menu = gtk_menu_new ();
    root_menu = gtk_menu_item_new_with_label ("edit");
            gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);
            gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
    menu_item = gtk_menu_item_new_with_label ("prefs");
            gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
            g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (cb_null), NULL);

    /* about */
    menu = gtk_menu_new ();
    root_menu = gtk_menu_item_new_with_label ("'bout");
            gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);
            gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
    menu_item = gtk_menu_item_new_with_label ("sth");
            gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
            g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (cb_null), NULL);
    menu_item = menu_item_about ();
            gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);


    return menu_bar;
}


