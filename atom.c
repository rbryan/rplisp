#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "atom.h"
#include "stack.h"



struct atom *new_atom(){
	struct atom *new;
	new = calloc(1,sizeof(struct atom));
	
	if(new == NULL)
		error("Allocating Atom: Out of memory.");

	return new;
	
}

void print_atom_type(struct atom *a){

	printf("\tType:\t");

	switch(a->type){
		
		case START:	printf("START\n");
				break;
		
		case TERM:	printf("TERM\n");
				break;
				
		case JUMP:	printf("JUMP\n");
				break;

		case INT:	printf("INT\n");
				break;

		case FLOAT:	printf("FLOAT\n");
				break;

		case STRING:	printf("STRING\n");
				break;

		case CALL:	printf("CALL\n");
				break;

		case REF:	printf("REF\n");
				break;

		case EXIT:	printf("EXIT\n");
				break;

		case IDENT:	printf("IDENT\n");
				break;
				

		default:
				error("Printing Atom Type: Unknown atom type");
	

	}

}

void print_atom(struct atom *a){

	switch(a->type){
		
		case START:	
				break;
		
		case TERM:
				break;
				
		case JUMP:
				printf("%ld\n", (long) a->data.jump_t - (long) stack);
				break;

		case INT:
				printf("%d\n", a->data.int_t);
				break;

		case FLOAT:
				printf("%f\n", a->data.float_t);
				break;

		case STRING:
				printf("%s\n", a->data.string_t);
				break;

		case CALL:	
				printf("%ld\n", (long) a->data.call_t - (long) stack);
				break;

		case REF:
				printf("%ld\n", (long) a->data.jump_t - (long) stack);
				break;

		case EXIT:
				break;

		case IDENT:
				printf("%s\n", a->data.string_t);
				break;
				

		default:
				error("Pretty Printing Atom: Unknown atom type");
	

	}

}

struct atom * cp_atom( struct atom *a){

	struct atom *new;

	new = new_atom();
	
	new->type = a->type;
	new->data = a->data;

	return new;
}


