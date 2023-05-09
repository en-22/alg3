CFLAGS = -Wall -g

all: myavl

myavl: myavl.o AVLTree.o
	gcc -o myavl myavl.o AVLTree.o

myavl.o: myavl.c
	gcc -c myavl.c $(CFLAGS)

AVLTree.o: AVLTree.c AVLTree.h
	gcc -c AVLTree.c $(CFLAGS)

clean:
	-rm *.o

purge:
	-rm *.o myavl