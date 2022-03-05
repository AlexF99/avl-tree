all:
	gcc -c avl.c -o avl.o
	gcc -g main.c avl.o -o main.o
