CC=gcc
CC=gcc
CFLAGS=-I.
DEPS = tetris.h
OBJ = tetris.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tetris: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
