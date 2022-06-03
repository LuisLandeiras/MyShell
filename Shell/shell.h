#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>

int parse(char *buf, char **args);
void execute(char **args);
int builtin(char **args);

typedef struct
{
    char msg[100]; 
    int tempo;
} aviso_t;
typedef struct
{
    char fonte[100];
    char destino[100];
} copiar_t;

#define BG 0
#define FG 1

void * avisowrapper();
void * socpwrapper();
void calc();
void bits();
void maior();
int wait();
int redirects();
int prop();
int isjpeg();
int rmr();
int setx();
int socp();
int ultimo();
int parse();
int valido();