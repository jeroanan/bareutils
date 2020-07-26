#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/WjCryptLib/WjCryptLib_Md5.h"

int main() {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char** buffer;
  int i,j;
  Md5Context md5ctx;
  MD5_HASH hash;

  i=0;
  for (1;;) {
    if ((read = getline(&line, &len, stdin)==-1)) {
      break;
    }

    buffer = (char**) realloc(buffer, (i+1) * sizeof(char*));
    buffer[i] = (char*) malloc(len * sizeof(char*));
    strcpy(buffer[i], line);
    i++;
  }

  Md5Initialise(&md5ctx);

  for (j=i-1;j>=0;j--) {
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

  return 0;
}
