#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "stack.h"
#include "atom.h"

extern int yyparse();

int main(int argc, char **argv){
	init_stack(INIT_STACK_SIZE);
	yyparse();
	return 0;
}
