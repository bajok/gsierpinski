/*
 *      macros_debug.h
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


#ifndef __macros_debug_h_
#define __macros_debug_h_

 

/*
#define DEBUG_FILE_READ "FILE"
*/
 
    

#define DEBUG_APPEND 3
#define DEBUG_APPEND_START 0


/*
    debug with extended output shold have in mind debug append and debug start index
    it should decide whether to append more output or not
*/



  
#define DEBUG_DATA_READ                 "DATA"
#define DEBUG_GL                        "GL  "
#define DEBUG_GTK                       "GTK "
#define DEBUG_STATISTICS                "STAT"
#define DEBUG_MEM_ALLOC                 "MEM "
#define DEBUG_THREADS                   "THREAD"
#define DEBUG_WITH_EXTENDED_OUTPUT      // has not string -- it extends normal debug output
  

 
#define LOG_GL_CONFIG                   "GL_CONFIG"

 

// this may be a string, this may be a function...
#define DEBUG_START                     " dbg   "
#define LOG_FLOW_START                "\n flow  "
#define LOG_INFO_START                  " .i.   "
#define LOG_WARNING_START               " [wrn] \n [wrn] "
#define LOG_ERROR_START                 " (err) \n (err) "

#define DEBUG_END                       "\n", NULL
#define LOG_END                         "\n", NULL
#define LOG_WARNING_END                 "\n [wrn] \n", NULL
#define LOG_ERROR_END                   "\n (err) \n", NULL


#define DEBUG_ACTION(string)            (g_print ("%s", string));
#define LOG_ACTION(string)              (g_print ("%s", string));


//~ --------------------------------------------------------------------------------------------------------------------
//~  standard logging
//~ --------------------------------------------------------------------------------------------------------------------
 
//
// warning / error

#define LOG_WARNING(string) \
    { \
        gchar *warning_message   = g_strconcat (LOG_WARNING_START, \
                                                string, \
                                                LOG_WARNING_END); \
        LOG_ACTION (warning_message) \
        g_free (warning_message); \
    }

#define LOG_ERROR(string) \
    { \
        gchar *error_message     = g_strconcat (LOG_ERROR_START, \
                                                string, \
                                                LOG_ERROR_END); \
        LOG_ACTION (error_message) \
        g_free (error_message); \
    }

//
// other messages

#define LOG_INFO(string) \
    { \
        gchar *info_message      = g_strconcat (LOG_INFO_START, \
                                                string, \
                                                LOG_END); \
        LOG_ACTION (info_message) \
        g_free (info_message); \
    }

#define LOG_INFO_VALUE(string,value) \
    { \
        gchar *valstr            = g_strdup_printf (" = %d", (gint) value); \
        gchar *info_message      = g_strconcat (LOG_INFO_START, \
                                                string, \
                                                valstr, \
                                                LOG_END); \
        LOG_ACTION (info_message) \
        g_free (info_message); g_free (valstr); \
    }

#define LOG_INFO_STRING(string,value) \
    { \
        gchar *valstr            = g_strdup_printf (" %s ", (gchar *) value); \
        gchar *info_message      = g_strconcat (LOG_INFO_START, \
                                                string, \
                                                valstr, \
                                                LOG_END); \
        LOG_ACTION (info_message) \
        g_free (info_message); g_free (valstr); \
    }

 
 
//~ --------------------------------------------------------------------------------------------------------------------
//~  debug logging
//~ --------------------------------------------------------------------------------------------------------------------

//
// warning / error

#define DEBUG_LOG_WARNING(module,caster,string) \
    { \
        gchar *warning_message   = g_strconcat (LOG_WARNING_START, \
                                                module, \
                                                "  ", \
                                                caster, \
                                                " (..) ", \
                                                string, \
                                                LOG_WARNING_END); \
        DEBUG_ACTION (warning_message) \
        g_free (warning_message); \
    }

#define DEBUG_LOG_ERROR(module,caster,string) \
    { \
        gchar *error_message     = g_strconcat (LOG_ERROR_START, \
                                                module, \
                                                "  ", \
                                                caster, \
                                                " (..) ", \
                                                string, \
                                                LOG_ERROR_END); \
        DEBUG_ACTION (error_message) \
        g_free (error_message); \
    } 

//
// other messages

#define DEBUG_LOG_FLOW(module,caster,string) \
    { \
        gchar *flow_message      = g_strconcat (LOG_FLOW_START, \
                                                module, \
                                                "  ", \
                                                caster, \
                                                " (..) ", \
                                                string, \
                                                LOG_END); \
        DEBUG_ACTION (flow_message) \
        g_free (flow_message); \
    }
 
 
// value macros shall be called ALWAYS after flow or warnings
// so they do not log their caster - instead they log optional string

#define DEBUG_LOG_INTEGER(module,opt_string,variable,value) \
    { \
        gchar *valstr            = g_strdup_printf (" = %d ", (gint) value); \
        gchar *log_message       = g_strconcat (DEBUG_START, \
                                                module, \
                                                "  ", \
                                                opt_string, \
                                                "      ~ ", \
                                                variable, \
                                                valstr, \
                                                DEBUG_END); \
        DEBUG_ACTION (log_message) \
        g_free (log_message); g_free (valstr); \
    }
 
#define DEBUG_LOG_FLOAT(module,opt_string,variable,value) \
    { \
        gchar *valstr            = g_strdup_printf (" = %f ", (gfloat) value); \
        gchar *log_message       = g_strconcat (DEBUG_START, \
                                                module, \
                                                "  ", \
                                                opt_string, \
                                                "      ~ ", \
                                                variable, \
                                                valstr, \
                                                DEBUG_END); \
        DEBUG_ACTION (log_message) \
        g_free (log_message); g_free (valstr); \
    }

#define DEBUG_LOG_FLOAT_ARRAY(module,opt_string,variable,array,array_length) \
    { \
        gchar *elementstr [array_length + 1]; \
        for (guint iter = 0; iter < (guint) array_length; iter++) { \
            elementstr [iter]    = g_strdup_printf ("%f", (gfloat) array [iter]); \
        } \
        elementstr [array_length] = NULL; \
        gchar *valstr = g_strjoinv (", ", elementstr); \
        gchar *log_message       = g_strconcat (DEBUG_START, \
                                                module, \
                                                "  ", \
                                                opt_string, \
                                                "      ~ ", \
                                                variable, \
                                                valstr, \
                                                DEBUG_END); \
        DEBUG_ACTION (log_message) \
        g_free (log_message); g_free (valstr); \
        for (guint iter = 0; iter < (guint) array_length; iter++) g_free (elementstr [iter]); \
    }
  
#define DEBUG_LOG_POINTER(module,opt_string,variable,value) \
    { \
        gchar *valstr            = g_strdup_printf (" = %p ", (gpointer) value); \
        gchar *log_message       = g_strconcat (DEBUG_START, \
                                                module, \
                                                "  ", \
                                                opt_string, \
                                                "      ~ ", \
                                                variable, \
                                                valstr, \
                                                DEBUG_END); \
        DEBUG_ACTION (log_message) \
        g_free (log_message); g_free (valstr);\
    }

#define DEBUG_LOG_STRING(module,opt_string,variable,value) \
    { \
        gchar *valstr            = g_strdup_printf (" = %s ", (gchar *) value); \
        gchar *log_message       = g_strconcat (DEBUG_START, \
                                                module, \
                                                "  ", \
                                                opt_string, \
                                                "      ~ ", \
                                                variable, \
                                                valstr, \
                                                DEBUG_END); \
        DEBUG_ACTION (log_message) \
        g_free (log_message); g_free (valstr); \
    }
 
#define DEBUG_LOG_STRING_ARRAY(module,opt_string,variable,array,array_length) \
    { \
        gchar *elementstr [array_length + 1]; \
        for (guint iter = 0; iter < (guint) array_length; iter++) { \
            elementstr [iter]    = g_strdup_printf ("%s", (gchar *) array [iter]); \
        } \
        elementstr [array_length] = NULL; \
        gchar *valstr = g_strjoinv ("|", elementstr); \
        gchar *log_message       = g_strconcat (DEBUG_START, \
                                                module, \
                                                "  ", \
                                                opt_string, \
                                                "      ~ ", \
                                                variable, \
                                                "|", \
                                                valstr, \
                                                "|", \
                                                DEBUG_END); \
        DEBUG_ACTION (log_message) \
        g_free (log_message); g_free (valstr); \
        for (guint iter = 0; iter < (guint) array_length; iter++) g_free (elementstr [iter]); \
    }
    





#define FORCED_QUIT  g_print ("\n\n d FORCED_QUIT triggered.\n\n"); cp_app_close (void); exit (-1);



#endif // __macros_debug_h_
 
 
