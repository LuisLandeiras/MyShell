/*execute . cria um processo prog�nito e executa um programa*/
#include "shell.h"
#define FILE_MODE (S_IRUSR | S_IWUSR)

/*int containsRedirect(int numargs, char **args){
  int index;
  for (index = 0; index < numargs; index++){
    if (strcmp(args[index], ">") == 0 || strcmp(args[index], "2>") == 0 || strcmp(args[index], "<") == 0 || strcmp(args[index], ">>") == 0){
      return index;
    }
  }
  return -1;
}*/

int ultimo(int *numargs, char **args){
  if (args[*numargs-1][0] == '&'){
    *numargs = *numargs - 1;
    args[*numargs] = NULL;
    return BG;
  }
  return FG;
}

int redirects(int numargs, char *args[])
{
  // i redirect do 2> fazer ainda
  if ( numargs < 3) {
    return numargs; //Guard the following section
  }
  if ( strcmp(args[numargs - 2] , ">") ==0){ // ii redirect stdout >
    int fd = creat(args[numargs - 1], FILE_MODE);
    if (fd < 0){ 
      perror(NULL); 
      return -1; /*indicar um erro*/
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    args[numargs - 2]=NULL ;
    numargs = numargs - 2;
  }
  if (strcmp(args[numargs - 2], ">>")==0) // verificar caso de append (>>) | tratar do >> open : O_WRONLY | O_APPEND
  {
      int fd = open(args[numargs - 1], O_WRONLY | O_APPEND);
      if (fd < 0)
      {
          perror(NULL);
          return -1;
      }
      dup2(fd, STDOUT_FILENO);
      close(fd);
      args[numargs - 2]=NULL;
      numargs = numargs - 2;
  } 
  if (strcmp(args[numargs - 2], "<")==0) // iii tratar do < open : O_RDONLY
  {
      int fd = open(args[numargs - 1], O_RDONLY);
      if (fd < 0)
      {
          perror(NULL);
          return -1;
      }
      dup2(fd, STDOUT_FILENO);
      close(fd);
      args[numargs - 2]=NULL;
      numargs = numargs - 2;
  }
return numargs;
}