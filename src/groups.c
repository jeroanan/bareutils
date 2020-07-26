#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  uid_t euid;
  struct passwd* pwent;
  gid_t *groupids;
  struct group* group;
  int ngroups;
  long ngroups_max;

  euid = geteuid();
  pwent = getpwuid(euid);
  group = getgrgid(pwent->pw_gid);

  ngroups_max = sysconf(_SC_NGROUPS_MAX) + 1;

  ngroups = getgroups(0, groupids);

  groupids = (gid_t *)malloc(ngroups * sizeof(gid_t));

  getgroups(ngroups_max, groupids);

  while (ngroups) {
    --ngroups;
    group = getgrgid(groupids[ngroups]);
    printf("%s", group->gr_name);
    if (ngroups) printf(" ");
  }
  printf("\n");

  free(groupids);
  return 0;
}
