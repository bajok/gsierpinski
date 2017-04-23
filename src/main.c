/*
 *      main.c
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


/*
 * gl configuration piece of code was grabbed from Simple.c
 * written by Naofumi Yasufuku  <naofumi@users.sourceforge.net>
 *
 * sierpinski algorithm: Lode's Computer Graphics Tutorial
 *
 */


//~ =======================
//~       gsierpinski
//~ =======================

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>

#include "data_structures_init.h"
#include "gthread_functions.h"
#include "gtk_frontend.h"


#ifndef PROGRAM_NAME
  #define PROGRAM_NAME "gsierpinski"
#endif


/*
#ifdef G_OS_WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif
*/
 


/*
    #define TEST_MACROS "TEST_MACROS"
*/




gint main (gint argc, gchar *argv[]) {

    LOG_INFO_STRING ("~ starting ~", PROGRAM_NAME)

    #ifdef TEST_MACROS
        //~ macros_debug.h
        // #define LOG_INFO(string)
        // #define LOG_INFO_VALUE(string,value)
        // #define LOG_INFO_STRING(string,value)
        // #define LOG_WARNING(string)
        // #define LOG_ERROR(string)
        // #define DEBUG_LOG_FLOW(module,caster,string)
        // #define DEBUG_LOG_WARNING(module,caster,string)
        // #define DEBUG_LOG_ERROR(module,caster,string)
        // #define DEBUG_LOG_INTEGER(module,caster,variable,value)
        // #define DEBUG_LOG_FLOAT(module,caster,variable,value)
        // #define DEBUG_LOG_POINTER(module,caster,variable,value)
        // #define DEBUG_LOG_STRING(module,caster,variable,value)

        gint    test_int_value      = 1;
        gfloat  test_float_value    = 0.11;
        gchar  *sample_string       = g_strdup_printf ("sample string");
        gpointer *sample_pointer    = NULL;
        gfloat  test_float_array [4];
        for (guint iter = 0; iter < 4; iter++)
            test_float_array [iter] = 0.001 * (gfloat) iter;
        gchar  *test_string_array [2];
        for (guint iter = 0; iter < 2; iter++)
            test_string_array [iter] = g_strdup_printf ("string %d", iter);

        LOG_INFO        (" -- -- -- -- -- -- -- -- -- -- -- -- -- .. -- -- -- -- -- -- -- -- -- -- -- -- -- ")
        LOG_INFO        ("testing text output alignment")
        LOG_INFO        (" -- -- -- -- -- -- -- -- -- -- -- -- -- ")
        LOG_INFO        ("info string")
        LOG_WARNING     ("warning message")
        LOG_ERROR       ("error message")
        LOG_INFO_VALUE  ("variable name string (default: integer)", test_int_value)
        LOG_INFO_VALUE  ("variable name string (float provided)", test_float_value)
        LOG_INFO_STRING ("string value", sample_string)
        // debug array logging shall be added
        LOG_INFO        ("~ debug macros below")
        DEBUG_LOG_WARNING   (TEST_MACROS, "main", "warning message")
        DEBUG_LOG_ERROR     (TEST_MACROS, "main", "error message")
        DEBUG_LOG_FLOW      (TEST_MACROS, "main", "functiona_name___main")
        DEBUG_LOG_STRING    (TEST_MACROS, " ", "sample_string", sample_string)
        DEBUG_LOG_POINTER   (TEST_MACROS, " ", "sample_pointer", sample_pointer)
        DEBUG_LOG_INTEGER   (TEST_MACROS, " ", "test_int_value", test_int_value)
        DEBUG_LOG_FLOAT     (TEST_MACROS, " ", "test_float_value", test_float_value)
        DEBUG_LOG_INTEGER   (TEST_MACROS, " ", "test_float_value", test_float_value)
        DEBUG_LOG_FLOAT     (TEST_MACROS, " ", "test_int_value", test_int_value)
        DEBUG_LOG_FLOAT_ARRAY (TEST_MACROS," ","test_float_array [4] = ",test_float_array,4)
        DEBUG_LOG_STRING_ARRAY (TEST_MACROS," ","test_string_array [2] = ",test_string_array,2)

        DEBUG_LOG_STRING    (TEST_MACROS, "opt_string", "", NULL)

        LOG_INFO        (" -- -- -- -- -- -- -- -- -- -- -- -- -- ")
        LOG_INFO        ("end of test")
        LOG_INFO        (" -- -- -- -- -- -- -- -- -- -- -- -- -- .. -- -- -- -- -- -- -- -- -- -- -- -- -- ")
        LOG_INFO        ("")
        LOG_INFO        ("")
        LOG_INFO        ("")
        LOG_INFO        ("")
        g_free (sample_string);

    #endif

//~ --------------------------------------------------------------------------------------------------------------------
//~ * data structures initialization
//~ --------------------------------------------------------------------------------------------------------------------

    if (initialize_gl_structures ()) {
        #ifdef DEBUG_MEM_ALLOC
            DEBUG_LOG_FLOW      (DEBUG_MEM_ALLOC, "main", "initialize_gl_structures ()")
            DEBUG_LOG_POINTER   (DEBUG_MEM_ALLOC, "main", "scene", scene)
            DEBUG_LOG_POINTER   (DEBUG_MEM_ALLOC, "main", "displaydata", displaydata)
        #endif
    } else return 1;

    if (initialize_current_data ()) {
        #ifdef DEBUG_MEM_ALLOC
            DEBUG_LOG_FLOW      (DEBUG_MEM_ALLOC, "main", "initialize_current_data ()")
            DEBUG_LOG_POINTER   (DEBUG_MEM_ALLOC, "main", "current", current)
        #endif
    } else return 2;


//~ --------------------------------------------------------------------------------------------------------------------
//~ * gtk initialization
//~ --------------------------------------------------------------------------------------------------------------------
 
    gtk_set_locale ();
//     gtk_init (&argc, &argv);
    gtk_init (NULL, NULL);
    gtk_gl_init (NULL, NULL);
    configure_gtkglext ();

 
 
//~ --------------------------------------------------------------------------------------------------------------------
//~ * initial data values and pointers
//~ --------------------------------------------------------------------------------------------------------------------

   

//~ --------------------------------------------------------------------------------------------------------------------
//~ * appending frontend
//~ --------------------------------------------------------------------------------------------------------------------

    LOG_INFO ("appending frontend")

    // there shall be a constructor for GUI struct

    UI = g_malloc0 ((sizeof (frontend_widgets)));

    // init variables
    UI-> main_window_title           = (gchar *) g_strdup (PROGRAM_NAME); // window title can be easily changed
    UI-> window_size_x               = 800;
    UI-> window_size_y               = 600;

    // append main window
    UI-> main_window                 = (GtkWidget *) append_main_window (UI->main_window_title);
    gtk_widget_show_all (UI->main_window);



    /* enabling tooltips */
//     gtk_tooltips_disable (GTK_TOOLTIPS (tooltips));
//     gtk_tooltips_enable (GTK_TOOLTIPS (tooltips));

//~ --------------------------------------------------------------------------------------------------------------------
//~ * threads initialization
//~ --------------------------------------------------------------------------------------------------------------------

    LOG_INFO ("initializing threads... - every thread should say \"hello\"")
 

    g_thread_init (NULL);

    gthreads = g_malloc0 (sizeof (gthread_refs));
    if (gthreads == NULL) {
        LOG_ERROR ("gthread_refs *gthreads: memory could not be allocated")
        return 3;
    } else {
 
        gthreads->debug_thread_runs = TRUE;
        gthreads->debug_thread      = g_thread_create ((GThread *) gthread_dbg, GINT_TO_POINTER ((1)), TRUE, NULL);
    }
 
    LOG_INFO ("threads initialized.")

 
//~ --------------------------------------------------------------------------------------------------------------------
//~ * gkt_main loop
//~ --------------------------------------------------------------------------------------------------------------------

    gtk_main ();




//~ --------------------------------------------------------------------------------------------------------------------
//~ * threads finalization
//~ --------------------------------------------------------------------------------------------------------------------

    gthreads->debug_thread_runs             = FALSE;

    g_thread_join (gthreads->debug_thread);
  

//~ --------------------------------------------------------------------------------------------------------------------
//~ * finalize (gtk_main_qit)
//~ --------------------------------------------------------------------------------------------------------------------


    finalize_struct (scene);
    finalize_struct (displaydata->sierpinski_color);
    finalize_struct (displaydata);

 

/*
    |
    |
    | this has to be finalized correctly !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    |
    |
*/

    LOG_WARNING ("structures have to be finalized correctly!")

    return 0;
}

