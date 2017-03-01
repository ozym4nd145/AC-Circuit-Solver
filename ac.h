#ifndef AC_H
#define AC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define inf 1000000000

FILE *outfile;

enum component_type {resistor, inductor, capacitor, voltage, current};
struct component{
	int id1,id2;
	char * name;
	char * val;
	enum component_type type;
} list[20005];//list of all components


int numcmp;//number of components
int numnets;//number of nets
int numsouces;
int numvoltage;

/*--------starting and ending pixels of each net---------*/
int times[20005];
int start[20005];
int end[20005];
char * arr[20005]; //arr[id] stores netlist name corresponding to the id 

struct complex{
double real;
double img;
} a[2005][2005],constants[20005],result[20005];

struct complex ao[2005][2005];
//a*result=constants

/*-------x is horizontal, y is vertical------*/

void yyerror(char  * s);
int accept(char * s);
int check(int i);
int check_name_error(char*);
void invert();
void gaussian(int index[]);
struct complex add(struct complex a,struct complex b);
struct complex sub(struct complex a,struct complex b);
struct complex mult(struct complex a,struct complex b);
struct complex div_(struct complex a,struct complex b);
#endif
