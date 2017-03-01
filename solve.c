#include "ac.h"
#include <stdio.h>
#include <stdlib.h>
#define complex struct complex
#include <math.h>


stack **adjlist;
complex** matrix;
complex* values;
complex** voltage_soln; //array of freq_arr_len X num_nets containing voltage of net at frequency of source
double* freq_arr;
complex* answer; //array containig soln of matrix
int freq_arr_len;

int *sources; //maps 0,1,2... to indices of sources in list array
int *index_cur_src; //maps index of current through voltage_sources in list array to index in matrix

struct source_data parse_source(char* str)
{
	struct source_data data;
	sscanf(str," ( %lf %lf %lf %lf",&data.dcoff,&data.ampl,&data.freq,&data.phase);
	return data;
}

void make_adjlist()
{
	sources = (int*)calloc(numsources,sizeof(int));
	index_cur_src = (int*)calloc(numcmp,sizeof(int));
	adjlist = (stack**)calloc(numnets,sizeof(stack*));
	freq_arr = (double*)calloc(numsources,sizeof(double));

	int i=0;
	int j=0,l=0;
	int k=numnets;
	for(i=0;i<numcmp;i++)
	{
		adjlist[list[i].id1] = push(adjlist[list[i].id1],i);
		adjlist[list[i].id2] = push(adjlist[list[i].id2],i);
		
		if(list[i].type==voltage || list[i].type==current)
		{
			double freq = list[i].freq;
			
			for(l=0;l<freq_arr_len;l++)
			{
				if(freq_arr[l]==freq)
				{
					break;
				}
			}
			if(l==freq_arr_len)
			{
				freq_arr[l] = freq;
				freq_arr_len++;
			}
			
			if(list[i].type==voltage)
			{
				index_cur_src[i] = k++;
			}
			sources[j++] = i;
		}
	}
}

void make_matrix(double cur_freq)
{
	//current_variables of voltage sources are 
	
	int cur_src_done = 0;
	matrix = (complex**)calloc((numnets+numvoltage),sizeof(complex*));
	values = (complex*)calloc((numnets+numvoltage),sizeof(complex));
	int eqn = 0;

	//V_net0 = 0

	matrix[eqn] = (complex*)calloc((numnets+numvoltage),sizeof(complex));
	matrix[eqn++][numnets-1] = make_complex(1,0);//1;  


	int i=0,j=0;
	//V1 - V2 = V eqns
	for(i=0;i<numsources;i++)
	{
		if(list[sources[i]].type==voltage)
		{
/*
			matrix[eqn] = (complex*)calloc(sizeof(complex)*(numnets+numvoltage));
			if(list[sources[i]].freq == cur_freq)
			{
				matrix[eqn][list[sources[i]].id1] = make_complex(-1,0);
				matrix[eqn][list[sources[i]].id2] = make_complex(1,0);
				values[eqn++] = make_complex(1,0);//TODO put value here
------------------------------CHECK--------------------------------------------
*/

			matrix[eqn] = (complex*)calloc((numnets+numvoltage),sizeof(complex));
			struct source_data data = parse_source(list[sources[i]].val);

			if(data.freq == cur_freq)
			{
				matrix[eqn][list[sources[i]].id1] = make_complex(-1,0);
				matrix[eqn][list[sources[i]].id2] = make_complex(1,0);
				values[eqn++] = make_complex(sqrt(2)*data.ampl,0);

			}
			else
			{
				matrix[eqn][list[sources[i]].id1] = make_complex(-1,0);
				matrix[eqn][list[sources[i]].id2] = make_complex(1,0);
				values[eqn++] = make_complex(0,0);
			}
		}
	}


	i=0;
	j=0;
	for(i=0;i<numnets-1;i++)
	{
		list* temp = adjlist[i];
		int id;
		while(temp!=NULL)
		{
			id = temp->id;
			if(list[id].type==voltage)
			{
				if(list[id].id1 == i)
				{
					//current outgoing from id1
					matrix[eqn][index_cur_src[id]] = make_complex(1,0);
				}
				else
				{
					//current incoming to id1
					matrix[eqn][index_cur_src[id]] = make_complex(-1,0);
				}

			}
			else if(list[id].type==current && list[id].freq == cur_freq)
			{
				//if current starts from here
/*
				if(list[id].id1 == i)
				{
					values[eqn] = add(values[eqn],make_complex(-1,0));//TODO: put value here
				}
				else
				{
					values[eqn] = add(values[eqn],make_complex(1,0));//TODO: put value here
--------------------CHECK--------------------
*/
				struct source_data data = parse_source(list[id].val);
				if(list[id].id1 == i)
				{
					values[eqn] = add(values[eqn],make_complex(-1*sqrt(2)*data.ampl,0));//TODO: put value here
				}
				else
				{
					values[eqn] = add(values[eqn],make_complex(sqrt(2)*data.ampl,0));//TODO: put value here
				}
			}
			else
			{
				complex inductance = get_inverse(get_inductance(id));	
				int other_net = (list[id].id1==i)?(list[id].id2):(list[id].id1);
				matrix[i][i] = sub(matrix[i][i],inductance);
				matrix[i][other_net] = add(matrix[i][other_net],inductance);
			}
			temp = temp->next;
		}
		eqn++;
	}
}



void free_matrix_values()
{
	int i=0;
	for(i=0;i<numnets-1;i++)
	{
		free(matrix[i]);
	}
	free(matrix);
	free(values);
}

void free_list_sources()
{
	free(sources);
	int i=0;
	list * temp;
	for(i=0;i<numnets;i++)
	{
		while(adjlist[i]!=NULL)
		{
			temp = adjlist[i]->next;
			free(adjlist[i]);
			adjlist[i] = temp;
		}
	}
	free(adjlist);
}

void solve_circuit()
{
	make_adjlist();
	voltage_soln = (complex**)calloc(freq_arr_len,sizeof(complex*));
	int i=0,j=0;
	for(i=0;i<freq_arr_len;i++)
	{
		voltage_soln[i] = (complex*)calloc(numnets,sizeof(complex));
		make_matrix(freq_arr[i]);
		solve_matrix();
		for(j=0;j<numnets;j++)
		{
			voltage_soln[i][j] = answer[j];
		}
	}
	free_list_sources();
	free_matrix_values();
}


