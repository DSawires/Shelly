#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>


int main(void) {
    char *ret;
    for (int i = 0; i < 20; i++){
    ret = malloc(80);
    ret[0] = 'a';
    ret[1] = 'b';
    ret[2] = '\0';
    printf("%s\n", ret);
    }
}