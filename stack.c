#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "error.h"
#include "atom.h"


struct atom *stack;
unsigned int stack_size;

void init_stack(unsigned int size){
	stack = calloc(size,sizeof(struct atom *));
	if(stack == NULL)
		error("Allocating Stack: Out of memory.");
}

