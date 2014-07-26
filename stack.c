#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "error.h"
#include "symbols.h"
#include "core.h"
#include "atom.h"


struct atom **stack;
unsigned int stack_size;
struct atom **vsp;
struct atom **usp;

void init_stack(unsigned int size){

	stack_size = size;

	stack = calloc(size,sizeof(struct data *));

	if(stack == NULL)
		error("Allocating Stack: Out of memory.");
	
	usp = &stack[0];
	vsp = &stack[size-1];

	push_core_functions();

	return;
	
}

void v_push_atom(struct atom *a){
	*vsp = a;
	vsp--;
	return;
}

struct atom *v_pop_atom(){
	struct atom *popped;
	vsp++;
	popped = *vsp;
	*vsp = NULL;
	return popped;
}

void u_push_atom(struct atom *a){
	*usp = a;
	usp++;
	return;
}

struct atom *u_pop_atom(){
	struct atom *popped;
	usp--;
	popped = *usp;
	*usp = NULL;
	return popped;
}






