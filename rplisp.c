#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "stack.h"
#include "symbols.h"
#include "atom.h"
#include "execute.h"
#include "core.h"

extern int yyparse();

int main(int argc, char **argv){
	init_stack(INIT_STACK_SIZE);
	init_symbol_table(INIT_SYMBOL_TABLE_SIZE);
	push_core_functions();
	yyparse();
	execute(exec_entry_pt);
#ifdef DEBUG
	print_stack();
#endif
	free_stack();
	free_symbol_table();
	return 0;
}
