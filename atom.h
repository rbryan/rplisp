


struct atom {
	int type;
	union atom_data {
		double float_t;
		int integer_t;
		char * string_t;
		struct atom *reference_t;
		void * pointer_t;
	} data;
};

extern struct atom *new_atom();
