#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_WIDTH 6

int main(void) {
  ssize_t read;
  char* line = NULL;
  size_t len = 0;
  int i;
  i=1;

  for (1;;) {
    if ((read = getline(&line, &len, stdin)==-1)) {
      break;
    }
    
    printf("%*d  %s", NUMBER_WIDTH, i, line);
    i++;
  }

  return EXIT_SUCCESS;
}


