#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/process_stdin.h"

#define NUMBER_WIDTH 6

int i;
void process_line(char *line, size_t length);

int main(void) {
  i=1;

  process_stdin(process_line, read_finished_do_nothing);

  return EXIT_SUCCESS;
}

void process_line(char *line, size_t length) {
  printf("%*d  %s", NUMBER_WIDTH, i, line);
  i++;
}
