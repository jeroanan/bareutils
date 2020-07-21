#include <dirent.h>
#include <error.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_node_type(struct stat* sb);

int main(int argc, char* argv[]) {
  
  struct dirent **namelist;
  char* dirtolist;
  char* pathname;
  int n,i;
  struct stat sb;
  char* nodetype;

  if (argc>2) {
    fprintf(stderr, "%s: usage: %s [DIR]\n", argv[0], argv[0]);
    exit(EXIT_FAILURE);
  }

  dirtolist = argc == 2 ? argv[1] : ".";

  /* got this from the manpage for scandir */
  n = scandir(dirtolist, &namelist, NULL, alphasort);
  if (n == -1) {
    perror("scandir");
    exit(EXIT_FAILURE);
  }

  for(i=0;i<n;i++) {
    pathname = (char*) malloc(strlen(dirtolist) + 1 + strlen(namelist[i]->d_name) * sizeof(char*));
    sprintf(pathname, "%s/%s", dirtolist, namelist[i]->d_name);

    if (lstat(pathname, &sb) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    } 

    nodetype = get_node_type(&sb);

    printf("%s\t%s\n", nodetype, namelist[i]->d_name);

    free(pathname);
    free(namelist[i]);
  }
  free(namelist);

  exit(EXIT_SUCCESS);
}

char* get_node_type(struct stat* sb) {

  switch(sb->st_mode & S_IFMT) {
    case S_IFBLK: 
      return "bd";
      break;
    case S_IFCHR:
      return "cd";
      break;
    case S_IFDIR:
      return "d";
      break;
    case S_IFIFO:
      return "fifo";
      break;
    case S_IFLNK:
      return "ln";
    case S_IFREG:
      return "f";
      break;
    case S_IFSOCK:
      return "sck";
      break;

    default: return "dunno";
  }

  return "";
}
