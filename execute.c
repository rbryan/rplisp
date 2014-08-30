#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "execute.h"
#include "atom.h"
#include "stack.h"
#include "symbols.h"


//Entry point for execution.
//This should be set when we push the core functions
//while initializing the stack.
struct atom **exec_entry_pt; 

struct atom ** execute(struct atom **sp){
	struct atom *current;

	struct symbol *sym; //used when an ident is encountered

	//Yes, I'm sorry okay. I alloc a new atom every time I push to
	//the user stack.
	//I know. It's terrible. It's inefficient. I hate myself for it.
	//But it works, it's simple, and it makes it easy to deal with
	//memory management because I know that everything that is on the
	//stack lives there. If anyone ever decides that this is a cool
	//project worth putting time into then a) they're foolish, and 
	//b) they can put in the time to rework this so that it's more 
	//efficient. 
	//To whom it may concern. I wish you luck. 
	// - R.E.B.

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
				u_push_atom(cp_atom(current));
				break;
			case FLOAT:
				u_push_atom(cp_atom(current));
				break;
			case STRING:
				u_push_atom(cp_atom(current));
				break;
			case REF:
				u_push_atom(cp_atom(current));
				break;
			case IDENT:
				sym = search_symbol_table(current->data.string_t);

				if(sym)
					execute(sym->sl);
				else	
					u_push_atom(cp_atom(current));

				break;
			case START:
				// Start executing the function recursively.
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
