#include "gio/gio.h"
#include "glib-object.h"
#include "glib.h"
#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print("Hello, World\n");
}


int main(int argc, char **argv)
{
    GtkApplication *app;
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    GResource *resource;
    GBytes *builder_data;
    GError *error = NULL;

    gtk_init(&argc, &argv);

    g_print("wow\n");
    resource = wiki_case_get_resource();

    g_print("loaded\n");
    builder = gtk_builder_new();

    // builder data
    builder_data = g_resource_lookup_data(resource, "/org/gtk/Example/builder.ui", G_RESOURCE_LOOKUP_FLAGS_NONE, &error);

    g_print("loaded\n");

    if (gtk_builder_add_from_string(builder, 
        g_bytes_get_data(builder_data, NULL), 
        g_bytes_get_size(builder_data), 
        &error) != 0)
    {
        g_printerr("Error loading data: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // window 
    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // buttons 
    button = gtk_builder_get_object(builder, "button1");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    button = gtk_builder_get_object(builder, "button2");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    button = gtk_builder_get_object(builder, "quit");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}