#include "shell.h"

int FileSize(FILE *file){
    int i = 0;
    char *line1 = NULL;
    int c;
    while ((c = fgetc(file)) != EOF){
        line1 = (char *)realloc(line1, sizeof(char) * (i + 2));
        line1[i] = c;
        i++;
    }
    return i;
}

void maior(char *value1, char *value2){
    FILE *f1, *f2;
    f1 = fopen(value1, "rb");
    f2 = fopen(value2, "rb");
    int size1 = FileSize(f1)/1024;
    int size2 = FileSize(f2)/1024;
    if(size1 > size2){
        printf("O maior ficheiro é %s e tem o tamanho de %d Kb\n", value1, size1);
    }else if(size1 < size2){
        printf("O maior ficheiro é %s e tem o tamanho de %d Kb\n", value2, size2);
    }else{
        printf("Os ficheiros tem o mesmo tamanho\n");
    }
}