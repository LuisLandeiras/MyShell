#include "shell.h"

char prompt[100];

int main ()
{
  int len;
  char linha[1024];/* um comando */
  char *args[64];/* com um maximo de 64 argumentos */

  strcpy (prompt, "MYSHELL: prompt>");
  while (1)
  {
    printf ("%s", prompt);
    if (fgets (linha, 1023, stdin) == NULL)
    {
      printf ("\n");
      exit (0);
    }
    len = strlen (linha);
    if (1 == len)
      continue;/* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
    parse (linha, args);/* particiona a string em argumentos */

    if (!builtin (args))
      execute (args);/* executa o comando */
    }
  return 0;
}

int builtin (char **args)
{
  //argumento usado para sair da shell
  if (strcmp (args[0], "exit") == 0)
  {
    exit (0);
    return 1;
  }

  if (strncmp (args[0], "42", 2) == 0)
  {
    printf ("42 is the answer to life the universe and everything\n");
    return 1;
  }

  //argumento usado para indicar a versão atual da shell
 if (0 == strcmp(args[0], "info"))
  {
    printf("SoShell 2020 versão 1.0\n");
    return 1;
  }

  if (strlen(args[0])>4 && 0 == strncmp(args[0], "PS1=", 4))
  {
    strcpy(prompt, args[0]+4);
    return 1;
  }

  //argumento usado para mostrar informações sobre o utilizador
  if (0 == strcmp(args[0], "me"))
  {
    system("id");
    return 1;
  }

  //argumento usado para se movimentar entre diretorias
  if (0 == strcmp(args[0], "cd"))
  {
    int err;
    if(NULL == args[1] || strcmp(args[1], "~")==0){
      err = chdir(getenv("HOME"));
    }else{
      err = chdir(args[1]);
    }
    if (err<0)
    {
      perror(args[1]);
    }
    return 1;
  }

  //argumento usado para fazer calculos matematicos simples
  if (0 == strcmp(args[0], "calc")){
    calc(args[1], args[2], args[3]);
    return 1;
  }

  //argumento usado para efetuar calculos binarios
  if (0 == strcmp(args[0], "bits")){
    bits(args[1], args[2], args[3]);
    return 1;
  }

  //argumento semelhante ao cat do linux 
  if (0 == strcmp(args[0], "cat"))
  {
    if (0 == strcmp(args[2], ">") || 0 == strcmp(args[2], ">>") || 0 == strcmp(args[2], "2>") || 0 == strcmp(args[2], "<") || NULL == args[2])
    {
      redirects(4,args[2]);
      return 1;
    }
  }
  
  //argumento usado para verificar se um ficheiro é um jpeg
  if (0 == strcmp(args[0], "isjpeg"))
  {
    isjpeg(args[1]);
    if (1 == isjpeg(args[1]))
    {
      printf("É um jpeg\n");
    }
    else
    {
      printf("Não é um jpeg\n");
    }
    return 1;
  }
  
  if (0 == strcmp(args[0], "aviso"))
  {
    pthread_t th;
    aviso_t * ptr = (aviso_t *)malloc(sizeof(aviso_t));
    strcpy(ptr->msg, args[1]);
    ptr->tempo=atoi(args[2]);
    pthread_create(&th, NULL, avisowrapper(aviso()), (void *)ptr);
    return 1;
  }

  //argumento usado para verificar qual o maior de dois ficheiros
  if(0 == strcmp(args[0], "maior")){
    maior(args[1], args[2]);
    return 1;
  }

  //argumento que modifica a propriedade de um ficheiro
  if(0 == strcmp(args[0], "prop")){
    propriedade(args[1]);
    return 1;
  }
  return 0;
}
