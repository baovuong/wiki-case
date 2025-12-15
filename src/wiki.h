#ifndef __WIKI_wiki_case_H__
#define __WIKI_wiki_case_H__

#include <glib.h>

typedef struct _LangLink {
    GString* lang;
    GString* url;
    GString* autonym;
    GString* asterisk;
} LangLink;

typedef struct _Category {
    GString* sort_key;
    gboolean is_hidden;
    GString* asterisk;
} Category;

typedef struct _Link {
    gint ns;
    gboolean exists;
    GString* asterisk;
} Link;

typedef struct _Template {
    gint ns;
    gboolean exists;
    GString* asterisk;
} Template;

typedef struct _Section {
    gint toc_level;
    gint level;
    GString* line;
    gint number;
    gint index;
    GString* from_title;
    gint byte_offset;
    GString* anchor;
    GString* linkAnchor;
} Section;

typedef struct _Property {
    GString* name;
    GString* asterisk;
} Property;

typedef struct _WikiArticle {
    GString* title;
    gint page_id;
    gint rev_id;
    GString* text;
    LangLink *lang_links;
    Category *categories;
    Link *links;
    Template *templates;
    GString* *images;
    GString* *external_links;
    Section *sections;
    GString* display_title;
    Property *properties;
} WikiArticle;

// methods for wiki article
extern WikiArticle* wiki_article_new();
extern WikiArticle* wiki_article_new_from_json(const char* json_string);
extern void wiki_article_free(WikiArticle* wiki_article);

#endif