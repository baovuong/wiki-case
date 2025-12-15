#include <gio/gio.h>
#include <glib-object.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "gresource.h"

typedef struct _SearchPayload
{
    GtkEntry* entry;
    GtkListBox* results;

} SearchPayload;

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print("Hello, World\n");
}

static void search(GtkWidget *widget, gpointer data)
{
    g_print("Searching\n");

    // get search string
    SearchPayload* payload = (SearchPayload*)data;
    GtkEntryBuffer* buffer = gtk_entry_get_buffer(payload->entry);

    if (gtk_entry_buffer_get_length(buffer) < 1) {
        return;
    }

    // do a search

    // populate the search into results
    GtkListBox *listBox = payload->results;

    for (int i=0; i<5; i++) 
    {
        GString* search_result_entry = g_string_new(gtk_entry_buffer_get_text(buffer));
        g_string_append(search_result_entry, g_strdup_printf(" %d", i));
        gtk_list_box_prepend(listBox, gtk_label_new(search_result_entry->str));
        g_string_free(search_result_entry, TRUE);
    }
}

static void back(GtkWidget *widget, gpointer data)
{
    g_print("Going Back\n");
}

static void forward(GtkWidget *widget, gpointer data)
{
    g_print("Going Forward\n");
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    GtkTextView *textView;
    GtkTextBuffer *buffer;
    GtkListBox *searchResultsListBox;
    GtkEntry *searchEntry;

    GResource *resource;
    GBytes *builder_data;
    GError *error = NULL;

    gtk_init(&argc, &argv);

    resource = wiki_case_get_resource();

    builder = gtk_builder_new();

    // builder data
    builder_data = g_resource_lookup_data(resource, "/org/gtk/Example/res/builder.ui", G_RESOURCE_LOOKUP_FLAGS_NONE, &error);

    if (gtk_builder_add_from_string(builder, 
        g_bytes_get_data(builder_data, NULL), 
        g_bytes_get_size(builder_data), 
        &error) == 0)
    {
        g_printerr("Error loading data: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    searchResultsListBox = (GtkListBox*)gtk_builder_get_object(builder, "search-results-list-box");
    searchEntry = (GtkEntry*)gtk_builder_get_object(builder, "search-entry");

    // window 
    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // buttons 
    button = gtk_builder_get_object(builder, "search-button");
    SearchPayload searchPayload;
    searchPayload.entry = searchEntry;
    searchPayload.results = searchResultsListBox;

    g_signal_connect(button, "clicked", G_CALLBACK(search), &searchPayload);

    button = gtk_builder_get_object(builder, "back-button");
    g_signal_connect(button, "clicked", G_CALLBACK(back), NULL);

    button = gtk_builder_get_object(builder, "forward-button");
    g_signal_connect(button, "clicked", G_CALLBACK(forward), NULL);

    textView = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "content-text-view"));
    buffer = gtk_text_view_get_buffer(textView);

    gtk_text_buffer_set_text(buffer, "LMAO", 4);
    gtk_main();

    return 0;
}