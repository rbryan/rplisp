#include <stdio.h>
#include <stdlib.h>
#include "symbols.h"
#include "stack.h"
#include "error.h"
#include "config.h"

struct symbol *ssp; //Symbol stack pointer;
unsigned int symbol_table_size;
struct symbol *symbol_table; 

//Set up the symbol table.
void init_symbol_table(unsigned int size){
	
	symbol_table = calloc(1,sizeof(struct symbol)*size);
	
	if(symbol_table == NULL)
		error("Initializing symbol table: Out of memory.");

	symbol_table_size = size;
	
	ssp = &symbol_table[0];


}

//Push a symbol to the symbol table.
void push_symbol(char *id, struct atom *loc){
	ssp->ident = id;
	ssp->sl = loc;

	if( (long) (ssp+1) - (long) (symbol_table) < symbol_table_size)
		ssp++;
	else
		error("Pushing symbol: Symbol table overflow.");

}

//Pop a symbol from the symbol table.
void pop_symbol(){
	if(ssp == symbol_table)
		error("Popping symbol: Symbol table already empty.");
	ssp--;
	free(ssp->ident);
	
}

//Print the symbol table.
void print_symbol_table(){
	int i;
	for(i=0; &symbol_table[i] != ssp ; i++){
		printf("\n");
		printf("Symbol:\t%s\n", symbol_table[i].ident);
		printf("Atom:\t%ld\n", (long) symbol_table[i].sl);
		printf("\n");	
	}
	
}

//Free the symbol table.
void free_symbol_table(){
	free(symbol_table);
}
