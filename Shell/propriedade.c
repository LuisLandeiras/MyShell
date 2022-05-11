#include "shell.h"

int propriedade(char *nome) {
    struct stat s;
    if(chmod(nome, S_IXUSR) < 0){
        return 1;
    }
    return 0;
}