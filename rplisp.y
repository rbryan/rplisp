%{

	#include <stdio.h>
	#include <stdlib.h>	

	extern int yylineno;
	extern int yyleng;
	extern char* yytext;

	extern int yylex();

	int noerror=1;

	void push_int(int num);
	void push_float(double num);
	void call(char *id, int len);

	int usp=0;
	int vsp=0;
	double stack[100];
	void yyerror (char const *s);
	

%}

%union{
	double doub; char *id; int integer;	
}

%start program

%token <doub> float_val
%token <integer> int_val
%token <id> identifier
%token <integer> open_chevron close_chevron
%type <integer> program number

%%



program : number program			{;}
     | identifier program			{call($1,yyleng);}
     | sexp program				{;}
     | sexp					{;}
     | identifier				{call($1,yyleng);}
     | number					{;}
     ;

number : float_val					{push_float($1);}
       | int_val					{push_int($1);}
	;
sexp : open_chevron program close_chevron		{;}


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

void yyerror (char const *s){
	fprintf(stderr, "Error: %s\n",s);
}



