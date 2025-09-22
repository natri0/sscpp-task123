#include "gets_string.h"

#include <cstring>

size_t get_line_from_string(char **buffer, int *buffer_size, char **string) {
    char *first_nl = strchr(*string, '\n');
    if (first_nl == nullptr) first_nl = &(*string)[strlen(*string)];
    size_t len = first_nl - *string;

    *buffer = strndup(*string, len+1);
    *buffer_size = len+2;
    *string = first_nl + 1;
    return len;
}

bool string_ptr_is_eof(const char **string) {
    return !*string || !**string;
}
