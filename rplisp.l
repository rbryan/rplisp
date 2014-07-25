%{
#include <stdio.h>
#include <stdlib.h>
#include "rplisp.tab.h"

extern void yyerror( const char *);
%}


%%

\<\<			{return open_chevron;}
>>			{return close_chevron;}
[+-]?[0-9]*(\.)[0-9]+	{sscanf(yytext,"%lf",&yylval.doub); return float_val;}
[+-]?[0-9]+		{sscanf(yytext,"%d",&yylval.integer); return int_val;}
[a-zA-Z_]+[a-zA-Z0-9_]*	{	yylval.id = malloc(yyleng);
				if(yylval.id == NULL)
					yyerror("Out of memory.");
				strncpy(yylval.id,yytext,yyleng);
				return identifier;}
[ \t\n]			{;}
.			{ECHO; yyerror("unexpected character");}

%%
int yywrap (void) {return 1;}
