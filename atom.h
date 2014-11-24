#ifndef _ATOM_H_
#define _ATOM_H_

enum atom_type{

	START, //Start atom indicates beginning of expression.
	TERM, //Terminal atom indicates end of expression.
	EXIT, //Exit the current expression.
	JUMP, //Jump to another atom
	INT, //Integer type
	FLOAT, //Float type (actually a double but we don't care.)
	STRING, //String type
	CALL, //Call to a function.
	REF, //Reference to a function.
	IDENT //Identifier (string)


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

		//apprantly I can't cast a union to a pointer
		//type as per gcc so I made this instead.
		void * vd; 
	} data;
};

struct atom *new_atom();
void print_atom(struct atom *a);
struct atom * cp_atom( struct atom *a);
void print_atom_type(struct atom *);
#endif
