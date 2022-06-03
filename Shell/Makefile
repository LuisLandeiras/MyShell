#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=main.o execute.o parse.o calc.o redirects.o aviso.o jpeg.o maior.o setx.o socp.o openfiles.o -lpthread

#Alvo por defeito é o primeiro
all :  soshell

main.o : shell.h main.c
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
calc.o : shell.h calc.c 
	$(CC) $(FLAGS) calc.c
redirects.o : shell.h redirects.c
	$(CC) $(FLAGS) redirects.c
aviso.o : shell.h aviso.c
	$(CC) $(FLAGS) aviso.c
jpeg.o : shell.h jpeg.c
	$(CC) $(FLAGS) jpeg.c
maior.o : shell.h maior.c
	$(CC) $(FLAGS) maior.c
setx.o : shell.h setx.c
	$(CC) $(FLAGS) setx.c
socp.o : shell.h socp.c
	$(CC) $(FLAGS) socp.c
openfiles.o : shell.h openfiles.c
	$(CC) $(FLAGS) openfiles.c
soshell : $(OBS)
	$(CC)  -o soshell  $(OBS) $(LIBS)
clean limpar:
	rm -f *.o
	rm -f *~
	echo "Clean"
