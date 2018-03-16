CC=gcc
PROG=main

all: main.c f.o
	${CC} main.c f.o -o ${PROG}

main.o: main.c f.h
	${CC} -c main.c

generation.o: generation.c
	${CC} -c generation.c

matrice.o: matrice.c
	${CC} -c matrice.c

validation.o: validation.c
	${CC} -c validation.c

f.o: generation.c matrice.c validation.c f.h
	${CC} -c generation.c matrice.c validation.c

clean :
	- rm  *.o