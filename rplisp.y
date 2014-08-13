%{

	#include <stdio.h>
	#include <stdlib.h>
	#include "stack.h"
	#include "atom.h"
	#include "error.h"

	extern int yylineno;
	extern int yyleng;
	extern char* yytext;

	extern int yylex();

	int noerror=1;

	void push_int(int num);
	void push_float(double num);
	void push_string(char * s);
	void call(char *id, int len);

	

%}

%union{
	double doub; char *id; int integer;	
}

%start sexp



%token <doub> float_val
%token <integer> int_val
%token <id> identifier
%token <id> string
%token <integer> open_chevron close_chevron
%type <integer> program number sexp

%%


sexp : open_chevron program close_chevron		{;}
     | open_chevron close_chevron			{;}
	;

program : program number			{;}
     | program identifier			{call($2,yyleng);}
     | program sexp				{;}
     | program string				{push_string($2);}
     | sexp					{;}
     | identifier				{call($1,yyleng);}
     | number					{;}
     | string					{push_string($1);}
     ;

number : float_val					{push_float($1);}
       | int_val					{push_int($1);}
	;


%%

void push_start(){
	struct atom *new;
	
	printf("Pushing start\n");

	new = new_atom();

	new->type = START;
	new->data.jump_t = NULL; //set when the corresponding end is pushed
	
	v_push_atom(new);

	print_stack();
	return;
}

void push_float(double n){
	struct atom *new;
	
	printf("Pushing float:\t%f\n",n);
	
	new = new_atom();

	new->type = FLOAT;
	new->data.float_t = n;

	v_push_atom(new);
	
	print_stack();
	return;
}

void push_int(int n){
	struct atom *new;

	printf("Pushing int:\t%d\n",n);

	new = new_atom();

	new->type = INT;
	new->data.integer_t = n;

	v_push_atom(new);
	print_stack();
	return;
}

void push_string(char * s){
	struct atom *new;
	
	printf("Pushing string:\t%s\n",s);

	new = new_atom();

	new->type = STRING;
	new->data.string_t = s;

	v_push_atom(new);
	print_stack();
	return;
}

void call(char *id, int len){
	printf("%s\n",id);
	return;
}




