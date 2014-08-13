#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "atom.h"



struct atom *new_atom(){
	struct atom *new;
	new = calloc(1,sizeof(struct atom));
	
	if(new == NULL)
		error("Allocating Atom: Out of memory.");

	return new;
	
}

void print_atom(struct atom *a){

	printf("Type:\t");

	switch(a->type){
		
		case START:	printf("START\n");
				break;
		
		case TERM:	printf("TERM\n");
				break;
				
		case JUMP:	printf("JUMP\n");
				printf("Value:\t%ld\n", (long) a->data.jump_t);
				break;

		case INT:	printf("INT\n");
				printf("Value:\t%d\n", a->data.integer_t);
				break;

		case FLOAT:	printf("FLOAT\n");
				printf("Value:\t%f\n", a->data.float_t);
				break;

		case STRING:	printf("STRING\n");
				printf("Value:\t\"%s\"\n", a->data.string_t);
				break;

		case CALL:	printf("CALL\n");
				printf("Value:\t%ld\n", (long) a->data.call_t);
				break;
	

	}
}


