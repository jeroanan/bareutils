#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char* prog;

int get_number_of_lines(char* strIn);
void limit_stdin(int number_of_lines);

int main(int argc, char* argv[]) {
  char *str;
  long nlines;

  if (argc!=2) {
    fprintf(stderr, "%s: Usage: %s NUMBER_OF_LINES\n", argv[0], argv[0]);
    exit(EXIT_FAILURE);
  }

  prog = argv[0];
  str = argv[1];
  nlines = get_number_of_lines(str);

  exit(EXIT_SUCCESS);
}

int get_number_of_lines(char* strIn) {
  char *endptr;
  long nlines;

  nlines = strtol(strIn, &endptr, 10);
  limit_stdin(nlines);

  errno = 0;

  if ((errno == ERANGE && (nlines == LONG_MAX || nlines == LONG_MIN))
      || (errno !=0 && nlines == 0)) {
    perror("strtol");
    exit(EXIT_FAILURE);
  }

  if (endptr==strIn || *endptr!= '\0') {
    fprintf(stderr, "%s: %s: not a valid number of lines\n", prog, strIn);
    exit(EXIT_FAILURE);
  }

  return nlines;
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
