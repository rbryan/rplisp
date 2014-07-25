#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

extern int yyparse();

int main(int argc, char **argv){
	yyparse();
	return 0;
}
