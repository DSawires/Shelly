#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define NORMAL 0
#define NEWLINE 1
#define NULLBYTE 2

char *get_token(char **ptr, int* status) {
  char *tok = (char*) malloc(80);
  char *del = *ptr;
  char *lines;
  int i = 0;
  while (isspace(**ptr)) {
    if (**ptr == '\n') {
      *status = NEWLINE;
      (*ptr)++;
      lines = (char*)malloc(80);
      for (i; (*ptr)[i] != '\0'; i++) {
        lines[i] = (*ptr)[i];
      }
      lines[i] = '\0';
      free(del);
      (*ptr) = lines;
      return NULL;
    }
    (*ptr)++;
  }
  if (*ptr[0] == '\0') {
    (*ptr)++;
    lines = (char*)malloc(80);
    lines[0] = '\0';
    free(del);
    (*ptr) = lines;
    *status = NULLBYTE;
    return NULL;
  } else {
    int j = 0;
    while (!isspace(**ptr)) {
      tok[j] = **ptr;
      (*ptr)++;
      j++;
    }
    tok[j] = 0;
    *status = NORMAL;
    lines = (char*)malloc(80);
    for (i; (*ptr)[i] != '\0'; i++) {
      lines[i] = (*ptr)[i];
    }
    lines[i] = '\0';
    free(del);
    (*ptr) = lines;
    return tok;
  }   
}

int main(int argc, char **argv, char **envp) {
  char *line = (char*) malloc(80);
  size_t size = 80;
  int ret;  

  printf("Enter a line of input\n");
  if ((ret = getline(&line, &size, stdin)) < 0) {
    perror("getline");
    return -1;
  } 
  /* assert: input line stored in line[] */

  int status = 0;
  char **arr= (char**) malloc(sizeof(char*)*5);

  for (int i = 0; status == 0 && i < 5; i++) {
    arr[i] = (char*)0;
  }

  for (int i = 0; status == 0 && i < 5; i++) {
    arr[i] = get_token(&line, &status);
  }

  char *a = (char*)0;
  free(line);
  
  if (arr[4] != a) {
    perror("number of tokens in input exceeds limit");
    for (int i = 0; status = 0 && i < 5; i++) {
      free(arr[i]);
    }
    return -1;
  } 

  if ((ret = fork()) < 0) {
    printf("fork() FAILED");
    perror("forkeg");
    _exit(1);
  }

  if (ret != 0) {
    printf("parent is waiting\n");
    wait(0);
  } else {
    printf("child execve call\n");
    if ((ret = execve(arr[0], arr, envp)) < 0) {
      perror("execve");
      return -1;
    } 
    _exit(1);
  }

  wait(NULL);
  printf("Wait is done\n");

  int i = 0;
  while ((arr)[i]) {
    free(arr[i]);
    i++;
  }

  return 0;
}
