#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* prog;

int get_number_of_lines(char* strIn);
int get_number_of_lines_in_file(char* strIn);
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
  nlines = abs(get_number_of_lines_in_file(str));
  limit_stdin(nlines);
}

int get_number_of_lines_in_file(char* strIn) {
  char *endptr;
  long nlines;

  nlines = strtol(strIn, &endptr, 10);

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
