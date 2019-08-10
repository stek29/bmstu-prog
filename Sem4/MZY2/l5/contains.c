#ifndef RELEASE
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef RELEASE
#define DEBUG printf
#else
#define DEBUG
#endif

#ifdef __MINGW32__
__stdcall
#endif
    int
    contains(char* str, int strl, char* sub, int subl) {
    DEBUG("%s(%.*s, %d, %.*s, %d)", __func__, strl, str, strl, subl, sub, subl);

    int found = 0;
    int subpos = 0;

    for (int i = 0; i != strl; ++i) {
        // DEBUG("str[%d] = %c\n", i, str[i]);
        // DEBUG("sub[%d] = %c\n", subpos, sub[subpos]);
        if (sub[subpos] == str[i]) {
            // DEBUG("++subpos\n");
            ++subpos;
        } else {
            subpos = (sub[0] == str[i]) ? 1 : 0;
            // DEBUG("subpos = %d\n", subpos);
        }

        // DEBUG("\n");
        if (subpos == subl) {
            found = 1;
            break;
        }
    }

    DEBUG(" = %d\n", found);
    fflush(stdout);

    return found;
}