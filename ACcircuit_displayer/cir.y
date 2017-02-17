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

void inti()
{
arr[0]="Net3";start[0]=inf;end[0]=0;
arr[1]="Net9";start[1]=inf;end[1]=0;
arr[2]="Net2";start[2]=inf;end[2]=0;
arr[3]="Net1";start[3]=inf;end[3]=0;
arr[4]="0";start[4]=inf;end[4]=0;
arr[5]="Net4";start[5]=inf;end[5]=0;
arr[6]="Net5";start[6]=inf;end[6]=0;
arr[7]="Net8";start[7]=inf;end[7]=0;
arr[8]="Net6";start[8]=inf;end[8]=0;

list[0].type=resistor;list[0].id1=0;list[0].id2=1;
list[1].type=capacitor;list[1].id1=2;list[1].id2=0;
list[2].type=inductor;list[2].id1=3;list[2].id2=2;
list[3].type=voltage;list[3].id1=3;list[3].id2=4;
list[4].type=inductor;list[4].id1=1;list[4].id2=5;
list[5].type=capacitor;list[5].id1=5;list[5].id2=6;

numcmp=6;
numnets=7;

/* R2 Net5 Net8 10K 
 L3 Net8 Net6 10NH 
 C3 Net6 0 100NF 
 C4 Net4 0 1NF */
}

int main() //TODO take file names from command line
{
/*
yyin = fopen("top.cir","r");
if(yyin==NULL)
{yyerror("Input file not found\n");}

oufile = fopen("top.svg","w");
if(outfile==NULL)
{yyerror("Output file not found\n");}


//change to keep parsing multiple times because we just want to ignore the wrong line
yyparse();


*/
inti();

int incrementor=40;

int j;
for(j=0;j<numnets;++j)
{y_coordinate[j]=(j+1)*incrementor;}


int i,x=incrementor;
for(i=0;i<numcmp;++i)
{
int net1 = list[i].id1;
int net2 = list[i].id2;

make_point(x,y_coordinate[net1]);
make_point(x,y_coordinate[net2]);

int a=y_coordinate[net1];
int b=y_coordinate[net2];

if(a>b)
{int t=b;b=a;a=t;}
//a<=b

//make_element(x,a,x,a+incrementor,list[i].type);
make_line(x,a+incrementor,x,b);

if()
{}


x+=incrementor;
}

for(i=0;i<numnets;++i)
{
make_line(start[i],y_coordinate[i],end[i],y_coordinate[i]);

}

return 0; 
}


//print error but don't exit
void yyerror (char *s) 
{

if(strcmp(s,"syntax error")==0){printf ("Format of input file is wrong\n");}
else{fprintf (outfile, "%s\n", s);}

}


