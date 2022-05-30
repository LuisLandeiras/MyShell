#include "shell.h"

/*void ioCopy(int IN, int OUT){
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
}*/

int ioCopy(int IN, int OUT){ // no error reporting
    int n;
    char buf[128];
    while ((n = read(IN, buf, 128)) > 0){
        if (write(OUT, buf, n) != n){
            perror("Erro de escrita!\n");
            return 1;
        }
    }
    if (n < 0){
        perror("Erro de leitura!\n");
        return 1;
    }
    return 0;
}

int socp(char *fonte, char *destino){
    int fi, fo;
    fi = open(fonte, O_RDONLY);
    if (fi < 0){
        perror("Erro ao abrir o ficheiro!\n");
        return 1;
    }
    if (access(destino, F_OK) == 0){
        if ((fo = open(destino, O_RDWR)) < 0){
            perror("Erro ao abrir o ficheiro!\n");
            return 1;
        }
    }
    else{
        fo = creat(destino, 0777);
    }

    int i = ioCopy(fi, fo);
    close(fi);
    close(fo);
    return i;
}

void * socpwrapper(void *args){
    copiar_t *ptr = (copiar_t *)args;
    int i = (socp(ptr->fonte, ptr->destino));
    if (i == 1){
        perror("Erro a copiar\n");
    } 
    else{
        printf("Copiado com sucesso\n");
    }
    void * a = &i;
    free(ptr);
    return a;
}



