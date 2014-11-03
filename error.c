#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void warning(const char *s){
	fprintf(stderr, "Warning: %s\n",s);
}

void error(const char *s){
	print_stack();
	fprintf(stderr, "Error: %s\n",s);
	exit(1);
}

void yyerror (char const *s){
	error(s);
}
