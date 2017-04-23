#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glconfig.h"
#include "macros_debug.h"


static void print_gl_config_attrib (GdkGLConfig *glconfig, const gchar *attrib_str, int attrib, gboolean is_boolean);
static void examine_gl_config_attrib (GdkGLConfig *glconfig);


GdkGLConfig *glconfig;


void configure_gtkglext () {

    /* gl configuration */
    gint major, minor;

    /* Query OpenGL extension version. */
    gdk_gl_query_version (&major, &minor);
    gchar *major_string         = g_strdup_printf ("%d", (gint) major); \
    gchar *minor_string         = g_strdup_printf ("%d", (gint) minor); \
    gchar *version              = g_strconcat (major_string, ".", minor_string, NULL);

    LOG_INFO_STRING (" ", " ")
    LOG_INFO_STRING ("OpenGL extension version: ", version)
    g_free (version);
    g_free (major_string);
    g_free (minor_string);

    /* Configure OpenGL-capable visual. */
    /* Try double-buffered visual */
    glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH | GDK_GL_MODE_DOUBLE);

    if (glconfig == NULL) {

        LOG_ERROR ("Cannot find the double-buffered visual.")
        LOG_ERROR ("Trying single-buffered visual.")

        /* Try single-buffered visual */
        glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH);
        if (glconfig == NULL) {

            LOG_ERROR ("No appropriate OpenGL-capable visual found.")

            exit (1); // there should be a defined exit code
        }
    }
    #ifdef LOG_GL_CONFIG
        examine_gl_config_attrib (glconfig);
    #endif
}
 

// OpenGL parameters are logged: #ifdef LOG_GL_CONFIG

static void print_gl_config_attrib (GdkGLConfig *glconfig, const gchar *attrib_str, int attrib, gboolean is_boolean) {

    gint value;

    if (gdk_gl_config_get_attrib (glconfig, attrib, &value)) {

        if (is_boolean)
            LOG_INFO_STRING  (attrib_str, value == TRUE ? "= TRUE" : "= FALSE")
        else
            LOG_INFO_VALUE  (attrib_str, value)
    }
    else {
        LOG_ERROR ("Cannot get attribute value:")
        LOG_INFO  (attrib_str)
    }
}

static void examine_gl_config_attrib (GdkGLConfig *glconfig) {
 
    LOG_INFO ("OpenGL visual configurations:")

    LOG_INFO_STRING ("gdk_gl_config_is_rgba (glconfig) =", \
                      gdk_gl_config_is_rgba (glconfig) ? "TRUE" : "FALSE")

    LOG_INFO_STRING ("gdk_gl_config_is_double_buffered (glconfig) =", \
                      gdk_gl_config_is_double_buffered (glconfig) ? "TRUE" : "FALSE")

    LOG_INFO_STRING ("gdk_gl_config_is_stereo (glconfig) =", \
                      gdk_gl_config_is_stereo (glconfig) ? "TRUE" : "FALSE")

    LOG_INFO_STRING ("gdk_gl_config_has_alpha (glconfig) =", \
                      gdk_gl_config_has_alpha (glconfig) ? "TRUE" : "FALSE")

    LOG_INFO_STRING ("gdk_gl_config_has_depth_buffer (glconfig) =", \
                      gdk_gl_config_has_depth_buffer (glconfig) ? "TRUE" : "FALSE")

    LOG_INFO_STRING ("gdk_gl_config_has_stencil_buffer (glconfig) =", \
                      gdk_gl_config_has_stencil_buffer (glconfig) ? "TRUE" : "FALSE")

    LOG_INFO_STRING ("gdk_gl_config_has_accum_buffer (glconfig) =", \
                      gdk_gl_config_has_accum_buffer (glconfig) ? "TRUE" : "FALSE")

    LOG_INFO ("OpenGL attributes:")

    print_gl_config_attrib (glconfig, "GDK_GL_USE_GL",           GDK_GL_USE_GL,           TRUE);
    print_gl_config_attrib (glconfig, "GDK_GL_BUFFER_SIZE",      GDK_GL_BUFFER_SIZE,      FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_LEVEL",            GDK_GL_LEVEL,            FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_RGBA",             GDK_GL_RGBA,             TRUE);
    print_gl_config_attrib (glconfig, "GDK_GL_DOUBLEBUFFER",     GDK_GL_DOUBLEBUFFER,     TRUE);
    print_gl_config_attrib (glconfig, "GDK_GL_STEREO",           GDK_GL_STEREO,           TRUE);
    print_gl_config_attrib (glconfig, "GDK_GL_AUX_BUFFERS",      GDK_GL_AUX_BUFFERS,      FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_RED_SIZE",         GDK_GL_RED_SIZE,         FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_GREEN_SIZE",       GDK_GL_GREEN_SIZE,       FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_BLUE_SIZE",        GDK_GL_BLUE_SIZE,        FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_ALPHA_SIZE",       GDK_GL_ALPHA_SIZE,       FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_DEPTH_SIZE",       GDK_GL_DEPTH_SIZE,       FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_STENCIL_SIZE",     GDK_GL_STENCIL_SIZE,     FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_RED_SIZE",   GDK_GL_ACCUM_RED_SIZE,   FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_GREEN_SIZE", GDK_GL_ACCUM_GREEN_SIZE, FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_BLUE_SIZE",  GDK_GL_ACCUM_BLUE_SIZE,  FALSE);
    print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_ALPHA_SIZE", GDK_GL_ACCUM_ALPHA_SIZE, FALSE);

}
