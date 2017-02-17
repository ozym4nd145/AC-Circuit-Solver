%{
#include "ac.h"
void test_print();
extern FILE *yyin;
void yyerror (char *s);
%}

%union {int n1;char * s;}         
%token sine
%token alnum
%token er
%token space
%token new_line
%token <s> COMPONENT TERMINAL RESISTANCE CAPACITANCE INDUCTANCE SINE SOURCEDATA END VSOURCE ISOURCE
%start Input
%%

Input: Line  
	| Line Input 
	| er		{;} 	
;

Line:
     Expression END { printf("END OF LINE1\n"); }
     |END	      { printf("END OF LINE2\n"); }
;

Expression:
COMPONENT TERMINAL TERMINAL RESISTANCE 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=0;++numcmp;printf("matchedr\n");}
| COMPONENT TERMINAL TERMINAL INDUCTANCE 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=1;++numcmp;printf("matchedl\n");}
| COMPONENT TERMINAL TERMINAL CAPACITANCE 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=2;++numcmp;printf("matchedc\n");}
| VSOURCE TERMINAL TERMINAL SINE SOURCEDATA 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($5);list[numcmp].type=3;++numcmp;printf("matchedv\n");}
| ISOURCE TERMINAL TERMINAL SINE SOURCEDATA 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($5);list[numcmp].type=4;++numcmp;printf("matchedi\n");}
;

%%                    


int accept(char * s)
{
int i,f=0;
for(i=0;i<numnets;++i)
{
if(strcmp(s,arr[i])==0)
{f=1;return i;}
}

if(f==0)
{arr[numnets]=s;++numnets;
return numnets-1;}
}


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
}

int main() //TODO take file names from command line
{
numcmp=numnets=0;


yyin = fopen("top.cir","r");
if(yyin==NULL)
{yyerror("Input file not found\n");exit(1);}


//change to keep parsing multiple times because we just want to ignore the wrong line
    do {
        yyparse();
    } while (!feof(yyin));


outfile = fopen("top.svg","w");
if(outfile==NULL)
{yyerror("Output file not found\n");exit(1);}

//start of svg file
fprintf(outfile,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
fprintf(outfile,"<svg    xmlns:svg=\"http://www.w3.org/2000/svg\"\n  xmlns=\"http://www.w3.org/2000/svg\"\n  height=\"500\" width=\"500\" version=\"1.0\" style=\"background: white\">\n");


int incrementor=60;

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
//print_info(x,a,x,a+incrementor,list[i]);

make_line(x,a+incrementor,x,b);


if(x<start[net1])
{start[net1]=x;}
if(x<start[net2])
{start[net2]=x;}
if(x>end[net1])
{end[net1]=x;}
if(x>end[net2])
{end[net2]=x;}

x+=incrementor;
}

for(i=0;i<numnets;++i)
{make_line(start[i],y_coordinate[i],end[i],y_coordinate[i]);}

fprintf(outfile,"</svg>\n");//end of svg file

return 0; 
}

void test_print()
{
printf("%d\n",numcmp);
printf("%d\n",numnets);

int i;
for(i=0;i<numcmp;++i)
{printf("list[%d].type=%d list[%d].id1=%d list[%d].id2=%d list[%d].name=%s list[%d].val=%s\n",i,list[i].type,i,list[i].id1,i,list[i].id2,i,list[i].name,i,list[i].val);}

for(i=0;i<numnets;++i)
{printf("arr[%d]=%s \n",i,arr[i]);}

}

//print error but don't exit
void yyerror (char * s) 
{

if(strcmp(s,"syntax error")==0){printf ("Format of input file is wrong\n");}
else{printf ("%s\n",s);}
return;
}


