#include <cstdio>

#include "anytype.h"

int main() {
    AnyType t;
    t = 1;
    printf("%d\n", (int) t);

    try {
        printf("%c\n", (char) t);
    } catch (BadCast e) {
        printf("bad cast\n");
    }
    return 0;
}
