
enum atom_type{
	JUMP	=	1,
	TERM	=	2,
	INT 	=	4,
	FLOAT	=	8,
	STRING	=	16,
	CALL	=	32

};

struct atom {
	int type;
	union atom_data {
		double float_t;
		int integer_t;
		char * string_t;
		struct atom *jump_t;
		void (*call_t)();
	} data;
};

extern struct atom *new_atom();
