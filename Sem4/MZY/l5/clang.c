#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void process_words(char* str);

void print_word_pair(char* w1, int w1len, char* w2, int w2len) {
#ifdef DEBUG
  printf("'%p:%d' и '%p:%d'\n", w1, w1len, w2, w2len);
#endif
  printf("'%.*s' и '%.*s'\n", w1len, w1, w2len, w2);
}

#ifdef DEBUG
void debug_wordscan(char* str, int word_count, char** word_starts, int* word_lens) {
  printf("%s\n", __func__);
  printf(
      "str:         %p\n"
      "word_count:  %d\n"
      "word_starts: %p\n"
      "word_lens:   %p\n",
      str, word_count, word_starts, word_lens
  );

  for (int i = 0; i != word_count; ++i) {
    printf("#%03d: %p:%03d -- %.*s\n",
        i, word_starts[i], word_lens[i],
        word_lens[i], word_starts[i]);
  }
}
#endif

int main(void) {
  char str[256];

  printf("Введите слова, разделенные пробелами: \n");
  if (fgets(str, sizeof(str), stdin) != str) {
    printf("Error\n");
    return 1;
  }

  int slen = strlen(str);
  if (str[slen - 1] == '\n') {
    str[slen - 1] = '\0';
  }

#ifdef DEBUG
  printf("str: %p\n(%s)\n\n", str, str);
#endif

  process_words(str);

  return 0;
}

