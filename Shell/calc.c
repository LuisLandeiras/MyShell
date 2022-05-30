#include "shell.h"
#include <math.h>

void calc(char *value1, char *op, char *value2){
    double x = atof(value1);
    double y = atof(value2);
    if(*op == '^'){
        printf("%.3f\n", powf(x,y));
    }
    if(*op == '+'){
        printf("%.3f\n", x+y);
    }
    if(*op == '-'){
        printf("%.3f\n", x-y);
    }
    if(*op == '*'){
        printf("%.3f\n", x*y);
    }
    if(*op == '/' || *op == '%'){
        if(y == 0){
            printf("Erro, impossível dividir por 0\n");
        }else{
            printf("%.3f\n", x/y);
        }  
    }
    if(*op != '/' && *op != '*' && *op != '-' && *op != '+' && *op != '^' && *op != '%'){
        printf("Erro\n");
    }
}

void bits(char *value1, char *op, char *value2){
    int x = atoi(value1);
    int y = atoi(value2);
    if(*op == '&'){
        printf("%d\n", x&y);
    }
    if(*op == '|'){
        printf("%d\n", x|y);
    }
    if(*op == '^'){
        printf("%d\n", x^y);
    }
    if(*op != '^' && *op != '|' && *op != '&'){
        printf("Erro\n");
    }
}

