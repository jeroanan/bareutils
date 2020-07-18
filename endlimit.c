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
  nlines = get_number_of_lines_in_file(str);
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
  int i,x;
  int number_to_print;
  ssize_t read;
  char* line = NULL;
  size_t len = 0;
  char** file_content;
  
  file_content = malloc(1 * sizeof(char*));

  i=0;
  for (1;;) {
    if ((read = getline(&line, &len, stdin)==-1)) {
      break;
    }
    
    file_content = (char**) realloc(file_content, ((i+1) * sizeof(char*)));
    file_content[i] = malloc(strlen(line) *sizeof(char*));

    strcpy(file_content[i], line);
    i++;
  }

  number_to_print = number_of_lines<i ? number_of_lines : i;
  int start_point = i-number_to_print;

  for (x=start_point;x<i;x++) {
    printf("%s", file_content[x]);
  }

  for(x=0; x<i; x++) {
    free(file_content[x]);
  }

  free(file_content);
}
