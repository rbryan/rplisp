#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "execute.h"
#include "atom.h"
#include "stack.h"


//Entry point for execution.
//This should be set when we push the core functions
//while initializing the stack.
struct atom **exec_entry_pt; 

struct atom ** execute(struct atom **sp){
	struct atom *current;

	sp--; //we expect to be called on a start;

	while(1){
		current = *sp;

		switch(current->type){
			case JUMP:
				execute(current->data.jump_t);
				break;
			case CALL:
				(current->data.call_t)();
				break;
			case INT:
				u_push_atom(current);
				break;
			case FLOAT:
				u_push_atom(current);
				break;
			case STRING:
				u_push_atom(current);
				break;
			case REF:
				u_push_atom(current);
				break;
			case START:
				// Start executing the function recursively.
				// --sp so that we don't get caught in a loop
				// of start calls and have a stack overflow.
				sp = execute(sp);	
				break;
			case EXIT:
				sp = find_terminal(sp);
				return sp;
			case TERM:
				return sp;
			default:
				break;
					
		}

		sp--;
	}
}

	
struct atom **find_terminal(struct atom **sp){
	while(1){
		if((*sp)->type == TERM)
			return sp;
		else
			sp--;
	}
}
