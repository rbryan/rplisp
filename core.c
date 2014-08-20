#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "symbols.h"
#include "stack.h"
#include "core.h"
#include "error.h"

void (*core_functions[])() = {def,NULL};
const char *fn_names[] = {"def",NULL};

//todo
void push_core_functions(){
	int i;
	for(i=0; core_functions[i] != NULL; i++){
		//vsp should be the start location of the function
		push_symbol(fn_names[i],vsp); 
		//push the function
		push_start();
		push_call(core_functions[i]);
		push_term();
		//vsp should now be the stack location just after the function.
		//This space should later be filled by the start of the users
		//program.
		exec_entry_pt = vsp;

	}
}

void def(){
	struct symbol *sym;
	struct atom *id;
	struct atom *ref;
	char *ident;

	id = u_pop_atom();

	if(id->type != IDENT)
		error("Call: def: Arg 1: IDENT exected.");

	ref = u_pop_atom();

	if(id->type != REF)
		error("Call: def: Arg 2: REF expected.");

	ident = id->data.string_t;

	sym = search_symbol_table(ident);

	if(sym)
		sym->sl = ref->data.jump_t;
	else
		push_symbol(ident,ref->data.jump_t);

	free(id);
	free(ref);
}
