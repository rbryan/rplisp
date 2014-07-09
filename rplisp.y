%{
	extern int yylineno;
	extern char* yytext[];
	int noerror=1;

	void push(double num);
	void call(char id);

	int sp;
	int bp;
	double ustack[100];
	double istack[100];
	

%}

%union{
	double num; char *id;	
}

%start program

%token <num> number
%token <id> identifier
%type <num> open_chevron close_chevron program

%%



program : number program			{push($1);}
     | identifier program			{call($1);}
     | sexp program				{;}
     | sexp					{;}
     | number					{push($1);}
     | identifier				{call($1);}
     ;

sexp : open_chevron program close_chevron		{;}


%%


