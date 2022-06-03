#include "shell.h"

int valido(int fd){
    int soma = 0;
    for (int fd = 0; fd < 255; fd++){
        if(fcntl(fd, F_GETFD) != -1 || errno != EBADF){
            soma++;
        } 
    } 
    return soma;
}