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
  int ret, i;  

  int status = 0;
  char **arr = (char**) malloc(sizeof(char*)*10);

  printf("Terminal: ");
  while ((ret = getline(&line, &size, stdin)) != -1) {
    if (ret < 0 && ret != -1) {
      perror("getline");
      return -1;
    }

    status = 0;

    for (int i = 0; i < 10; i++) {
      arr[i] = (char*)0;
    }

    for (i = 0; status == 0 && i < 10; i++) {
      arr[i] = get_token(&line, &status);
    }

    if (status == 1 && i == 1) {
      free(line);
      printf("Terminal: ");
      line = (char*) malloc(80);
      continue;
    }

    char *a = (char*)0;

    if ((ret = fork()) < 0) {
      perror("fork");
      _exit(1);
    }

    if (ret != 0) {
      wait(0);
    } else {
      if ((ret = execve(arr[0], arr, envp)) < 0) {
      perror("execve");
      return -1;
    } 
      _exit(1);
    }
    i = 0;
    while (arr[i]) {
      free(arr[i]);
      i++;
    }
    free(line);
    line = (char*) malloc(80);
    printf("Terminal: ");
  }
  wait(NULL);

  return 0;
}
