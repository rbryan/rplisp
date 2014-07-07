CC=clang
CFLAGS= -O0 -g -Wall



COMP = $(CC) $(CFLAGS)

rplisp: rplisp.o
	$(COMP) rplisp.o -o rplisp

rplisp.o: rplisp.c
	$(COMP) -c rplisp.c
