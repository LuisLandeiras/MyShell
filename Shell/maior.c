#include "shell.h"

void maior(char *value1, char *value2){
    FILE *f1, *f2;
    char c1, c2;
    if((f1 = fopen(value1, "r")) == NULL){
        printf("Erro ao abrir o ficheiro %s\n", value1);
    }
    if ((f2 = fopen(value2, "r")) == NULL)
    {
        printf("Erro ao abrir o ficheiro %s\n", value2);
    }
    c1 = fgetc(f1);
    c2 = fgetc(f2);
    if(c1 > c2){
        printf("%s\n", value1);
    }
    if(c1 < c2){
        printf("%s\n", value2);
    }
}