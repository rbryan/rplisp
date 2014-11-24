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

void print_atom(struct atom *a){

	printf("\tType:\t");

	switch(a->type){
		
		case START:	printf("START\n");
				break;
		
		case TERM:	printf("TERM\n");
				break;
				
		case JUMP:	printf("JUMP\n");
				printf("\tValue:\t%ld\n", (long) a->data.jump_t - (long) stack);
				break;

		case INT:	printf("INT\n");
				printf("\tValue:\t%d\n", a->data.int_t);
				break;

		case FLOAT:	printf("FLOAT\n");
				printf("\tValue:\t%f\n", a->data.float_t);
				break;

		case STRING:	printf("STRING\n");
				printf("\tValue:\t\"%s\"\n", a->data.string_t);
				break;

		case CALL:	printf("CALL\n");
				printf("\tValue:\t%ld\n", (long) a->data.call_t - (long) stack);
				break;

		case REF:	printf("REF\n");
				printf("\tValue:\t%ld\n", (long) a->data.jump_t - (long) stack);
				break;

		case EXIT:	printf("EXIT\n");
				break;

		case IDENT:	printf("IDENT\n");
				printf("\tValue:\t%s\n", a->data.string_t);
				break;
				

		default:
				error("Printing Stack: Unknown atom type");
	

	}

}

struct atom * cp_atom( struct atom *a){

	struct atom *new;

	new = new_atom();
	
	new->type = a->type;
	new->data = a->data;

	return new;
}


