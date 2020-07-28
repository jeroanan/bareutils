#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/process_stdin.h";
#include "../lib/WjCryptLib/WjCryptLib_Md5.h"

void process_line(char *line, size_t len);
void read_finished(void);
int i;

char** buffer;
char *line = NULL;

int main() {

  process_stdin(process_line, read_finished);

  return 0;
}

void process_line(char *line, size_t len) {
    buffer = (char**) realloc(buffer, (i+1) * sizeof(char*));
    buffer[i] = (char*) malloc(len * sizeof(char*));
    strcpy(buffer[i], line);
    i++;
}

void read_finished(void) {
  Md5Context md5ctx;
  MD5_HASH hash;
  int j;

  Md5Initialise(&md5ctx);

  for (j=0;j<i;j++) {
    Md5Update(&md5ctx, buffer[j], (uint32_t)strlen(buffer[j]));
    free(buffer[j]);
  }
  free(buffer);
  
  Md5Finalise(&md5ctx, &hash);

  for(i=0;i<sizeof(hash);i++)
  {
    printf( "%2.2x", hash.bytes[i] );
  }
  printf( "\n" );
}
