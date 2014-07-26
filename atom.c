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


