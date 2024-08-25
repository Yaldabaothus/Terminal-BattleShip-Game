CC=clang-18
LIBS=-lncursesw

main: main.c
	$(CC) -o main main.c $(LIBS)