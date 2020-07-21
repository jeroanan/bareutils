#include<stdio.h>
#include <stdlib.h>

#include "inc/string_to_number.h";

int get_number_of_lines(char* strIn);
void limit_stdin(int number_of_lines);

int main(int argc, char* argv[]) {
  char *str;
  long nlines;

  if (argc!=2) {
    fprintf(stderr, "%s: Usage: %s NUMBER_OF_LINES\n", argv[0], argv[0]);
    exit(EXIT_FAILURE);
  }

  str = argv[1];
  
  if (string_to_number(str, &nlines)) {
    fprintf(stderr, "Invalid number of lines: %s\n", str);
    exit(EXIT_FAILURE);
  }

  limit_stdin(nlines);

  exit(EXIT_SUCCESS);
}

void limit_stdin(int number_of_lines) {
  int i;
  ssize_t read;
  char* line = NULL;
  size_t len = 0;
  
  for (int i=0;i<number_of_lines;i++) {
    if ((read = getline(&line, &len, stdin)==-1)) {
      break;
    }
    printf("%s", line);
  }
}
