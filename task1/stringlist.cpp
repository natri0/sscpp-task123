#include "stringlist.h"

#include <stdlib.h>
#include <string.h>

StringList SL_new() {
    auto sl = static_cast<StringList>(malloc(sizeof(char *)));
    sl[0] = nullptr;
    return sl;
}

void SL_free(StringList sl) {
    if (!*sl) return;

    for (int i = 0; sl[i] != nullptr; i++)
        free(sl[i]);
    free(sl);
}

void SL_add(StringList *sl, const char *str) {
    if (!sl || !*sl) return;

    unsigned int list_len = SL_length(*sl);

    *sl = static_cast<StringList>(realloc(*sl, sizeof(char *) * (list_len + 2)));
    (*sl)[list_len] = strdup(str);
    (*sl)[list_len + 1] = nullptr;
}

void SL_remove(StringList *sl, const char *str) {
    if (!sl || !*sl) return;

    unsigned int new_len = SL_length(*sl) + 1 - SL_count(*sl, str);
    auto *new_sl = static_cast<StringList>(malloc(sizeof(char *) * new_len));

    for (unsigned int read_pos = 0, write_pos = 0; read_pos < SL_length(*sl); read_pos++) {
        if (strcmp(str, (*sl)[read_pos]) == 0) {
            free((*sl)[read_pos]);
            continue;
        }

        new_sl[write_pos] = (*sl)[read_pos];
        write_pos++;
    }

    new_sl[new_len - 1] = nullptr;
    *sl = new_sl;
}

unsigned int SL_length(StringList sl) {
    unsigned int len = 0;
    for (; sl[len]; len++) {}
    return len;
}

unsigned int SL_count(StringList sl, const char *str) {
    unsigned int count = 0;
    for (int i = 0; sl[i]; i++)
        if (strcmp(sl[i], str) == 0) count++;
    return count;
}

int SL_first_index_of(StringList sl, const char *str) {
    for (int i = 0; sl[i]; i++)
        if (strcmp(sl[i], str) == 0) return i;
    return -1;
}

void SL_sort_with_fn(StringList sl, SortFn fn) {
    if (!sl || !*sl) return;
    qsort(sl, SL_length(sl), sizeof(char *), reinterpret_cast<int(*)(const void*,const void*)>(fn));
}

void SL_sort(StringList sl) {
    SL_sort_with_fn(sl, strcmp);
}

void SL_remove_duplicates(StringList *sl) {
    if (!*sl) return;

    unsigned int count_unique = 0;

    for (unsigned int i = 0; i < SL_length(*sl); i++) {
        for (int j = i-1; j >= 0; j--)
            if (strcmp((*sl)[i], (*sl)[j]) == 0) goto continue_count_loop;

        count_unique++;
        continue_count_loop:
    }

    StringList new_sl = static_cast<StringList>(malloc(sizeof(char *) * (count_unique + 1)));

    for (unsigned int read_pos = 0, write_pos = 0; read_pos < SL_length(*sl) && write_pos < count_unique; read_pos++) {
        for (int j = read_pos-1; j >= 0; j--)
            if (strcmp((*sl)[read_pos], (*sl)[j]) == 0) {
                free((*sl)[read_pos]);
                goto continue_write_loop;
            }

        new_sl[write_pos++] = (*sl)[read_pos];
        continue_write_loop:
    }

    *sl = new_sl;
}
