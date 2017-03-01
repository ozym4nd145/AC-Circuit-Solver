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
;

Line: END	      {/*printf("Got only end\n");*/}
     | Expression {/*printf("Got only expression\n");*/}
;

Expression:
COMPONENT TERMINAL TERMINAL RESISTANCE END
	{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=0;if(check(numcmp)==1){++numcmp;}}
| COMPONENT TERMINAL TERMINAL INDUCTANCE END 
	{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=1;if(check(numcmp)==1){++numcmp;}}
| COMPONENT TERMINAL TERMINAL CAPACITANCE END
	{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($4);list[numcmp].type=2;if(check(numcmp)==1){++numcmp;}}
| VSOURCE TERMINAL TERMINAL SINE SOURCEDATA END
	{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($5);list[numcmp].type=3;if(check(numcmp)==1){++numcmp;}}
| ISOURCE TERMINAL TERMINAL SINE SOURCEDATA END
	{list[numcmp].name=strdup($1);list[numcmp].id1=accept($2);list[numcmp].id2=accept($3);list[numcmp].val=strdup($5);list[numcmp].type=4;if(check(numcmp)==1){++numcmp;}}
| VSOURCE TERMINAL TERMINAL SINE er {/*printf("Got and error\n");*/}
| ISOURCE TERMINAL TERMINAL SINE er {/*printf("Got and error\n");*/}
| COMPONENT TERMINAL TERMINAL er {/*printf("Got and error\n");*/}
| VSOURCE TERMINAL TERMINAL er {/*printf("Got and error\n");*/}
| ISOURCE TERMINAL TERMINAL er {/*printf("Got and error\n");*/}
| COMPONENT TERMINAL er {/*printf("Got and error\n");*/}
| VSOURCE TERMINAL er {/*printf("Got and error\n");*/}
| ISOURCE TERMINAL er {/*printf("Got and error\n");*/}
| COMPONENT er {/*printf("Got and error\n");*/}
| VSOURCE er {/*printf("Got and error\n");*/}
| ISOURCE er {/*printf("Got and error\n");*/}
| er {/*printf("Got and error\n");*/}
;

%%                    

int accept(char * s) {
    check_name_error(s);
    int i, f = 0;
    for (i = 0; i < numnets; ++i) {
        if (strcmp(s, arr[i]) == 0) {
            f = 1;
	        ++times[i];
            return i;
        }
    }

    if (f == 0) {
        arr[numnets] = strdup(s);
        ++numnets;
	    ++times[numnets - 1];
        return numnets - 1;
    }
}

int check(int i)
{
	if(list[i].id1==list[i].id2)
	{
        fprintf(stderr,"Error - both terminal nets of %s are same, it is ignored\n",list[i].name);
        return 0;
    }
	else
	{
        check_name_error(list[i].name);
        return 1;
    }
}

int check_name_error(char* name)
{
    int err_flag = 0;
    int i=0;
    int len = strlen(name);
    char* dup_name = strdup(name);
    for(i=0;i<len;i++)
    {
        if(!((name[i]>=48 && name[i]<=57)||(name[i]>=65 && name[i]<=90)||(name[i]>=97 && name[i] <= 122)||(name[i]==95)))
        {
            err_flag=1;
            name[i]=95;
        }
    }
    if(err_flag)
    {
        fprintf(stderr, "Error - Foreign characters found in name - %s. Replacing it with - %s\n",dup_name,name);
    }
    free(dup_name);
    return 0;
}
int swap_net(int idx1,int idx2)
{
    // printf("Swapping - %d = %s <=> %d = %s\n",idx1,arr[idx1],idx2,arr[idx2]);
    if(idx1==idx2)
    {
        return 1;
    }
    char* p = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = p;
    // printf("After %d = %s <=> %d = %s\n",idx1,arr[idx1],idx2,arr[idx2]);

    int i=0;
    for(i=0;i<numcmp;i++)
    {
        // printf("Edge - %s , t1 - %d, t2 - %d\n",list[i].name, list[i].id1,list[i].id2);
        if(list[i].id1 == idx1)
        {
            list[i].id1 = idx2;
        }
        else if(list[i].id1 == idx2)
        {
            list[i].id1 = idx1;
        }
        if(list[i].id2 == idx1)
        {
            list[i].id2 = idx2;
        }
        else if(list[i].id2 == idx2)
        {
            list[i].id2 = idx1;
        }
        // printf("Edge - %s , t1 - %d, t2 - %d\n",list[i].name, list[i].id1,list[i].id2);
    }

}

int check_ground()
{
    int i=0;
    int found = 0;
    for(i=0;i<numnets && found==0;i++)
    {
        if(!strcmp(arr[i],"0"))
        {
            found = 1;
            swap_net(i,numnets-1);
        }
    }
    return found;
}

int main(int argc, char* argv[]) //TODO take file names from command line
{
    if(argc != 3)
    {
        fprintf(stderr, "3 args required!\n");
        exit(-1);
    }
    numcmp = numnets = 0;

    //Initializing start to infinity    
    int i=0;
    for(i=0;i<20005;i++)
    {
		times[i] = 0;
        start[i] = inf;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stderr,"Error - Input file not found\n");
        exit(-1);
    }

    //change to keep parsing multiple times because we just want to ignore the wrong line
    do {
        yyparse();
    } while (!feof(yyin));

//	test_print();	//debug

    outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fprintf(stderr,"Error - Output file not found\n");
        exit(-1);
    }

 	for(i=0;i<numnets;++i)
 	{
 		
        if(times[i]==1)
 		{
            fprintf(stderr,"Error - Net: \"%s\" is connected to only one component\n",arr[i]);
        }
 	}

    int is_draw_ground = 0;

    if(!check_ground())
    {
        fprintf(stderr,"Error - No ground net found\n");
    }
    else
    {
        is_draw_ground = 1;
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
        
        char* print_text = (char *)malloc((strlen(list[i].name)+strlen(list[i].val)+10)*sizeof(char));
        strcpy(print_text,list[i].name);
        strcat(print_text," ");
        if(list[i].type == voltage || list[i].type == current)
        {
            strcat(print_text,"SINE ");
        }
        strcat(print_text,list[i].val);

        make_element(i,net1,i,net2,list[i].type,print_text,outfile);
        free(print_text);
        
        
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
    if(is_draw_ground)
    {
        draw_ground(end[numnets-1],numnets-1,outfile);
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
        fprintf(stderr,"Error - Format of input file is wrong\n");
    } else {
        fprintf(stderr,"%s\n", s);
    }

}

