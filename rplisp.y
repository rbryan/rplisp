%{

	#include <stdio.h>
	#include <stdlib.h>
	#include "stack.h"
	#include "atom.h"
	#include "symbols.h"
	
	#include "error.h"

	extern int yylineno;
	extern int yyleng;
	extern char* yytext;

	extern int yylex();

	//int noerror=1;

	void handle_quote_start();
	void handle_ident(char *id);

	

%}

%union{
	double doub; char *id; int integer;	
}

%start sexp



%token <doub> float_val
%token <integer> int_val open_chevron close_chevron open_paren close_paren
%token <id> identifier
%token <id> string
%type <integer> program sexp number group_open group_close

%%


sexp 	: group_open program group_close	{;}
      	| group_open group_close		{;}
	;

group_open: open_chevron			{handle_quote_start();}
	| open_paren				{push_start();}
	;

group_close: close_chevron			{push_term();}
	| close_paren				{push_term();}
	;

program : program number			{;}
	| program identifier			{handle_ident($2);}
	| program sexp				{;}
	| program string			{push_string($2);}
	| sexp					{;}
	| identifier				{handle_ident($1);}
	| number				{;}
	| string				{push_string($1);}
	;

number	: int_val				{push_int($1);}
	| float_val				{push_float($1);}
	;

%%

void handle_quote_start(){
	push_start();
	//We expect that the statement to be called will follow.
	//vsp-1 should be the location following the ref.
	//this location should hold an exit which will be eaten
	//when execute is called.
	push_ref(vsp - 1); 
	push_exit();
}

void handle_ident(char *id){
	struct symbol *sym;
	
	sym = search_symbol_table(id);
	
	if(sym)
		push_jump(sym->sl);
	else
		push_ident(id);
	
	return;
}

