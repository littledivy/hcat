#include <string.h>
#include <stdio.h>

#include "color.h"

char* keywords[] = {
 "go",
 "package",
 "import"
 "func",
 "main",
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

int print_token(char* tok) {
  if(in(keywords, 5, tok)) {
    // Print keywords
    LOG_RED(tok);
    return 1;
  }
  return 0;
}
