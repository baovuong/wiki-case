#ifndef __WIKI_wiki_case_H__
#define __WIKI_wiki_case_H__

typedef struct lang_link {
    char* lang,
    char* url,
    char* autonym,
    char* asterisk
} lang_link_t;

typedef struct category {
    char* sort_key,
    bool is_hidden,
    char* asterisk
} category_t;

typedef struct link {
    int ns,
    bool exists,
    char* asterisk
} link_t;

typedef struct template {
    int ns,
    bool exists,
    char* asterisk
} template_t;

typedef struct section {
    int toc_level,
    int level,
    char* line,
    int number,
    int index,
    char* from_title,
    int byte_offset,
    char* anchor,
    char* linkAnchor
} section_t;

typedef struct property {
    char* name,
    char* asterisk
} property_t;

typedef struct wiki_article {
    char* title,
    int page_id,
    int rev_id,
    char *text,
    lang_link_t *lang_links,
    category_t *categories,
    link_t *links,
    template_t *templates,
    char* *images,
    char* *external_links,
    section_t *sections,
    char* display_title,
    property_t *properties
} wiki_article_t;

wiki_article_t get_wiki_article_from_json(const char* value);

#endif