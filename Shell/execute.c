/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"

int containsRedirect(int numargs, char **args){
  int index;
  for (index = 0; index < numargs; index++)
  {
    if (strcmp(args[index], ">") == 0 || strcmp(args[index], "2>") == 0 || strcmp(args[index], "<") == 0 || strcmp(args[index], ">>") == 0)
    {
      return index;
    }
  }

  return -1;
}

int ultimo(int *numargs, char **args){
  if (args[*numargs-1][0] == '&'){
    *numargs = *numargs - 1;
    args[*numargs] = NULL;
    return BG;
  }
  return FG;
}

void execute(int numargs, char **args)
{

  int indice, pidFilho, fd[2];

  if (indice == -1)
  {
    if (containsRedirect(numargs, args) == -1)
    {
      int code = ultimo(&numargs, args);
      int pid, status;
      if ((pid = fork()) < 0)
      {                  /* cria um processo progenito */
        perror("forks"); /* NOTE: perror() produz uma pequema mensagem de erro para o stream */
        exit(1);         /* estandardizado de erros que descreve o ultimo erro encontrado */
                         /* durante uma chamada ao sistema ou funcao duma biblioteca */
      }

      if (pid == 0)
      {

        execvp(*args, args); /* NOTE: as versoes execv() e
                              * execvp() de execl() sao uteis quando */
        perror(*args);       /* o numero de argumentos nao e. conhecido.
                              * Os argumentos de  */
        fflush(stdout);

        exit(1);
      }

      if (code == FG)
        while (wait(&status) != pid)
          /*spin fazer nada */;
    }
    else
    {
      redirects(numargs, args);
    }
  }
  if (indice > 0)
  {
    int code = ultimo(&numargs, args);
    int pid, status;
    if ((pid = fork()) < 0)
    {                  /* cria um processo progenito */
      perror("forks"); /* NOTE: perror() produz uma pequema mensagem de erro para o stream */
      exit(1);         /* estandardizado de erros que descreve o ultimo erro encontrado */
                       /* durante uma chamada ao sistema ou funcao duma biblioteca */
    }

    if (pid == 0)
    {
      args[indice] = NULL;
      pipe(fd);
      pidFilho = fork();
      if (pidFilho == 0)
      { // write
        numargs = indice;
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
      }
      else
      { // read
        args = args + indice + 1;
        numargs = numargs - indice - 1;
        dup2(fd[0], STDIN_FILENO); // duplicar o descritor de ficheiro de leitura do PIPE para a posição na tabele de FD do STDIN
        close(fd[1]);
        close(fd[0]); // fechar o descritor do ficheiro do pipe que este processo não necessita.
      }
      if (containsRedirect(numargs, args) != -1)
      {
        redirects(numargs, args);
        exit(0);
      }
      else
      {
        execvp(*args, args);
      }
      return;
    }
    if (code == FG)
      while (wait(&status) != pid)
        /*spin fazer nada */;
  }
}