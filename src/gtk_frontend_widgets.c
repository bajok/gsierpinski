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
/*
#include <GL/gl.h>
#include <GL/glu.h>
*/
#include "gtk_frontend.h"
#include "gtk_frontend_basic_widgets.h"
#include "gtk_callbacks.h"
#include "data_structures_init.h"



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
    button = gtk_button_new_with_label ("cb_null");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_null), NULL);
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    separator = gtk_vseparator_new ();
    gtk_widget_set_size_request (separator, 60, 0);
    gtk_container_add (GTK_CONTAINER (tool_button), separator);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label ("  -  s a y o n a r a  -  ");
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
    button = gtk_toggle_button_new_with_label ("show settings");
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    g_signal_connect (G_OBJECT (button), "toggled", G_CALLBACK (cb_toggle_widget_display_state),
                                                    GINT_TO_POINTER (MAIN_WINDOW_SETTINGS));
    gtk_container_add (GTK_CONTAINER (tool_button), button);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    separator = gtk_vseparator_new ();
    gtk_widget_set_size_request (separator, 60, 0);
    gtk_container_add (GTK_CONTAINER (tool_button), separator);

    tool_button = (GtkWidget*) gtk_tool_item_new ();
    gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
    button = gtk_button_new_with_label ("reset sierpinski vertices");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_reset_data), GINT_TO_POINTER (SIERPINSKI_VERTICES));
    gtk_container_add (GTK_CONTAINER (tool_button), button);
  
    return toolbar;
}
  
 
//~ --------------------------------------------------------------------------------------------------------------------
//~ about window
//~ --------------------------------------------------------------------------------------------------------------------

/*
static GtkWidget *menu_item_about () {

    GtkWidget *menu_item = gtk_menu_item_new_with_label ("about");
    g_signal_connect (G_OBJECT (menu_item), "activate", G_CALLBACK (cb_display_about_window), (gpointer) glconfig);

    return menu_item;
}
*/


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
    root_menu = gtk_menu_item_new_with_label ("gsierpinski");
            gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);
            gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
    separator = gtk_separator_menu_item_new ();
            gtk_container_add (GTK_CONTAINER (menu), separator);
            gtk_widget_set_sensitive (separator, FALSE);
    menu_item = gtk_menu_item_new_with_label ("sayonara");
            gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
            g_signal_connect (G_OBJECT (menu_item), "activate", G_CALLBACK (cb_app_close), NULL);

    /* about */
    menu = gtk_menu_new ();
    root_menu = gtk_menu_item_new_with_label ("'bout");
            gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);
            gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
    menu_item = gtk_menu_item_new_with_label ("sth");
            gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
            g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (cb_null), NULL);

    return menu_bar;
}
 
 

//~ --------------------------------------------------------------------------------------------------------------------
//~ settings
//~ --------------------------------------------------------------------------------------------------------------------

GtkWidget *main_window_settings_widget () {

    GtkWidget *settings_widget = gtk_hbox_new (FALSE, 0);
    GtkWidget *frame;
    GtkWidget *hbox, *hbox2; // hbox2 - second level hbox

    GtkWidget *adj;
    GtkWidget *vbox;
    GtkWidget *label;

/*
    spin buttons for colors!
    color fade spin buttons
*/

    frame = gtk_frame_new ("sierpinski");
    hbox = gtk_hbox_new (FALSE, 10);

    gtk_container_add (GTK_CONTAINER (settings_widget), frame);
    gtk_container_add (GTK_CONTAINER (frame), hbox);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);

    // a label

        adj = create_spin_button ("sierpinski depth", 1.0, 12.0, 1.0, displaydata->sierpinski_depth,
                                   cb_chgval_gldisplay_spinbutton, GINT_TO_POINTER (DATA_SIERP_DEPTH));
        gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

        label = gtk_label_new ("sierpinski color");
        gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
     
        adj = create_spin_button ("red", 0.0, 1.0, 0.01, displaydata->sierpinski_color [0],
                                   cb_chgval_gldisplay_spinbutton, GINT_TO_POINTER (DATA_SIERP_COLOR_R));
        gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
        
        adj = create_spin_button ("green", 0.0, 1.0, 0.01, displaydata->sierpinski_color [1],
                                   cb_chgval_gldisplay_spinbutton, GINT_TO_POINTER (DATA_SIERP_COLOR_G));
        gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

        adj = create_spin_button ("blue", 0.0, 1.0, 0.01, displaydata->sierpinski_color [2],
                                   cb_chgval_gldisplay_spinbutton, GINT_TO_POINTER (DATA_SIERP_COLOR_B));
        gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

        adj = create_spin_button ("alpha", 0.0, 1.0, 0.01, displaydata->sierpinski_color [3],
                                   cb_chgval_gldisplay_spinbutton, GINT_TO_POINTER (DATA_SIERP_COLOR_A));
        gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

        adj = create_spin_button ("sierpinski_color_fade", 0.0, 1.0, 0.01, displaydata->sierpinski_color_fade,
                                   cb_chgval_gldisplay_spinbutton, GINT_TO_POINTER (DATA_SIERP_COLOR_FADE));
        gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
  

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
    gtk_widget_set_size_request (vbox, 300, -1);

    // a label - this may be another widget !

    label = gtk_label_new ("vertice A - X, Y, Z");
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

    hbox2 = gtk_hbox_new (FALSE, 10);
    gtk_box_pack_start (GTK_BOX (vbox), hbox2, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_XMIN, SIERP_XMAX, 0.1, displaydata->sierpinski_vertice_A [0],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_AX));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_YMIN, SIERP_YMAX, 0.1, displaydata->sierpinski_vertice_A [1],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_AY));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_ZMIN, SIERP_ZMAX, 0.1, displaydata->sierpinski_vertice_A [2],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_AZ));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

    label = gtk_label_new ("vertice B - X, Y, Z");
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

    hbox2 = gtk_hbox_new (FALSE, 10);
    gtk_box_pack_start (GTK_BOX (vbox), hbox2, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_XMIN, SIERP_XMAX, 0.1, displaydata->sierpinski_vertice_B [0],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_BX));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_YMIN, SIERP_YMAX, 0.1, displaydata->sierpinski_vertice_B [1],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_BY));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_ZMIN, SIERP_ZMAX, 0.1, displaydata->sierpinski_vertice_B [2],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_BZ));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

    label = gtk_label_new ("vertice C - X, Y, Z");
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
 
    hbox2 = gtk_hbox_new (FALSE, 10);
    gtk_box_pack_start (GTK_BOX (vbox), hbox2, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_XMIN, SIERP_XMAX, 0.1, displaydata->sierpinski_vertice_C [0],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_CX));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_YMIN, SIERP_YMAX, 0.1, displaydata->sierpinski_vertice_C [1],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_CY));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_ZMIN, SIERP_ZMAX, 0.1, displaydata->sierpinski_vertice_C [2],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_CZ));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

    label = gtk_label_new ("vertice D - X, Y, Z");
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

    hbox2 = gtk_hbox_new (FALSE, 10);
    gtk_box_pack_start (GTK_BOX (vbox), hbox2, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_XMIN, SIERP_XMAX, 0.1, displaydata->sierpinski_vertice_D [0],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_DX));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

        adj = create_scale_adjustment_nolabel (SIERP_YMIN, SIERP_YMAX, 0.1, displaydata->sierpinski_vertice_D [1],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_DY));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);
     
        adj = create_scale_adjustment_nolabel (SIERP_ZMIN, SIERP_ZMAX, 0.1, displaydata->sierpinski_vertice_D [2],
                                       cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (DATA_SIERP_VERTICE_DZ));
        gtk_box_pack_start (GTK_BOX (hbox2), adj, TRUE, TRUE, 0);

    
  
    frame = gtk_frame_new ("gl");
    hbox = gtk_hbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (settings_widget), frame);
    gtk_container_add (GTK_CONTAINER (frame), hbox);
 
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
 
    adj = create_scale_adjustment ("scene->gltranslate_X", GLTRANSLATE_MIN, GLTRANSLATE_MAX, 0.1, scene->gltranslate [0],
                                    TRUE, cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (SCENE_GLTRANSLATE_X));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);
    
    adj = create_scale_adjustment ("scene->gltranslate_Y", GLTRANSLATE_MIN, GLTRANSLATE_MAX, 0.1, scene->gltranslate [1],
                                    TRUE, cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (SCENE_GLTRANSLATE_Y));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

    adj = create_scale_adjustment ("scene->gltranslate_Z", GLTRANSLATE_MIN, GLTRANSLATE_MAX, 0.1, scene->gltranslate [2],
                                    TRUE, cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (SCENE_GLTRANSLATE_Z));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

    adj = create_scale_adjustment ("scene->glrotate_angle", ANGLE_MIN, ANGLE_MAX, 1, scene->glrotate [0],
                                    TRUE, cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (SCENE_GLROTATE_ANGLE));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

    adj = create_scale_adjustment ("scene->glrotate_X", ANGLE_MIN, ANGLE_MAX, 1, scene->glrotate [1],
                                    TRUE, cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (SCENE_GLROTATE_X));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

    adj = create_scale_adjustment ("scene->glrotate_Y", ANGLE_MIN, ANGLE_MAX, 1, scene->glrotate [2],
                                    TRUE, cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (SCENE_GLROTATE_Y));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);

    adj = create_scale_adjustment ("scene->glrotate_Z", ANGLE_MIN, ANGLE_MAX, 1, scene->glrotate [3],
                                    TRUE, cb_chgval_gldisplay_adjustment, GINT_TO_POINTER (SCENE_GLROTATE_Z));
    gtk_box_pack_start (GTK_BOX (vbox), adj, TRUE, FALSE, 0);


 

  
    UI->main_window_settings = settings_widget;
 
    return settings_widget;
}

