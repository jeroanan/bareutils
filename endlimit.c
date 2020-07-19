#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limit_stdin(int number_of_lines);
int string_to_number(char* strIn, long* n);

int main(int argc, char* argv[]) {
  char *str;
  int result;
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
}

int string_to_number(char* strIn, long* n) {
  char *endptr;

  *n = strtol(strIn, &endptr, 10);

  errno = 0;

  if ((errno == ERANGE && (*n == LONG_MAX || *n == LONG_MIN))
      || (errno !=0 && *n == 0)) {
    return 1;
  }

  if (endptr==strIn || *endptr!= '\0') {
    return 1;
  }

  return 0;
}

void limit_stdin(int number_of_lines) {
  int i,x,c;
  int number_to_print;
  ssize_t read;
  char* line = NULL;
  size_t len = 0;
  char** file_content;
  
  file_content = malloc(number_of_lines * sizeof(char*));

  i=0;
  c=0;
  for (1;;) {
    if ((read = getline(&line, &len, stdin)==-1)) {
      break;
    }
    
    file_content[c] = malloc(strlen(line) *sizeof(char*));
    strcpy(file_content[c], line);

    if (c<number_of_lines) {
      c++;
    } else {
      for (x=1;x<=c;x++) {
        file_content[x-1] = (char*) realloc(file_content[x-1], strlen(file_content[x]) * sizeof(char*));
        strcpy(file_content[x-1], file_content[x]);
      }
    }
    i++;
  }

  number_to_print = number_of_lines<i ? number_of_lines : i;

  for (x=0;x<number_to_print;x++) {
    printf("%s", file_content[x]);
  }

  for(x=0; x<c; x++) {
    free(file_content[x]);
  }

  free(file_content);
}
