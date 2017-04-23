/*
 *      gthread_functions.c
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


#include <glib.h>
#include "data_structures_init.h"
/*
#include "configuration.h"
*/


/*
#define CONFIG_FILE config->config_filename
#define DATA_DIRECTORY config->data_directory
*/


 
//~ ----------------------------------------------------------------------------
//~ threads definitions and vars
//~ ----------------------------------------------------------------------------

gulong dbg_sleep = 60000 * 1000; // 60s

gpointer *gthread_dbg (gpointer data) {

    #ifdef DEBUG_THREADS
        LOG_INFO_VALUE ("debug thread attached. ", GPOINTER_TO_INT (data))
    #endif

    while (TRUE) {

        // in debug thread there shall be no #ifdef for logging - as debug thread may be attached or not
        DEBUG_LOG_FLOW (DEBUG_THREADS, "gthread_dbg", "dumping variable values:")
        DEBUG_LOG_INTEGER (DEBUG_THREADS, " ", "config->graph_width",     config->graph_width)
        DEBUG_LOG_INTEGER (DEBUG_THREADS, " ", "config->graph_height",    config->graph_height)
        DEBUG_LOG_INTEGER (DEBUG_THREADS, " ", "current->get_listing",    current->get_listing)
        DEBUG_LOG_INTEGER (DEBUG_THREADS, " ", "current->get_label",      current->get_label)

/*
    for (int i = 0; i < DEBUG_APPEND; i++) {

        g_prnt ("%d: %s ", i, newconnect->labels [i]);
    }
*/

/*
    for (gint i = 0; i < DEBUG_APPEND; i++) {
        for (gint j = 0; j < 21; j++) {
            g_prnt (" %s %d %f %f %f %f %f \n",    newconnect->labels [i],
                                             newconnect->daily[j]->listed[i]->date,
                                             newconnect->daily[j]->listed[i]->v_open,
                                             newconnect->daily[j]->listed[i]->v_high,
                                             newconnect->daily[j]->listed[i]->v_low,
                                             newconnect->daily[j]->listed[i]->v_close,
                                             newconnect->daily[j]->listed[i]->volume);
        }
    }
*/

 
/*
        g_prnt (" %d %f %f %f %f %f \n",    newconnect_daily [i]->date,
                                             newconnect_daily [i]->v_open,     newconnect_daily [i]->v_high,
                                             newconnect_daily [i]->v_low,      newconnect_daily [i]->v_close,
                                             newconnect_daily [i]->volume);
*/

 

/*
void                gtk_widget_get_pointer              (GtkWidget *widget,
                                                         gint *x,
                                                         gint *y);
*/


/*
newconnect_daily [i]->label->str,
*/
    g_usleep (dbg_sleep);
    }
}


//~ --------------------------------------------------------------------------------------------------------------------
//~ threads
//~ --------------------------------------------------------------------------------------------------------------------

//~ static void producer_sighandler(int signum)
//~ {
    //~ /* make sure mutex is unlocked. ignore errors. */
    //~ pthread_mutex_unlock (&results_lock);

    //~ pthread_exit((void*)1);
//~ }

//~ static void produce_result (char *filename, char *crc, gboolean checksum_ok)
//~ {
    //~ struct sfvresult *r;

    //~ /* create a sfvresult slot to insert in results */
    //~ r = malloc (sizeof (struct sfvresult));
    //~ if (!r) {
        //~ fprintf(stderr, "ERROR: malloc failed.\n");
        //~ exit(9997);
    //~ }

    //~ /* crc checksum parameter hits the bitbucket here. No use for it. */
    //~ r->checksum_ok = checksum_ok;
    //~ r->filename = strdup(filename);

    //~ /* take lock */
    //~ if (pthread_mutex_lock (&results_lock) != 0) {
        //~ fprintf(stderr, "ERROR: could not aquire results lock!\n");
        //~ exit(9998);
    //~ }

    //~ /* append result slot */
    //~ g_queue_push_tail (results, r);

    //~ /* release lock */
    //~ if (pthread_mutex_unlock (&results_lock) != 0) {
        //~ fprintf(stderr, "ERROR: could not release results lock!\n");
        //~ exit(9999);
    //~ }

    //~ /* signal consumer */
    //~ kill(getpid(), SIGUSR1);
//~ }




