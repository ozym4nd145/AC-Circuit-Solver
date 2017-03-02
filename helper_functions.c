#include <stdio.h>
#include "ac.h"
#include <stdlib.h>
#include "helper_functions.h"

void print_matrix(int rows)
{
	if(rows == 0)
	{
		rows = numnets+numvoltage;
	}
	int i=0,j=0;

	for(i=0;i<rows;i++)
	{
		for(j=0;j<(numnets+numvoltage);j++)
		{
			printf("%3.5lf %3.5lf | ",matrix[i][j].real,matrix[i][j].img);
		}
		printf("\n");
	}
	printf("-------------------------------\n");
}