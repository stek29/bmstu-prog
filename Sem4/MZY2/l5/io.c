#include <stdio.h>
#include <string.h>

extern
#ifdef __MINGW32__
    __stdcall
#endif
    char*
    lcsubstr(char* str, int strl, int* lclen);

#define MAX_STR_LEN 255
const int MAX_WORD_CNT = (MAX_STR_LEN+1) / 2;

int main(void) {
    char strbuf[MAX_STR_LEN + 1] = {0};
#ifndef RELEASE
    printf("Enter string (up to %d chars):\n", MAX_STR_LEN);

    if (fgets(strbuf, sizeof(strbuf), stdin) == NULL) {
        printf("Error: Can't read string\n");
        return 1;
    }
#else
    strcpy(strbuf, "jjjjjj h regpeo      fperk tpke ad");
#endif

    int len = strlen(strbuf);

    if (strbuf[len - 1] == '\n') {
        strbuf[len - 1] = '\0';
        --len;
    }

    int lclen = 0;
    char* lcs = lcsubstr(strbuf, len, &lclen);

    printf("LCS: '%.*s'\n", lclen, lcs);
    printf("LCS len: %d\n", lclen);

    getchar();
    return 0;
}
