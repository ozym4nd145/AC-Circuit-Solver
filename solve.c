#include "ac.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "helper_functions.h"


const double PIE = 3.1415926536;
const double EPSILON = 1e-16;
//TODO PARSE UNITS ALSO
struct source_data parse_source(char* str)
{
	struct source_data data;
	char unit_freq[5];unit_freq[0]='\0';
	char unit_phase[5];unit_phase[0]='\0';
	sscanf(str," ( %lf %lf %lf %s %lf %s",&data.dcoff,&data.ampl,&data.freq,unit_freq,&data.phase,unit_phase);
	return data;
}



// complex get_inductance(int id,double freq)
// {
// 	return make_complex(0,0);
// }
complex get_inductance(int id,double freq)
{
	if(list[id].type == resistor)
	{
		double value;
		char unit[5];
		unit[0] = '\0';
		sscanf(list[id].val," %lf %s",&value,unit);
		if(unit[0]!='\0')
		{
			char *tmp = unit;
			for(;*tmp;tmp++)
			{
				*tmp = toupper(*tmp);
			}
			if(strcmp(unit,"K")==0)
			{
				value = 1000*value;
			}
			else if(strcmp(unit,"MEG")==0)
			{
				value = 1000000*value;
			}
			else if(strcmp(unit,"F")==0)
			{
				value = value/1000000000000000L;
			}
			else if(strcmp(unit,"P")==0)
			{
				value = value/1000000000000L;
			}
			else if(strcmp(unit,"N")==0)
			{
				value = value/1000000000;
			}
			else if(strcmp(unit,"U")==0)
			{
				value = value/1000000;
			}
			else if(strcmp(unit,"M")==0)
			{
				value = value/1000;
			}
		}
		return make_complex(value,0);
	}
	if(list[id].type == capacitor)
	{
		double value;
		char unit[5];
		unit[0] = '\0';
		sscanf(list[id].val," %lf %s",&value,unit);
		if(unit[0]!='\0')
		{
			char *tmp = unit;
			for(;*tmp;tmp++)
			{
				*tmp = toupper(*tmp);
			}
			if(strcmp(unit,"KF")==0)
			{
				value = 1000*value;
			}
			else if(strcmp(unit,"MEGF")==0)
			{
				value = 1000000*value;
			}
			else if(strcmp(unit,"FF")==0)
			{
				value = value/1000000000000000L;
			}
			else if(strcmp(unit,"PF")==0)
			{
				value = value/1000000000000L;
			}
			else if(strcmp(unit,"NF")==0)
			{
				value = value/1000000000;
			}
			else if(strcmp(unit,"UF")==0)
			{
				value = value/1000000;
			}
			else if(strcmp(unit,"MF")==0)
			{
				value = value/1000;
			}
		}
		return div_(make_complex(1,0),make_complex(0,value*freq*2*PIE));
	}
	if(list[id].type == inductor)
	{
		double value;
		char unit[5];
		unit[0] = '\0';
		sscanf(list[id].val," %lf %s",&value,unit);
		if(unit[0]!='\0')
		{
			char *tmp = unit;
			for(;*tmp;tmp++)
			{
				*tmp = toupper(*tmp);
			}
			if(strcmp(unit,"KH")==0)
			{
				value = 1000*value;
			}
			else if(strcmp(unit,"MEGH")==0)
			{
				value = 1000000*value;
			}
			else if(strcmp(unit,"FH")==0)
			{
				value = value/1000000000000000L;
			}
			else if(strcmp(unit,"PH")==0)
			{
				value = value/1000000000000L;
			}
			else if(strcmp(unit,"NH")==0)
			{
				value = value/1000000000;
			}
			else if(strcmp(unit,"UH")==0)
			{
				value = value/1000000;
			}
			else if(strcmp(unit,"MH")==0)
			{
				value = value/1000;
			}
		}
		return make_complex(0,freq*value*2*PIE);
	}
	return make_complex(0,0);
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
			struct source_data data = parse_source(list[i].val);
			double freq = data.freq;
			
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
	matrix[eqn++][numnets-1] = make_complex(1,0);//WRONG
	// print_matrix(1);

	int i=0,j=0;
	//V1 - V2 = V eqns
	for(i=0;i<numsources;i++)
	{
		if(list[sources[i]].type==voltage)
		{

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
	// print_matrix(numvoltage+1);


	i=0;
	j=0;
	for(i=0;i<numnets-1;i++)
	{
		// printf("eqn - %d\n",eqn);
		matrix[eqn] = (complex*)calloc((numnets+numvoltage),sizeof(complex));
		stack* temp= adjlist[i];
		int id;
		while(temp!=NULL)
		{
			id = temp->id;

			struct source_data data = parse_source(list[id].val);

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
			else if(list[id].type==current && data.freq == cur_freq)
			{
				//if current starts from here
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
				complex inductance = div_(make_complex(1,0),get_inductance(id,cur_freq));	
				int other_net = (list[id].id1==i)?(list[id].id2):(list[id].id1);
				matrix[eqn][i] = sub(matrix[eqn][i],inductance);
				matrix[eqn][other_net] = add(matrix[eqn][other_net],inductance);
			}
			temp = temp->next;
		}
		eqn++;
	}
}

void print_soln()
{
	FILE* f=fopen("results.txt","w");
	if(f==NULL)
	{fprintf(stderr,"Error - Can't open results.txt\n");}

	int i=0;int j=0;
	for(j=0;j<freq_arr_len;j++)
	{
		fprintf(f,"FREQ = %lfHz\n",freq_arr[j]);
		fprintf(f,"VOLTAGES\n");
		for(i=0;i<numcmp;i++)
		{
			complex volt = sub(voltage_soln[j][list[i].id2],voltage_soln[j][list[i].id1]);
			fprintf(f,"%s ",list[i].name);
			fprintf(f,"%lf ",abs_(volt)/sqrt(2));
			fprintf(f,"%lf \n",(atan(volt.img/(volt.real+EPSILON))*180)/PIE);
		}
		fprintf(f,"\nCURRENTS\n");
		for(i=0;i<numcmp;i++)
		{
			complex curr;
			fprintf(f,"%s ",list[i].name);
			if(list[i].type==voltage)
			{
				curr = voltage_soln[j][index_cur_src[i]];
			}
			else if(list[i].type==current)
			{
				struct source_data data = parse_source(list[i].val);
				curr = make_complex(data.ampl*sqrt(2),0);//TODO: take into account the offset etc.
			}
			else
			{
				curr = div_(sub(voltage_soln[j][list[i].id2],voltage_soln[j][list[i].id1]),(get_inductance(i,freq_arr[j])));
			}
			fprintf(f,"%lf ",abs_(curr)/sqrt(2));
			fprintf(f,"%lf \n",(atan(curr.img/(curr.real+EPSILON))*180)/PIE);
		}
		fprintf(f,"\n");
	}
	fclose(f);
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
	stack * temp;
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

void pass()
{int i,j;
	n=numnets+numvoltage;

a = (complex**)calloc((n+10),sizeof(complex*));
for (i = 0; i < n; ++i) 
{a[i] = (complex*)calloc((n+10),sizeof(complex));}

	
	for(i=0;i<n;++i)
	{
		for(j=0;j<n;++j)
		{a[i][j].real=matrix[i][j].real;a[i][j].img=matrix[i][j].img;
		 ao[i][j].real=matrix[i][j].real;ao[i][j].img=matrix[i][j].img;}
	}
	// for(i=0;i<n;++i)
	// {
	// 	constants[i]=values[i];
	// }
}


void solve_circuit()
{
	//i=-2;j=-2;
	make_adjlist();
	voltage_soln = (complex**)calloc((freq_arr_len+10),sizeof(complex*));
	//i=-1;j=-1;
	printf("numsources - %d\nnumvoltage - %d\nnumnets - %d\nfreq_len - %d\n",numsources,numvoltage,numnets,freq_arr_len);
	int i=0,j=0;	
	for(i=0;i<freq_arr_len;i++)
	{
		printf("Freq - %lf\n",freq_arr[i]);
		voltage_soln[i] = (complex*)calloc((numnets+10+numvoltage),sizeof(complex));
		make_matrix(freq_arr[i]);
		print_matrix(0);
		pass();
		solve_matrix();
		test();
		for(j=0;j<(numnets+numvoltage);j++)//-----------------CHECK------??-------------
		{
			voltage_soln[i][j] = answer[j];
		}
		free_matrix_values();
	}
	free_list_sources();
	print_soln();
}

