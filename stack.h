
extern struct atom **stack;
extern unsigned int stack_size;
extern struct atom **vsp;
extern struct atom **usp;


void init_stack(unsigned int size);
void free_stack();
struct atom *u_pop_atom();
struct atom *v_pop_atom();
void u_push_atom(struct atom *a);
void v_push_atom(struct atom *a);
