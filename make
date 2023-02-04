shell:  shell.o
    gcc -c shell.c

shell.o:  shell.c
    gcc -o shell shell.o

shell:  extra.o
    gcc -c extra.c

shell.o:  extra.c
    gcc -o extra extra.o
