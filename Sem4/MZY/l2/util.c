#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define die_s(s) do { perror(s); abort(); } while (0)
#define die die_s(__func__)

void GetStr(char* buf, int size) {
  if (fgets(buf, size, stdin) != buf) {
    die;
  }
}

void PutStr(char *buf) {
  if (printf("%s", buf) < 0) {
    die;
  }
}

void IntToStr(int v, char* buf, int bufsize) {
  int rv = snprintf(buf, bufsize, "%d", v);
  if (rv < 0) {
    die;
  }
}

int StrToInt(char* buf) {
  int v;
  int rv = sscanf(buf, "%d", &v);
  if (rv != 1) {
    die;
  }
  return v;
}

