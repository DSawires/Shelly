#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv, char**envp) {
  int a;
  char *arr[] = {"/usr/bin/grep", "a*", "shell_6.c"};
  //close(0);
  //a = open("shell_6.c", O_RDONLY);
  execve("/usr/bin/grep", arr, envp);
  //close(a);
}