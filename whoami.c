#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  uid_t euid;
  struct passwd* pwent;

  euid = geteuid();
  pwent = getpwuid(euid);
  printf("%s\n",pwent->pw_name);

  exit(EXIT_SUCCESS);
}

