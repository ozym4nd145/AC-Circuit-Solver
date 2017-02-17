%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ac.h"
extern FILE *yyin;
FILE *outfile;
void yyerror (char *s);
%}

%union {int n1;}         
%start file
%token sine
%token alnum
%token number
%token space
%token new_line
%%

file 	: line file {;}
	|line	{;}
	;
										// with units
line    :alnum alnum  alnum  number alnum new_line {printf("matched\n");}	//R1 Net2 Net1 1k
	|alnum number alnum  number alnum new_line {printf("matched2\n");}	//R1 0 Net1 1k
	|alnum alnum  number number alnum new_line {printf("matched3\n");}	//R1 Net1 0 1k
	|alnum alnum  alnum  number  new_line {printf("matched\n");}	// without units
	|alnum number alnum  number  new_line {printf("matched2\n");}
	|alnum alnum  number number  new_line {printf("matched3\n");}	
	|alnum alnum   alnum   sine '(' number  number  number alnum  number alnum  number ')' new_line {printf("matched4\n");}
	|alnum number  alnum   sine '(' number  number  number alnum  number alnum  number ')' new_line {printf("matched5\n");}
	|alnum alnum   number  sine '(' number  number  number alnum  number alnum  number ')' new_line {printf("matched6\n");}
	|alnum alnum   alnum   sine '(' number  number  number alnum  number alnum   ')' new_line {printf("matched4\n");}
	|alnum number  alnum   sine '(' number  number  number alnum  number alnum   ')' new_line {printf("matched5\n");}
	|alnum alnum   number  sine '(' number  number  number alnum  number alnum   ')' new_line {printf("matched6\n");}		
;

num_type : number 
%%                    

int main() 
{

yyin = fopen("top.cir","r");
if(yyin==NULL)
{yyerror("Input file not found\n");}


yyparse();
return 0; 
}

//print error but don't exit
void yyerror (char *s) 
{

if(strcmp(s,"syntax error")==0){printf ("Format of input file is wrong\n");}
else{fprintf (outfile, "%s\n", s);}

}


