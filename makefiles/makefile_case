CC = gcc
OBJ = case.o main.o
FLAGS = -g -Wall
EXEC = case

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(FLAGS)

%.o: %.c %.h
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -i *.o
	rm -i *.*~