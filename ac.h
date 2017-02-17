#ifndef AC_H
#define AC_H

#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>

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

/*--------starting and ending pixels of each net---------*/
int start[20005];
int end[20005];
int y_coordinate[20005];
char * arr[20005]; //arr[id] stores netlist name corresponding to the id 

/*-------x is horizontal, y is vertical------*/



void make_point(int ,int );
void make_line(int x1,int y1,int x2,int y2);
void yyerror(char  * s);
int accept(char * s);
#endif