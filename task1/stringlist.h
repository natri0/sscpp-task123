#pragma once

typedef char **StringList;

StringList SL_new();
void SL_free(StringList sl);

void SL_add(StringList *sl, const char *str);
void SL_remove(StringList *sl, const char *str);

unsigned int SL_length(StringList sl);
unsigned int SL_count(StringList sl, const char *str);
int SL_first_index_of(StringList sl, const char *str);
