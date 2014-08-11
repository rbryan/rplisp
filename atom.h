#ifndef _ATOM_H_
#define _ATOM_H_

enum atom_type{
	JUMP	=	1, //Jump to another atom
	TERM	=	2, //Terminal atom pushes its value to the stack.
	INT 	=	4, //Integer type
	FLOAT	=	8, //Float type (actually a double but we don't care.)
	STRING	=	16, //String type
	CALL	=	32 //Call to a function.

};

struct atom {
	int type; //atom_type enum

	//Value stored by the atom. We want it to always fit
	//in the native wordsize of the processor.
	union atom_data { 
		double float_t;
		int integer_t;
		char * string_t;
		struct atom *jump_t;
		void (*call_t)();
	} data;
};

extern struct atom *new_atom();

#endif
