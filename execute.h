#ifndef _EXECUTE_H_
#define _EXECUTE_H_

//Entry point for execution.
//This should be set when we push the core functions
//while initializing the stack.
extern struct atom **exec_entry_pt;

struct atom ** execute(struct atom **sp);
struct atom **find_terminal(struct atom **sp);

#endif
