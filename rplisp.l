%{
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "rplisp.tab.h"

%}


%%

(>>)			{return close_chevron;}
(<<)			{return open_chevron;}
(\()			{return open_paren;}
(\))			{return close_paren;}

[+-]?[0-9]*(\.)[0-9]+	{sscanf(yytext,"%lf",&yylval.doub); return float_val;}
[+-]?[0-9]+		{sscanf(yytext,"%d",&yylval.integer); return int_val;}
[a-zA-Z_\-\*\/\+]+[a-zA-Z0-9_]*	{	
				yylval.id = malloc(yyleng+1);
				if(yylval.id == NULL)
					yyerror("Out of memory.");
				strncpy(yylval.id,yytext,yyleng);
				return identifier;
			}
\"[^\"]*\"		{	
				yylval.id = malloc(yyleng-1);
				if(yylval.id == NULL)
					yyerror("Out of memory.");
				strncpy(yylval.id,yytext+1,yyleng-2);
				yylval.id[yyleng-1] = '\0';
				return string;
			}
[ \t\n]			{;}
.			{ECHO; yyerror("unexpected character");}

%%
int yywrap (void) {return 1;}
