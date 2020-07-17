#include <stdio.h>

int main(int argc, char* argv[]) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  if (argc<2) {
    fprintf(stderr, "%s: Usage: %s FILE...\n", argv[0], argv[0]);
    return 1;
  }

  for (int i=1;i<argc;i++) {
    fp = fopen(argv[i], "r");

    if (fp==NULL) {
      fprintf(stderr, "%s: %s: no such file\n", argv[0], argv[1]);
      return 2;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
      printf("%s", line);
    }

    fclose(fp);
  }
  return 0;
}
