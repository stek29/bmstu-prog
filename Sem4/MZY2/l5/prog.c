#include <stdio.h>
#include <string.h>

extern int contains(char* str, int strl, char* substr, int subl);

int main(void) {
    char buf1[255];
    char buf2[255];

    for (;;) {
        if (fgets(buf1, sizeof(buf1), stdin) == NULL) break;
        if (fgets(buf2, sizeof(buf1), stdin) == NULL) break;

        int l1 = strlen(buf1);
        int l2 = strlen(buf2);

        if (buf1[l1-1] == '\n') --l1;
        if (buf2[l2-1] == '\n') --l2;

        buf1[l1] = '\0';
        buf2[l2] = '\0';

        int c = contains(buf1, l1, buf2, l2);

        printf("'%s' contains '%s': %s\n", buf1, buf2, c?"yes":"no");
    }

    return 0;
}
