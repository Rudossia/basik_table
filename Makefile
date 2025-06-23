CFLAGS= -g -fsanitize=address,undefined


all: build  clean

build:
	gcc  -c -Wall -Wextra -Werror -ftrapv  main.c -o main.o -lreadline $(CFLAGS)
	gcc -c -Wall -Wextra -Werror -ftrapv table.c -o stack.o $(CFLAGS)
	gcc  main.o table.c -o tabl -lreadline $(CFLAGS)


clean:
	rm -rf *.o
