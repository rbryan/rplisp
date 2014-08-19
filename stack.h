#ifndef _STACK_H_
#define _STACK_H_

extern struct atom **stack;
extern unsigned int stack_size;
extern struct atom **vsp;
extern struct atom **usp;


void init_stack(unsigned int size);
void free_stack();
void print_stack();
struct atom *u_pop_atom();
struct atom *v_pop_atom();
void u_push_atom(struct atom *a);
void v_push_atom(struct atom *a);
void push_int(int num);
void push_float(double num);
void push_string(char * s);
void push_term();
void push_start();
void push_exit();
void push_ref(struct atom **ref);
void call(char *id, int len);
void connect_ends();

#endif
