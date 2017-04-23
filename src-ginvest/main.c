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


//~ =================================
//~   M  I  L  E  S  T  O  N  E  S
//~ =================================

    //~ first: what it is supposed to do.

            //~ stock changes monitor with hopefully generic data gathering

//~ ---------------------------------

//~ milestone 1: - gtk frontend with opengl capable widgets
//~ milestone 2: - backend for configurable application functions
//~ milestone 3: - at least some kind of generic data reading and gathering
//~ milestone 4: - some nfs, gathered data exposition
//~ milestone 5: - application specific functionality (undefined strictly yet)

//~ ---------------------------------

//~ milestones completion:

//~ 1 - done
//~ 2 - done
//~ 3 - .
//~ 4 - .
//~ 5 - .


 

/*
no to:

 odczyt danych gpw/newconnect bedzie sie odbywal bezposrednio z podanej strony

 najlepsza bylaby jakas biblioteka, ktora czytalaby wierszami wartosci z tabelek htmlowych

 moznaby podac linka i !regexp! ktory bylby wzorem linijki, ktory ma ta biblioteka wydostac

 jesli znalazlaby wiecej niz np. 10 takich linijek, to wydostaje je i dorzuca do archiwum z okreslona data.

*/



/*
    linki:
    http://www.inwestycje.pl/gpw/notowania_gieldowe




 Baza danych z końca dnia (EOD) aktualizowana automatycznie z serwisu Bossa.pl

 http://bossa.pl/notowania/daneatech/amibroker/eod.html




 w sumie do aktualizacji bazy moze sluzyc skrypt w pythonie
 *
 * baza bedzie sie zapisywala na serwerze, link w ginvest.conf
 *
 * ACZKOLWIEK penetrator strony html nie jest zly....
 *


     !!!

     http://bossa.pl/pub/
 */


//~ changing window title:
    //~ char buf[1024];

    //~ /* set window title */
    //~ snprintf(buf, 1024, "%s - %s", PROGNAME, sfvfilename);
    //~ gtk_window_set_title(GTK_WINDOW(window), buf);





/*
int value = some_func(((my_data_t*)p)->a);
*/


//~ =======================
//~   G  I  N  V  E  S  T
//~ =======================

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>

#include "file_io.h"
#include "data_structures_init.h"
#include "configuration.h"

#include "gthread_functions.h"
#include "glconfig.h"

#include "gtk_frontend.h"
/*
#include "gtk_frontend_child_windows.h"
*/


#ifndef PROGRAM_NAME
  #define PROGRAM_NAME "ginvest"
#endif


/*
14.02.2009  everybody loves you
*/



/*
#define DEBUG_GL
*/

/*
mozna zrobic takie cos:

application developement tree:
main.c
 |
 |
\ /
 |
include1.h  include2.h  include3.h ...
 |              |
 |              |
\ /            \ /
 |              |
next_level
_include.h

*/


 
#define TEST_MACROS "TEST_MACROS"


gint main (gint argc, gchar *argv[]) {


/*
    structures defined in: .c
*/

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
            DEBUG_LOG_FLOW (DEBUG_MEM_ALLOC, "main", "initialize_gl_structures ()")
        #endif
    } else return 1;

    if (initialize_configuration ()) {
        #ifdef DEBUG_MEM_ALLOC
            DEBUG_LOG_FLOW (DEBUG_MEM_ALLOC, "main", "initialize_configuration ()")
        #endif
    } else return 2;

    if (initialize_current_data ()) {
        #ifdef DEBUG_MEM_ALLOC
            DEBUG_LOG_FLOW (DEBUG_MEM_ALLOC, "main", "initialize_current_data ()")
        #endif
    } else return 3;

    if (initialize_statistics_data ()) {
        #ifdef DEBUG_MEM_ALLOC
            DEBUG_LOG_FLOW (DEBUG_MEM_ALLOC, "main", "initialize_statistics_data ()")
        #endif
    } else return 4;

    if (initialize_statistics_parameters ()) {
        #ifdef DEBUG_MEM_ALLOC
            DEBUG_LOG_FLOW (DEBUG_MEM_ALLOC, "main", "initialize_statistics_parameters ()")
        #endif
    } else return 5;

    if (initialize_debug_data ()) {
        #ifdef DEBUG_MEM_ALLOC
            DEBUG_LOG_FLOW (DEBUG_MEM_ALLOC, "main", "initialize_debug_data ()")
        #endif
    } else return 100;


//~ --------------------------------------------------------------------------------------------------------------------
//~ * gtk initialization
//~ --------------------------------------------------------------------------------------------------------------------
 
/*
    #ifdef ENABLE_NLS
        bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
        bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
        textdomain (GETTEXT_PACKAGE);
    #endif
*/ 

    gtk_set_locale ();
//     gtk_init (&argc, &argv);
    gtk_init (NULL, NULL);
    gtk_gl_init (NULL, NULL);
    configure_gtkglext ();


//~ --------------------------------------------------------------------------------------------------------------------
//~ * reading configuration and data files
//~ --------------------------------------------------------------------------------------------------------------------

    #ifdef DEBUG_DATA_READ
           DEBUG_LOG_FLOW (DEBUG_DATA_READ, "main", "file i/o begin")
    #endif

    //~ gboolean _success = FALSE;
    if  (file_io_read_configuration ())
        LOG_INFO ("configuration file read successfully")
    else
        //~ FIXME --------- if no config file -- create new one
        // (from template -- values are given in data_structures_init)
        LOG_ERROR ("problem with reading configuration, using defaults...         [ TODO ]")

    if  (file_io_read_data ())
        LOG_INFO ("data read successfully")
    else {
        LOG_ERROR ("cannot read data - aborting...")
        return 20;
    }


//~ --------------------------------------------------------------------------------------------------------------------
//~ * initial data values and pointers
//~ --------------------------------------------------------------------------------------------------------------------

    // initial data pointer may vay as there may be several data types already read

    std_entire_data *source = NULL;

    if (current->t_stock_enum == NEWCONNECT) {
        source = newconnect;
        current->data_source = newconnect; 
        current->get_listing = config->get_listing;
        current->get_label   = config->get_label;
        current->t_std_daily_result = V_OPEN; // as a BASE for STATISTICS

        #ifdef DEBUG_DATA_READ
            DEBUG_LOG_FLOW      (DEBUG_DATA_READ, "main", "post read summary:")
            DEBUG_LOG_INTEGER   (DEBUG_DATA_READ, " ", "current->get_listing", current->get_listing)
            DEBUG_LOG_INTEGER   (DEBUG_DATA_READ, " ", "current->get_label",   current->get_label)
            DEBUG_LOG_INTEGER   (DEBUG_DATA_READ, " ", "current->t_std_daily_result",   current->t_std_daily_result)
            DEBUG_LOG_POINTER   (DEBUG_DATA_READ, " ", "current->data_source",   current->data_source)
        #endif
 
        // standard init
/*
        statdata is not initialized anywhere else!
*/  
        statdata->get_listing = source->num_of_listings - 1; // last listing
        statdata->get_listing_range = 3; // how far to "go back" in check for stats
        statdata->get_label = 0;          // in case of: "for every label" it does not matter
        statdata->toggle_show_zeroes = FALSE; 
  
        t_statistic_type_enum num_of_t_statistics = STAT_T_STATISTIC_LAST_INDEX;
        statdata->num_of_t_statistics = num_of_t_statistics;  // size of t_statistic_type_enum


/*
        for (guint iter = 0; iter < STANDARD_LABELS_MAX; iter++) {
            for (guint iter2 = 0; iter2 < TN_PERIOD_TYPES; iter2++) 
                statdata->tn_stats [iter][iter2] = g_malloc0 ((sizeof (gfloat)) * ((guint) num_of_t_statistics));

        }
*/
 
/*
        for (guint iter = 0; iter < STANDARD_LABELS_MAX; iter++) {
            for (guint iter2 = 0; iter2 < STAT_T_STATISTIC_LAST_INDEX; iter2++)
                statdata->tn_stats [iter][1][iter2] = iter2;
        }
*/
      
         
        statdata->t_stat_name = t_stat_name_default;
 
/* 
            if (!(destination->daily[iter]->char_date = (gchar*) 
                g_malloc0 ((sizeof (gchar)) * CSV_FIELDNAME_LEN))) return FALSE;
*/

        statparams->t1_period_len = 5;
        statparams->t2_period_len = 20;
        statparams->t3_period_len = 90;
 

        // this may be moved to initialize data pointers
/*
        statparams-> 
*/
 
  
   
/*
        current->t_std_daily_result = V_OPEN; 
*/

    }


//~ --------------------------------------------------------------------------------------------------------------------
//~ * appending frontend
//~ --------------------------------------------------------------------------------------------------------------------


    // there shall be a constructor for GUI struct

    displaydata = g_malloc0 ((sizeof (glgraph_display_data)));
 
  
    UI = g_malloc0 ((sizeof (frontend_widgets)));

    statdata->gui_columns_total         = STAT_T_STATISTIC_LAST_INDEX; // statistics columns - label is separate
    statdata->gui_columns_visible_arr   = g_malloc0 ((sizeof (gboolean)) * statdata->gui_columns_total);

    UI->adv_columns_total               = statdata->gui_columns_total;
    UI->adv_columns_visible_arr         = statdata->gui_columns_visible_arr;
    #ifdef DEBUG_GTK
        DEBUG_LOG_INTEGER (DEBUG_GTK, " ", "UI->adv_columns_total", UI->adv_columns_total)
    #endif 
      
    // data assignement
    // columns visible 
    for (guint iter = 0; iter < UI->adv_columns_total; iter++)
        UI->adv_columns_visible_arr [iter] = TRUE;
/*
    //columns invisible
    for (gint iter = STAT_T_STATISTIC_LAST_INDEX + 1; iter < TN_PERIODS_TOTAL_L; iter++)
        UI->adv_columns_visible_arr [iter] = FALSE;
*/
   
  

    UI-> main_window_title           = (gchar *) g_strdup (PROGRAM_NAME);
    UI-> main_window                 = (GtkWidget *) append_main_window (UI->main_window_title);
    gtk_widget_show_all (UI->main_window);

    UI-> child_window_settings       = append_child_window_settings   ("ginvest - settings");
    UI-> child_window_diagnostic     = append_child_window_diagnostic ("ginvest - diagnostic window",
                                                                        current->t_stock_enum, source);

    UI-> child_window_statistics     = append_child_window_statistics ("ginvest - standard statistics",
                                                                        current->t_stock_enum, source);

 
    gtk_widget_show_all (UI->child_window_settings);
    gtk_widget_show_all (UI->child_window_diagnostic);
    gtk_widget_show_all (UI->child_window_statistics);


    /* enabling tooltips */
//     gtk_tooltips_disable (GTK_TOOLTIPS (tooltips));
//     gtk_tooltips_enable (GTK_TOOLTIPS (tooltips));

//~ --------------------------------------------------------------------------------------------------------------------
//~ * threads initialization
//~ --------------------------------------------------------------------------------------------------------------------

    LOG_INFO ("initializing threads... - every thread should say \"hello\"")

    g_thread_init (NULL);
    GThread *debug_thread = g_thread_create ((GThread *) gthread_dbg, GINT_TO_POINTER ((1)), FALSE, NULL);

    LOG_INFO ("threads initialized.")

 
//~ --------------------------------------------------------------------------------------------------------------------
//~ * gkt_main loop
//~ --------------------------------------------------------------------------------------------------------------------

    gtk_main ();

//~ --------------------------------------------------------------------------------------------------------------------
//~ * threads finalization
//~ --------------------------------------------------------------------------------------------------------------------



 

//~ --------------------------------------------------------------------------------------------------------------------
//~ * finalize (gtk_main_qit)
//~ --------------------------------------------------------------------------------------------------------------------


    finalize_struct (config);
    finalize_struct (current);

    finalize_struct (properties);
    finalize_struct (scene);
    finalize_struct (plane);


/*
    ile usunac wskaznikow najlepiej sprawdzic robiac przycisk re-read data :)
*/

/*
    |
    |
    | this has to be finalized correctly !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    |
    |
*/

    LOG_WARNING ("structures have to be finalized correctly!")


    for (gint iter = 0; iter < newconnect->num_of_listings; iter++) {
        finalize_struct_array ((gpointer *) newconnect->daily[0]->listed, current->labels_max);
    }
    finalize_struct_array ((gpointer *) newconnect->daily, current->listings_max);
/*
    finalize_struct_array ((gpointer *) newconnect->labels, current->labels_max);
*/
    g_strfreev ((gpointer **) newconnect->labels);
/* 
    finalize_struct ((gpointer **) newconnect->labels);
*/
    finalize_struct (newconnect);


    return 0;
}

