#include <stdio.h>
#include <stdlib.h>

void process_stdin(
    void (*line_processor)(char*, size_t), 
    void (*read_finished)(void)) {

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  for (1;;) {
    if ((read = getline(&line, &len, stdin)==-1)) {
      break;
    }
    
    line_processor(line, len);
  }

  read_finished();
}

void read_finished_do_nothing(void) {} 
