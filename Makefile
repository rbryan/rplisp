CC=gcc
CFLAGS= -O0 -g -Wall

%.c : %.l
%.c : %.y


COMP = $(CC) $(CFLAGS)

rplisp: rplisp.o execute.o stack.o error.o atom.o core.o symbols.o lex.yy.o rplisp.tab.o Makefile
	$(COMP) rplisp.o execute.o lex.yy.o rplisp.tab.o error.o atom.o core.o stack.o symbols.o -o rplisp

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

error.o: error.c error.h
	$(COMP) -c error.c

atom.o: atom.c atom.h
	$(COMP) -c atom.c

core.o: core.c core.h
	$(COMP) -c core.c

symbols.o: symbols.c symbols.h
	$(COMP) -c symbols.c

execute.o: execute.c execute.h
	$(COMP) -c execute.c

clean: 
	rm *.o lex.yy.c rplisp.tab.c rplisp.tab.h 
