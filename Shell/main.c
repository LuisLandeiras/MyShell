#include "shell.h"

char prompt[100];

int main ()
{
  int len;
  char linha[1024];/* um comando */
  char *args[64];/* com um maximo de 64 argumentos */

  strcpy (prompt, "SOSHELL>");
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
    parse(linha, args);/* particiona a string em argumentos */

    if (!builtin (args))
      execute (args);/* executa o comando */
    }
  return 0;
}

int builtin (char **args)
{
  //usado para sair da shell(Funcional)
  if (strcmp (args[0], "exit") == 0)
  {
    exit (0);
    return 1;
  }

  //usado para indicar a versão atual da shell(Funcional)
  if (0 == strcmp(args[0], "obterinfo"))
  {
    printf("SoShell 2020 versão 1.0\n");
    return 1;
  }

  //(Funcional)
  if (strlen(args[0])>4 && 0 == strncmp(args[0], "PS1=", 4))
  {
    strcpy(prompt, args[0]+4);
    return 1;
  }

  //usado para mostrar informações sobre o utilizador(Funcional)
  if (0 == strcmp(args[0], "quemsoueu"))
  {
    system("id");
    return 1;
  }

  //usado para se movimentar entre diretorias
  if (0 == strcmp(args[0], "cd"))
  {
    int err;
    if(NULL == args[1] || strcmp(args[1], "~") == 0){
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

  //usado para fazer calculos matematicos simples(Funcional)
  if (0 == strcmp(args[0], "calc")){
    calc(args[1], args[2], args[3]);
    return 1;
  }

  //usado para efetuar calculos binarios(Funcional)
  if (0 == strcmp(args[0], "bits")){
    bits(args[1], args[2], args[3]);
    return 1;
  }
  
  //usado para verificar se um ficheiro é um jpeg(Funcional) 
  if (0 == strcmp(args[0], "jpeg"))
  {
    int f = open(args[1], O_RDONLY);
    if (isjpeg(f) == 1){
      printf("Is a jpeg\n");
    }
    else{
      printf("Is not a jpeg\n");
    }
    return 1;
  }
  
  //usado para mostrar um aviso dado um n tempo com threads(Funcional)
  if (0 == strcmp(args[0], "aviso"))
  {
    pthread_t th;
    aviso_t * ptr = (aviso_t *)malloc(sizeof(aviso_t));
    strcpy(ptr->msg, args[1]);
    ptr->tempo = atoi(args[2]);
    pthread_create(&th, NULL, avisowrapper, (void *)ptr);
    return 1;
  }

  //usado para verificar qual o maior de dois ficheiros(Funcional)
  if(0 == strcmp(args[0], "maior")){
    maior(args[1], args[2]);
    return 1;
  }

  //Torna um ficheiro executavel(Não funcional)
  if(0 == strcmp(args[0], "setx")){
    setx(args[1]);
    return 1;
  }

  //usado para remover a leitura de um ficheiro(Não funcional)
  if(0 == strcmp(args[0], "removel")){
    rmr(args[1]);
    return 1;
  }

  //usado para copiar um ficheiro para outro com threads(Funcional)
  if (0 == strcmp(args[0], "socpth")){
    pthread_t th;
    copiar_t *ptr = (copiar_t *)malloc(sizeof(copiar_t));
    strcpy(ptr->fonte, args[1]);
    strcpy(ptr->destino, args[2]);
    pthread_create(&th, NULL, socpwrapper, (void *)ptr);
    return 1;
  }

  //usado para copiar um ficheiro para outro sem threads(Funcional)
  if(0 == strcmp(args[0], "socp")){
    socp(args[1], args[2]);
    return 1;
  }

  if(0 == strcmp(args[0], "openfiles")){
    if(valido()){
      printf("Número de ficheiros abertos: %i\n", valido());
    }
    return 1;
  }
  return 0;
}
