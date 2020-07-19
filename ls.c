#include <dirent.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  
  struct dirent **namelist;
  int n,i;

  /* got this from the manpage for scandir */
  n = scandir(".", &namelist, NULL, alphasort);
  if (n == -1) {
    perror("scandir");
    exit(EXIT_FAILURE);
  }

  for(i=0;i<n;i++) {
    printf("%d\t%s\n", namelist[i]->d_ino, namelist[i]->d_name);
    free(namelist[i]);
  }
  free(namelist);

  exit(EXIT_SUCCESS);
}

