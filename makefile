CFLAGS = -Wall -g # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
    objects = AVLTree.o myavl.o

myavl.o: myavl.c
	$(CC) -c $(CFLAGS) myavl.c

AVLTree.o: AVLTree.c
	$(CC) -c $(CFLAGS) AVLTree.c

all: AVLTree.o
	$(CC) -o myavl myavl.o AVLTree.o $(LDFLAGS)

clean:
	rm -f $(objects) *~

purge: clean
	rm -f myavl

