#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/string_to_number.h";
#include "inc/process_stdin.h";

long nlines;
int c, lines_read;
char** file_content;

void process_line(char *line, size_t len);
void read_finished(void);

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

  file_content = malloc(nlines * sizeof(char*));
  c=0;
  process_stdin(process_line, read_finished);
  //limit_stdin(nlines);
}

void process_line(char *line, size_t len) {
  int x;

  file_content[c] = malloc(strlen(line) *sizeof(char*));
  strcpy(file_content[c], line);

  if (c<nlines) {
    c++;
  } else {
    for (x=1;x<=c;x++) {
      file_content[x-1] = (char*) realloc(file_content[x-1], strlen(file_content[x]) * sizeof(char*));
      strcpy(file_content[x-1], file_content[x]);
    }
  }
  lines_read++;
}

void read_finished(void) {
  int number_to_print, x;

  number_to_print = nlines<lines_read ? nlines : lines_read; 

  for (x=0;x<number_to_print;x++) {
    printf("%s", file_content[x]);
  }

  for(x=0; x<c; x++) {
    free(file_content[x]);
  }

  free(file_content);
}

