#ifndef _ATOM_H_
#define _ATOM_H_

enum atom_type{

	START = 1, //Start atom indicates beginning of expression.
	TERM = 2, //Terminal atom indicates end of expression.
	EXIT = 4, //Exit the current expression.
	JUMP = 8, //Jump to another atom
	INT = 16, //Integer type
	FLOAT = 32, //Float type (actually a double but we don't care.)
	STRING = 64, //String type
	CALL = 128, //Call to a function.
	REF = 256, //Reference to a function.
	IDENT = 512, //Identifier (string)
	STACK = 1024 //Identifies an atom as living only on the stack.


};

struct atom {
	int type; //atom_type enum

	//Value stored by the atom. We want it to always fit
	//in the native wordsize of the processor.
	union atom_data { 
		double float_t;
		int int_t;
		char * string_t;
		struct atom **jump_t;
		void (*call_t)();
	} data;
};

struct atom *new_atom();
void print_atom(struct atom *a);

#endif
