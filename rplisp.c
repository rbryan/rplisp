#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "stack.h"
#include "symbols.h"
#include "atom.h"
#include "execute.h"

extern int yyparse();

int main(int argc, char **argv){
	init_stack(INIT_STACK_SIZE);
	init_symbol_table(INIT_SYMBOL_TABLE_SIZE);
	yyparse();
	execute();
	free_stack();
	free_symbol_table();
	return 0;
}
