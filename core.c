#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "symbols.h"
#include "stack.h"
#include "core.h"
#include "error.h"

void (*core_functions[])() = {_def,_print,_add,NULL};
const char *fn_names[] = {"def","print","+",NULL};

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

void _print(){
	struct atom *a;

	a = u_pop_atom();

	print_atom(a);

	free(a);
}

void int_add(struct atom *a, struct atom *b){
	
	a->data.int_t = a->data.int_t + b->data.int_t;

	u_push_atom(a);

	free(b);

}

void float_add(struct atom *a, struct atom *b){
	
	a->data.float_t = a->data.float_t + b->data.float_t;

	u_push_atom(a);

	free(b);
}

void _add(){
	struct atom *a, *b;

	a = u_pop_atom();
	b = u_pop_atom();

	if(a->type != b->type)
		error("Addition: Numbers need to be of the same type.");
	
	if(a->type == FLOAT)
		float_add(a,b);
	else
		int_add(a,b);

}

void _def(){
	struct symbol *sym;
	struct atom *id;
	struct atom *ref;
	char *ident;

	id = u_pop_atom();

	if(id->type != IDENT)
		error("Call: def: Arg 1: IDENT exected.");

	ref = u_pop_atom();

	if(ref->type != REF)
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
