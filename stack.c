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

//Initialize the stack space.

void init_stack(unsigned int size){

	stack_size = size;

	stack = calloc(size,sizeof(struct atom *));

	if(stack == NULL)
		error("Allocating Stack: Out of memory.");
	
	usp = &stack[0];
	vsp = &stack[size-1];

	push_core_functions();

	return;
	
}

//Free the stack.

void free_stack(){
	int i;
	for(i=stack_size-1; &stack[i] != vsp; i--)
		free(stack[i]);

	for(i=0; &stack[i] != usp; i++)
		free(stack[i]);

	free(stack);
}

//Push an atom to the variable stack.
//User stack builds down from the top of the program space.

void v_push_atom(struct atom *a){
	*vsp = a;
	vsp--;
	return;
}

//Pop an atom from the variable stack.

struct atom *v_pop_atom(){
	struct atom *popped;
	vsp++;
	popped = *vsp;
	*vsp = NULL;
	return popped;
}

//Push an atom to the user stack.
//User stack builds up from the bottom.

void u_push_atom(struct atom *a){
	*usp = a;
	usp++;
	return;
}

//Pop an atom from the user stack.

struct atom *u_pop_atom(){
	struct atom *popped;
	usp--;
	popped = *usp;
	*usp = NULL;
	return popped;
}






