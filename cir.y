%{
#include "ac.h"
#include "draw.h"
void test_print();
extern FILE *yyin;
void yyerror (char *s);
int yylex();
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
     Expression END { }
     |END	      { }
;

Expression:
COMPONENT TERMINAL TERMINAL RESISTANCE 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=0;++numcmp;}
| COMPONENT TERMINAL TERMINAL INDUCTANCE 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=1;++numcmp;}
| COMPONENT TERMINAL TERMINAL CAPACITANCE 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=2;++numcmp;}
| VSOURCE TERMINAL TERMINAL SINE SOURCEDATA 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($5);list[numcmp].type=3;++numcmp;}
| ISOURCE TERMINAL TERMINAL SINE SOURCEDATA 
{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($5);list[numcmp].type=4;++numcmp;}
;

%%                    

int accept(char * s) {
    int i, f = 0;
    for (i = 0; i < numnets; ++i) {
        if (strcmp(s, arr[i]) == 0) {
            f = 1;
            return i;
        }
    }

    if (f == 0) {
        arr[numnets] = strdup(s);
        ++numnets;
        return numnets - 1;
    }
}

int main(int argc, char* argv[]) //TODO take file names from command line
{
    if(argc != 3)
    {
        fprintf(stderr, "3 args required!\n");
        exit(-1);
    }
    numcmp = numnets = 0;

    /**
     * Initializing start to infinity
     */
    int i=0;
    for(i=0;i<20005;i++)
    {
        start[i] = inf;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        yyerror("Input file not found\n");
        exit(1);
    }

    //change to keep parsing multiple times because we just want to ignore the wrong line
    do {
        yyparse();
    } while (!feof(yyin));

    outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        yyerror("Output file not found\n");
        exit(1);
    }

    start_svg(numnets,numcmp,outfile);

    for (i = 0; i < numcmp; ++i) {
        int net1 = list[i].id1;
        int net2 = list[i].id2;

        if (net1 > net2) {
            int t = net2;
            net2 = net1;
            net1 = t;
        }
        
        make_element(i,net1,i,net2,list[i].type,list[i].name,outfile);
        
        
        if (i < start[net1]) {
            start[net1] = i;
        }
        if (i < start[net2]) {
            start[net2] = i;
        }
        if (i > end[net1]) {
            end[net1] = i;
        }
        if (i > end[net2]) {
            end[net2] = i;
        }

    }

    for (i = 0; i < numnets; ++i) {
        draw_line(start[i], i, end[i], i,outfile);
    }

    end_svg(outfile);

    return 0;
}

void test_print() {
    printf("%d\n", numcmp);
    printf("%d\n", numnets);

    int i;
    for (i = 0; i < numcmp; ++i) {
        printf("list[%d].type=%d list[%d].id1=%d list[%d].id2=%d list[%d].name=%s list[%d].val=%s\n", i, list[i].type, i, list[i].id1, i, list[i].id2, i, list[i].name, i, list[i].val);
    }

    for (i = 0; i < numnets; ++i) {
        printf("arr[%d]=%s \n", i, arr[i]);
    }

}

//print error but don't exit
void yyerror(char * s) {

    if (strcmp(s, "syntax error") == 0) {
        printf("Format of input file is wrong\n");
    } else {
        printf("%s\n", s);
    }
    return;
}

