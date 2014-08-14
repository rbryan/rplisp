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

//print the stack
void print_stack(){
	int i;
	printf("Variable Stack:\n");
	for(i=stack_size-1; &stack[i] != vsp; i--){
		printf("-----\n");
		printf("%d",i);
		print_atom(stack[i]);
	}

	printf("User Stack:\n");
	for(i=0; &stack[i] != usp; i++){
		printf("-----\n");
		printf("%d",i);
		print_atom(stack[i]);
	}

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

void push_start(){
	struct atom *new;
	
	printf("Pushing start\n");

	new = new_atom();

	new->type = START;
	new->data.jump_t = NULL; //set when the corresponding term is pushed
	
	v_push_atom(new);

	print_stack();
	return;
}

void push_term(){
	struct atom *new;

	printf("Pushing end\n");

	new = new_atom();
	
	new->type = TERM;
	new->data.jump_t = NULL; //set later when start is found.

	v_push_atom(new);

	print_stack();
	return;
}

//Connects the current term to the corresponding start.
//When this is called the function term should have just
//been pushed.
void connect_ends(){
	struct atom **term;
	struct atom **current;

	term = vsp + 1;

	if((*term)->type != TERM || (*term)->data.jump_t != NULL)
		error("Connecting ends: TERM not found.");

	current = term;

	while(1){
		current++;

		if(current == stack + stack_size)
			error("Connecting ends: Corresponding START not found.");

		if((*current)->type == START && (*current)->data.jump_t == NULL)
			break;
	}

	(*current)->data.jump_t = term;
	(*term)->data.jump_t = current;

	return;

}

void push_float(double n){
	struct atom *new;
	
	printf("Pushing float:\t%f\n",n);
	
	new = new_atom();

	new->type = FLOAT;
	new->data.float_t = n;

	v_push_atom(new);
	
	print_stack();
	return;
}

void push_int(int n){
	struct atom *new;

	printf("Pushing int:\t%d\n",n);

	new = new_atom();

	new->type = INT;
	new->data.integer_t = n;

	v_push_atom(new);
	print_stack();
	return;
}

void push_string(char * s){
	struct atom *new;
	
	printf("Pushing string:\t%s\n",s);

	new = new_atom();

	new->type = STRING;
	new->data.string_t = s;

	v_push_atom(new);
	print_stack();
	return;
}

void call(char *id, int len){
	printf("%s\n",id);
	return;
}






