#include<stdio.h>
#include <stdlib.h>

#include "inc/string_to_number.h";
#include "inc/process_stdin.h";

int i;
long nlines;

void process_line(char *line, size_t len);

int main(int argc, char* argv[]) {
  char *str;

  if (argc!=2) {
    fprintf(stderr, "%s: Usage: %s NUMBER_OF_LINES\n", argv[0], argv[0]);
    exit(EXIT_FAILURE);
  }

  str = argv[1];
  
  if (string_to_number(str, &nlines)) {
    fprintf(stderr, "Invalid number of lines: %s\n", str);
    exit(EXIT_FAILURE);
  }

  i=0;
  process_stdin(process_line, read_finished_do_nothing);

  exit(EXIT_SUCCESS);
}

void process_line(char *line, size_t len) {
  printf("%s", line);

  if (++i == nlines) {
    exit(EXIT_SUCCESS);
  }
}
