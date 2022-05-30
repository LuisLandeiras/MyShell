// redirects.c
// redirects are handled in reverse order: i) 2> ii) > OU > iii)<
#include "shell.h"
#define FILE_MODE (S_IRUSR | S_IWUSR)

int redirects(int numargs, char *args[])
{

    // i redirect do 2>
    // ii redirect stdout >
    int code = ultimo(&numargs, args);
    int pid, status;
    if ((pid = fork()) < 0)
    {                    /* cria um processo progenito */
        perror("forks"); /* NOTE: perror() produz uma pequema mensagem de erro para o stream */
        exit(1);         /* estandardizado de erros que descreve o ultimo erro encontrado */
                         /* durante uma chamada ao sistema ou funcao duma biblioteca */
    }

    if (pid == 0)
    {
        int fd;
        if (numargs < 3)
        {
            execvp(args[0], args);
            return numargs;
        } // Guard the following section

        if ((strcmp(args[numargs - 2], "2>")) == 0)
        {
            if (fork() == 0)
            {

                fd = creat(args[numargs - 1], FILE_MODE);
                if (fd == -1)
                {
                    perror("open");
                    exit(1);
                }
                dup2(fd, STDERR_FILENO);

                close(fd);
                numargs = numargs - 2;
                args[numargs] = NULL;
                execvp(args[0], args);

                perror("execvp as failed");
                exit(1);
            }
        }
        if (numargs < 3)
        {
            return numargs;
        } // Guard the following section

        if (strcmp(args[numargs - 2], ">") == 0)
        {

            fd = creat(args[numargs - 1], FILE_MODE);
            if (fd < 0)
            {
                perror(NULL);
                return -1; /*indicar um erro*/
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[numargs - 2] = NULL;
            numargs = numargs - 2;
            execvp(args[0], args);
            perror("execvp as failed");
            exit(1);
        }
        if (numargs < 3)
        {
            return numargs;
        } // Guard the following section
        if (strcmp(args[numargs - 2], ">>") == 0)
        {
            if (access(args[numargs - 1], F_OK) == -1)
            {
                fd = creat(args[numargs - 1], FILE_MODE);
                if (fd < 0)
                {
                    perror(NULL);
                    return -1; /*indicar um erro*/
                }
            }
            else
            {
                fd = open(args[numargs - 1], O_APPEND | O_WRONLY);
                if (fd < 0)
                {
                    perror(NULL);
                    return -1; /*indicar um erro*/
                }
            }
            if (fd < 0)
            {
                perror(NULL);
                return -1; /*indicar um erro*/
            }
            printf("%s", args[numargs - 1]);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[numargs - 2] = NULL;
            numargs = numargs - 2;
            execvp(args[0], args);
            perror("execvp as failed");
            exit(1);
        }

        if (numargs < 3)
        {
            return numargs;
        } // Guard the following section
        if (strcmp(args[numargs - 2], "<") == 0)
        {

            fd = open(args[numargs - 1], O_RDONLY);
            if (fd < 0)
            {
                perror(NULL);
                return -1; /*indicar um erro*/
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[numargs - 2] = NULL;
            numargs = numargs - 2;
            execvp(args[0], args);
            perror("execvp as failed");
            exit(1);
        }
        return numargs;
    }
    if (code == FG)
        while (wait(&status) != pid)
            /*spin fazer nada */;
    return 0;
}
