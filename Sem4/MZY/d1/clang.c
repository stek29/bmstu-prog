#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct charinfo {
  int freq;
  char ch;
};

extern int process_text(char *str, int strlen, struct charinfo *info);

#ifdef DEBUG
extern int char_info_buf['Z' - 'A' + 1];
#endif

int main(void) {
  char str[256];

  printf("Enter string:\n");
  if (fgets(str, sizeof(str), stdin) != str) {
    printf("Error\n");
    return 1;
  }

  struct charinfo infos['Z' - 'A' + 1];
  // memset(infos, 0, sizeof(charinfo));

  int slen = strlen(str);
  int chcnt = process_text(str, slen, infos);

  printf("Unique letters: %d\n", chcnt);

#ifdef DEBUG
  for (int i = 'A'; i != 'Z' + 1; ++i) {
    printf("buf[%c] = %d\n", i, char_info_buf[i - 'A']);
  }
#endif

  for (int i = 0; infos[i].ch != 0; ++i) {
    printf("%c: %d times\n", infos[i].ch, infos[i].freq);
  }

  return 0;
}

