#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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

