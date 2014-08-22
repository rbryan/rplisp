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
#ifdef DEBUG	
	printf("Pushing start\n");
#endif
	new = new_atom();

	new->type = START;
	new->data.jump_t = NULL; //set when the corresponding term is pushed
	
	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
	return;
}

void push_term(){
	struct atom *new;
#ifdef DEBUG
	printf("Pushing end\n");
#endif
	new = new_atom();
	
	new->type = TERM;
	new->data.jump_t = NULL; //set later when start is found.

	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
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
#ifdef DEBUG	
	printf("Pushing float:\t%f\n",n);
#endif	
	new = new_atom();

	new->type = FLOAT;
	new->data.float_t = n;

	v_push_atom(new);
#ifdef DEBUG	
	print_stack();
#endif
	return;
}

void push_int(int n){
	struct atom *new;
#ifdef DEBUG
	printf("Pushing int:\t%d\n",n);
#endif
	new = new_atom();

	new->type = INT;
	new->data.int_t = n;

	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
	return;
}

void push_string(char * s){
	struct atom *new;
#ifdef DEBUG	
	printf("Pushing string:\t%s\n",s);
#endif
	new = new_atom();

	new->type = STRING;
	new->data.string_t = s;

	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
	return;
}

void push_ref(struct atom **ref){
	
	struct atom * new;
#ifdef DEBUG
	printf("Pushing ref:\t%ld\n",(long) ref);
#endif
	new = new_atom();

	new->type = REF;
	new->data.jump_t = ref;

	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
	return;
}

void push_exit(){
	
	struct atom * new;
#ifdef DEBUG
	printf("Pushing exit.\n");
#endif
	new = new_atom();

	new->type = EXIT;

	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
	return;
}

void push_ident(char * id){
	struct atom *new;
#ifdef DEBUG
	printf("Pushing ident:\t%s\n",id);
#endif
	new = new_atom();

	new->type = IDENT;
	new->data.string_t = id;

	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
	return;
}


void push_jump(struct atom **j){
	
	struct atom * new;
#ifdef DEBUG
	printf("Pushing jump:\t%ld\n",(long) j);
#endif
	new = new_atom();

	new->type = JUMP;
	new->data.jump_t = j;

	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
	return;
}

void push_call( void (*fn)()){

	struct atom *new;
#ifdef DEBUG
	printf("Pushing call:\t%ld\n",(long) fn);
#endif
	new = new_atom();

	new->type = CALL;
	new->data.call_t = fn;

	v_push_atom(new);
#ifdef DEBUG
	print_stack();
#endif
	return;
}

