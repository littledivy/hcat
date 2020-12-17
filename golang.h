#include <string.h>
#include <stdio.h>

#include "color.h"

char* keywords[] = {
 "go",
 "package",
 "import"
 "func",
};

int in(char **arr, int len, char *target) {
  int i;
  for(i = 0; i < len; i++) {
    if(strncmp(arr[i], target, strlen(target)) == 0) {
      return 1;
    }
  }
  return 0;
}

void print_token(char* tok) {
  if(in(keywords, strlen(*keywords), tok)) {
    // Print keywords
    LOG_RED(tok);
  } else {
    printf("%s", tok);
  }
}
