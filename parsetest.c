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
  int i;

  

  printf("t = %s", *ptr);

  while (isspace(**ptr)) {
    if (**ptr == '\n') {
      *status = NEWLINE;
      (*ptr)++;
      lines = (char*)malloc(80);
      for (i = 0; (*ptr)[i] != '\0'; i++) {
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

int main() {
  size_t size = 80;
  int ret;  

  while(1) {
  char *line = (char*) malloc(80);
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

  int i = 0;
  while ((arr)[i]) {
    printf("%s\n", arr[i]);
    free(arr[i]);
    i++;
  }
  }

  return 0;
}
