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

    *sl = static_cast<StringList>(realloc(*sl, sizeof(char *) * (SL_length(*sl) + 2)));
    (*sl)[SL_length(*sl)] = strdup(str);
    (*sl)[SL_length(*sl) + 1] = nullptr;
}

void SL_remove(StringList *sl, const char *str) {
    if (!sl || !*sl) return;

    unsigned int new_len = SL_length(*sl) + 1 - SL_count(*sl, str);
    auto *new_sl = static_cast<StringList>(malloc(sizeof(char *) * new_len));

    for (unsigned int read_pos = 0, write_pos = 0; read_pos < SL_length(*sl); read_pos++) {
        if (strcmp(str, *sl[read_pos]) == 0)
            free(*sl[read_pos]);

        new_sl[write_pos] = *sl[read_pos];
        write_pos++;
    }

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
