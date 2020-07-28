#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/process_stdin.h"

char **buffer;
int line_counter;

void process_line(char *line, size_t len);
void read_finished();

int main(void) {

  void (*process_func)(char*, size_t);
  void (*read_finished_func)(void);

  process_func = process_line;
  read_finished_func = read_finished;

  process_stdin(process_func, read_finished_func);

  return 0;
}

void process_line(char *line, size_t len) {
  int i = line_counter;

  buffer = (char**) realloc(buffer, (i+1) * sizeof(char*));
  buffer[i] = (char*) malloc(len * sizeof(char*));
  strcpy(buffer[i], line);
  line_counter++;
}

void read_finished() {
  int j;

  for (j=line_counter-1;j>=0;j--) {
    printf("%s", buffer[j]);
    free(buffer[j]);
  }
  free(buffer);
}
