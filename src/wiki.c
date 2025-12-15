#include <glib-object.h>
#include <glib.h>
#include <json-glib/json-glib.h>

#include "wiki.h"

// helper function declarations

WikiArticle* wiki_article_new()
{
    WikiArticle* result = g_malloc(sizeof(WikiArticle));
    
    return result;
}

WikiArticle* wiki_article_new_from_json(const char* json_string)
{
    WikiArticle* result = wiki_article_new();
    JsonParser *parser = json_parser_new();
    GError* err = NULL;

    if (!json_parser_load_from_data (parser, json_string, -1, &err)) {
        g_print("error in parsing json data %s", err->message);
        g_error_free (err);
        g_object_unref (parser);
        return NULL;
    }

    JsonReader *reader = json_reader_new(json_parser_get_root(parser));
    char** members = json_reader_list_members(reader);
    int i = 0;
    while (members[i] != 0)
    {
        if (g_str_equal(members[i], "title")) {
            result->title = g_string_new(NULL);
            g_string_append(result->title, members[i]);
        }
    }

    g_object_unref(parser);

    return result;
}

void wiki_article_free(WikiArticle *wiki_article)
{
    // free up members
    g_string_free(wiki_article->title, TRUE);
    g_free(wiki_article);
}
