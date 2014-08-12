#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include "atom.h"

struct symbol {
	char * ident; //identifier string
	struct atom *sl; //stack location	
};

extern struct symbol *ssp;
extern struct symbol *symbol_table;
extern unsigned int symbol_table_size;

void init_symbol_table(unsigned int size);
void free_symbol_table();
void print_symbol_table();

#endif
