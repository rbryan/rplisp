#ifndef _SYMBOL_H_
#define _SYMVOL_H_

#include "atom.h"

struct symbol {
	char * ident; //identifier string
	struct atom *sl; //stack location	
};

void init_symbol_table();

#endif
