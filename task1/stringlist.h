#pragma once

typedef char **StringList;
typedef int (*SortFn)(const char *a, const char *b);

StringList SL_new();
void SL_free(StringList sl);

void SL_add(StringList *sl, const char *str);
void SL_remove(StringList *sl, const char *str);

unsigned int SL_length(StringList sl);
unsigned int SL_count(StringList sl, const char *str);
int SL_first_index_of(StringList sl, const char *str);

void SL_remove_duplicates(StringList *sl);
void SL_sort_with_fn(StringList sl, SortFn fn);
void SL_sort(StringList sl);

void SL_replace_in_all(StringList sl, const char *to_replace, const char *replace_with);
