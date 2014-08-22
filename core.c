#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "symbols.h"
#include "stack.h"
#include "core.h"
#include "error.h"

void (*core_functions[])() = {def,print,add,NULL};
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

void print(){
	struct atom *a;

	a = u_pop_atom();

	print_atom(a);

	//free the atom if it existed purely on the stack.
	if(a->type & STACK)
		free(a);
}

void add(){
	struct atom *a;
	struct atom *b;
	struct atom *new;

	a = u_pop_atom();
	b = u_pop_atom();

	//Later improvement to reuse other
	//variables that were created on the stack?
	new = new_atom(); 

	if(a->type & FLOAT || b->type & FLOAT){
		new->type = FLOAT & STACK;
	}else{
		new->type = INT & STACK;
	}

	if(a->type & FLOAT){
		if(b->type & FLOAT)
			new->data.float_t =  a->data.float_t + b->data.float_t;
		else
			new->data.float_t = a->data.float_t + b->data.int_t;
	}else{
		if(b->type & FLOAT)
			new->data.float_t = a->data.int_t + b->data.float_t;
		else
			new->data.int_t = a->data.int_t + b->data.int_t;
	}

	if(a->type & STACK)
		free(a);
	if(b->type & STACK)
		free(b);

	
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

	if(ref->type != REF)
		error("Call: def: Arg 2: REF expected.");

	ident = id->data.string_t;

	sym = search_symbol_table(ident);

	if(sym)
		sym->sl = ref->data.jump_t;
	else
		push_symbol(ident,ref->data.jump_t);

	//Free the atoms that were used if they live on
	//the stack.
	//I don't know that either of these are possible
	//but we'll check anyway.
	if(id->type & STACK)
		free(id);
	if(ref->type & STACK)
		free(ref);

}
