#include "shell.h"
#define BUFFSIZE 128

void ioCopy(int IN, int OUT){
    int n;
    char buf[BUFFSIZE];
    while ( ( n = read (IN, buf, BUFFSIZE)) > 0){
       if (write (OUT, buf, n) != n)
       perror("Erro de escrita!\n");
    }
    if (n < 0){
        perror("Erro de leitura!\n");
    }
    fclose(IN);
    fclose(OUT);
}

void copy(char *fonte, char *destino){
    FILE *f1 = fopen(fonte, "rb");
    FILE *f2 = fopen(destino, "wb");
    ioCopy(f1, f2);
}




