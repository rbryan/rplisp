%{

	#include <stdio.h>
	#include <stdlib.h>
	#include "error.h"

	extern int yylineno;
	extern int yyleng;
	extern char* yytext;

	extern int yylex();

	int noerror=1;

	void push_int(int num);
	void push_float(double num);
	void call(char *id, int len);

	

%}

%union{
	double doub; char *id; int integer;	
}

%start sexp



%token <doub> float_val
%token <integer> int_val
%token <id> identifier
%token <integer> open_chevron close_chevron
%type <integer> program number sexp

%%


sexp : open_chevron program close_chevron		{;}
     | open_chevron close_chevron			{;}
	;

program : program number			{;}
     | program identifier			{call($2,yyleng);}
     | program sexp				{;}
     | sexp					{;}
     | identifier				{call($1,yyleng);}
     | number					{;}
     ;

number : float_val					{push_float($1);}
       | int_val					{push_int($1);}
	;


%%

void push_float(double n){
	printf("%f\n",n);
	return;
}
void push_int(int n){
	printf("%d\n",n);
	return;
}

void call(char *id, int len){
	printf("%s\n",id);
	return;
}




