#include "shell.h"

int containspipe(int numArgs, char **args){
  int i;
  for(i=0;i<numArgs;i++){
    if(args[i][0]=='|'){
      return i;
    }
  return -1;
  }
}
int main()
{
    char *myargs[]= { "ls", "-l" , "-a", NULL};

    int indice, pidFilho, fd[2], numArgs;
    char **args = myargs;
    numArgs = 3;
    indice = containspipe(numArgs, args);
    if(indice == -1){
      execvp(*args, args);
    }
    if(indice > 0){
        printf ("pipe detected at index %d\n", indice);
        printf ("Remove PIPE symbol. Create Pipe. Fork(). Exec in 2 Processes\n");
        args[indice] = NULL;
        pipe (fd);
        pidFilho = fork ();
    }
    if ( pidFilho == 0){ //write
        numArgs = indice;
        fprintf (stderr,"cmd write to pipe: %s numArgs=%d\n", args[0], numArgs);
        dup2 (fd[1], STDOUT_FILENO);
        close (fd[0]); close (fd[1]);
    }else{ //read
        args = args + indice + 1;
        numArgs = numArgs - indice - 1;
        fprintf (stderr,"cmd read from pipe: %s numArgs=%d\n", args[0], numArgs);
    }
    return 0;
}