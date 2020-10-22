CC=gcc
CC=gcc
CFLAGS=-I.
DEPS = tp2_tableau.h
OBJ = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tetris: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
