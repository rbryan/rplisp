CC=gcc
CFLAGS= -O0 -g -Wall

%.c : %.l
%.c : %.y


COMP = $(CC) $(CFLAGS)

rplisp: rplisp.o stack.o lex.yy.o rplisp.tab.o Makefile
	$(COMP) rplisp.o lex.yy.o rplisp.tab.o -o rplisp

rplisp.o: rplisp.c config.h
	$(COMP) -c rplisp.c

stack.o: stack.c stack.h
	$(COMP) -c stack.c

lex.yy.c: rplisp.l
	flex rplisp.l

rplisp.tab.c rplisp.tab.h: rplisp.y
	bison -d rplisp.y

lex.yy.o: lex.yy.c rplisp.tab.h
	$(COMP) -c lex.yy.c

rplisp.tab.o: rplisp.tab.c
	$(COMP) -c rplisp.tab.c

clean: 
	rm *.o lex.yy.c rplisp.tab.c rplisp.tab.h 
