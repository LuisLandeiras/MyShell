#include "shell.h"

int setx(char *nome) {
    if(chmod(nome, S_IXUSR) < 0){
        return 1;
    }
    return 0;
}

int rmr(char *nome) {
    if (chmod(nome, ~S_IRUSR) < 0){
        return 1;
    }
    return 0;
}