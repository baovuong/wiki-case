#include "wiki.h"

WikiArticle* wiki_article_new()
{
    WikiArticle* result = g_malloc(sizeof(WikiArticle));
    
    return result;
}

void wiki_article_free(WikiArticle *wiki_article)
{
    g_free(wiki_article);
}
