CC=gcc
FLAGS=-O2 -Wall -Werror -lncurses
OBJ=cell_space.o  input.o  output.o conway.o
BIN=conway

conway: $(OBJ)
	$(CC) -o $@ $^ $(FLAGS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY:
	clean

clean:
	rm *.o
	rm $(BIN)
