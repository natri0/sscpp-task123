#include "gets_string.h"

#include <cstring>

char *get_line_from_string(char *buffer, int buffer_size, char **string) {
    char *first_nl = strchr(*string, '\n');
    if (first_nl == nullptr) first_nl = &(*string)[strlen(*string)];

    char old_ch = first_nl[1];
    first_nl[1] = '\0';
    strlcpy(buffer, *string, buffer_size);
    first_nl[1] = old_ch;

    *string = first_nl + 1;
    return buffer;
}

bool string_ptr_is_eof(const char **string) {
    return !*string || !**string;
}
