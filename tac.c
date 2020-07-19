#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char** buffer;
  int i,j;

  i=0;
  for (1;;) {
    if ((read = getline(&line, &len, stdin)==-1)) {
      break;
    }

    buffer = (char**) realloc(buffer, (i+1) * sizeof(char*));
    buffer[i] = (char*) malloc(len * sizeof(char*));
    strcpy(buffer[i], line);
    i++;
  }

  for (j=i-1;j>=0;j--) {
    printf("%s", buffer[j]);
    free(buffer[j]);
  }
  free(buffer);

  return 0;
}
