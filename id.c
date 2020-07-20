#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  uid_t euid;
  struct passwd* pwent;
  gid_t *groupids;
  int ngroups;
  long ngroups_max;
  struct group* group;

  euid = geteuid();
  pwent = getpwuid(euid);
  group = getgrgid(pwent->pw_gid);

  ngroups_max = sysconf(_SC_NGROUPS_MAX) + 1;

  ngroups = getgroups(0, groupids);

  groupids = (gid_t *)malloc(ngroups * sizeof(gid_t));

  getgroups(ngroups_max, groupids);

  printf("uid=%d(%s) gid=%d(%s) groups=", euid, pwent->pw_name, pwent->pw_gid, group->gr_name);

  while (ngroups) {
    --ngroups;
    group = getgrgid(groupids[ngroups]);
    printf("%d(%s)", group->gr_gid, group->gr_name);
    if (ngroups) printf(",");
  }

  printf("\n");

  free(groupids);
  exit(EXIT_SUCCESS);
}
