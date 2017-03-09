#include "ac.h"
#include <stdlib.h>
#include "helper_functions.h"
#include <math.h>

const double PIE = 3.1415926536;
const double EPSILON = 1e-16;
//TODO PARSE UNITS ALSO


struct source_data parse_source(char* str)
{
	struct source_data data;
	char unit_freq[5];unit_freq[0]='\0';
	char unit_phase[5];unit_phase[0]='\0';
	
	char dc[100],amp[100],freq[100],phase[100];
	char udc[100],uamp[100],ufreq[100],uphase[100];
	
	//printf("string = \"%s\"\n",str);
	sscanf(str," ( %s %s %s %s )",dc,amp,freq,phase);
	//	printf(" ( %s * %s * %s * %s ) \n",dc,amp,freq,phase);


	int i,j,temp;	
	//dc
	temp=strlen(dc);
	for(i=0;i<temp;++i)
	{
		if(('a'<=dc[i] && dc[i]<='z')||('A'<=dc[i] && dc[i]<='Z'))
		{break;}
	}
	for(j=i;j<temp;++j)
	{dc[j]=toupper(dc[j]);
	 udc[j-i]=dc[j];}
	udc[temp-i]='\0';

	sscanf(dc,"%lf",&data.dcoff);
	//	printf("*%s*\n",udc);
			if(strcmp(udc,"K")==0)
			{
				data.dcoff = 1000*data.dcoff;
			}
			else if(strcmp(udc,"MEG")==0)
			{
				data.dcoff = 1000000*data.dcoff;
			}
			else if(strcmp(udc,"F")==0)
			{
				data.dcoff = data.dcoff/1000000000000000L;
			}
			else if(strcmp(udc,"P")==0)
			{
				data.dcoff = data.dcoff/1000000000000L;
			}
			else if(strcmp(udc,"N")==0)
			{
				data.dcoff = data.dcoff/1000000000;
			}
			else if(strcmp(udc,"U")==0)
			{
				data.dcoff = data.dcoff/1000000;
			}
			else if(strcmp(udc,"M")==0)
			{
				data.dcoff = data.dcoff/1000;
			}
			else if(strcmp(udc,"")==0)
			{
				data.dcoff = data.dcoff;
			}
			else
			{fprintf(stderr,"Invalid unit for dc offset\n");}

	//amp
		temp=strlen(amp);
	for(i=0;i<temp;++i)
	{
		if(('a'<=amp[i] && amp[i]<='z')||('A'<=amp[i] && amp[i]<='Z'))
		{break;}
	}
	for(j=i;j<temp;++j)
	{amp[j]=toupper(amp[j]);
	 uamp[j-i]=amp[j];}
	uamp[temp-i]='\0';
	//	printf("*%s*\n",uamp);
	
	sscanf(amp,"%lf",&data.ampl);
	
			if(strcmp(uamp,"K")==0)
			{
				data.ampl = 1000*data.ampl;
			}
			else if(strcmp(uamp,"MEG")==0)
			{
				data.ampl = 1000000*data.ampl;
			}
			else if(strcmp(uamp,"F")==0)
			{
				data.ampl = data.ampl/1000000000000000L;
			}
			else if(strcmp(uamp,"P")==0)
			{
				data.ampl = data.ampl/1000000000000L;
			}
			else if(strcmp(uamp,"N")==0)
			{
				data.ampl = data.ampl/1000000000;
			}
			else if(strcmp(uamp,"U")==0)
			{
				data.ampl = data.ampl/1000000;
			}
			else if(strcmp(uamp,"M")==0)
			{
				data.ampl = data.ampl/1000;
			}
			else if(strcmp(uamp,"")==0)
			{
				data.ampl = data.ampl;
			}
			else
			{fprintf(stderr,"Invalid unit for amplitude\n");}

	//freq
		temp=strlen(freq);
	for(i=0;i<temp;++i)
	{
		if(('a'<=freq[i] && freq[i]<='z')||('A'<=freq[i] && freq[i]<='Z'))
		{break;}
	}
	for(j=i;j<temp;++j)
	{freq[j]=toupper(freq[j]);
	 ufreq[j-i]=freq[j];}
	ufreq[temp-i]='\0';

	sscanf(freq,"%lf",&data.freq);
	
			if(strcmp(ufreq,"KHZ")==0)
			{
				data.freq = 1000*data.freq;
			}
			else if(strcmp(ufreq,"MEGHZ")==0)
			{
				data.freq = 1000000*data.freq;
			}
			else if(strcmp(ufreq,"FHZ")==0)
			{
				data.freq = data.freq/1000000000000000L;
			}
			else if(strcmp(ufreq,"PHZ")==0)
			{
				data.freq = data.freq/1000000000000L;
			}
			else if(strcmp(ufreq,"NHZ")==0)
			{
				data.freq = data.freq/1000000000;
			}
			else if(strcmp(ufreq,"UHZ")==0)
			{
				data.freq = data.freq/1000000;
			}
			else if(strcmp(ufreq,"MHZ")==0)
			{
				data.freq = data.freq/1000;
			}
			else if(strcmp(ufreq,"HZ")==0)
			{
				data.freq = data.freq;
			}
			else
			{fprintf(stderr,"Invalid unit for frequency\n");}

	//phase
		temp=strlen(phase);
	for(i=0;i<temp;++i)
	{
		if(('a'<=phase[i] && phase[i]<='z')||('A'<=phase[i] && phase[i]<='Z'))
		{break;}
	}
	for(j=i;j<temp;++j)
	{phase[j]=toupper(phase[j]);
	 uphase[j-i]=phase[j];}
	uphase[temp-i]='\0';

	sscanf(phase,"%lf",&data.phase);
	
			if(strcmp(uphase,"KS")==0)
			{
				data.phase = 1000*data.phase;
			}
			else if(strcmp(uphase,"MEGS")==0)
			{
				data.phase = 1000000*data.phase;
			}
			else if(strcmp(uphase,"FS")==0)
			{
				data.phase = data.phase/1000000000000000L;
			}
			else if(strcmp(uphase,"PS")==0)
			{
				data.phase = data.phase/1000000000000L;
			}
			else if(strcmp(uphase,"NS")==0)
			{
				data.phase = data.phase/1000000000;
			}
			else if(strcmp(uphase,"US")==0)
			{
				data.phase = data.phase/1000000;
			}
			else if(strcmp(uphase,"MS")==0)
			{
				data.phase = data.phase/1000;
			}
			else if(strcmp(uphase,"S")==0)
			{
				data.phase = data.phase;
			}	
			else
			{fprintf(stderr,"Invalid unit for phase\n");}

  data.phase = -1*data.freq*2*data.phase*PIE;
	return data;
}

complex get_impedance(int id, double freq) {
  if (list[id].type == resistor) {
    double value;
    char unit[5];
    unit[0] = '\0';
    sscanf(list[id].val, " %lf %s", &value, unit);
    if (unit[0] != '\0') {
      char* tmp = unit;
      for (; *tmp; tmp++) {
        *tmp = toupper(*tmp);
      }
      if (strcmp(unit, "K") == 0) {
        value = 1000 * value;
      } else if (strcmp(unit, "MEG") == 0) {
        value = 1000000 * value;
      } else if (strcmp(unit, "F") == 0) {
        value = value / 1000000000000000L;
      } else if (strcmp(unit, "P") == 0) {
        value = value / 1000000000000L;
      } else if (strcmp(unit, "N") == 0) {
        value = value / 1000000000;
      } else if (strcmp(unit, "U") == 0) {
        value = value / 1000000;
      } else if (strcmp(unit, "M") == 0) {
        value = value / 1000;
      }
    }
    return make_complex(value, 0);
  }
  if (list[id].type == capacitor) {
    double value;
    char unit[5];
    unit[0] = '\0';
    sscanf(list[id].val, " %lf %s", &value, unit);
    if (unit[0] != '\0') {
      char* tmp = unit;
      for (; *tmp; tmp++) {
        *tmp = toupper(*tmp);
      }
      if (strcmp(unit, "KF") == 0) {
        value = 1000 * value;
      } else if (strcmp(unit, "MEGF") == 0) {
        value = 1000000 * value;
      } else if (strcmp(unit, "FF") == 0) {
        value = value / 1000000000000000L;
      } else if (strcmp(unit, "PF") == 0) {
        value = value / 1000000000000L;
      } else if (strcmp(unit, "NF") == 0) {
        value = value / 1000000000;
      } else if (strcmp(unit, "UF") == 0) {
        value = value / 1000000;
      } else if (strcmp(unit, "MF") == 0) {
        value = value / 1000;
      }
    }
    return div_(make_complex(1, 0), make_complex(0, value * freq * 2 * PIE));
  }
  if (list[id].type == inductor) {
    double value;
    char unit[5];
    unit[0] = '\0';
    sscanf(list[id].val, " %lf %s", &value, unit);
    if (unit[0] != '\0') {
      char* tmp = unit;
      for (; *tmp; tmp++) {
        *tmp = toupper(*tmp);
      }
      if (strcmp(unit, "KH") == 0) {
        value = 1000 * value;
      } else if (strcmp(unit, "MEGH") == 0) {
        value = 1000000 * value;
      } else if (strcmp(unit, "FH") == 0) {
        value = value / 1000000000000000L;
      } else if (strcmp(unit, "PH") == 0) {
        value = value / 1000000000000L;
      } else if (strcmp(unit, "NH") == 0) {
        value = value / 1000000000;
      } else if (strcmp(unit, "UH") == 0) {
        value = value / 1000000;
      } else if (strcmp(unit, "MH") == 0) {
        value = value / 1000;
      }
    }
    return make_complex(0, freq * value * 2 * PIE);
  }
  return make_complex(0, 0);
}

void make_adjlist() {
  PRINT_DC = 0;
  sources = (int*)calloc(numsources, sizeof(int));
  parsed_source =
      (struct source_data*)calloc(numsources, sizeof(struct source_data));
  index_cur_src = (int*)calloc(numcmp, sizeof(int));
  adjlist = (stack**)calloc(numnets, sizeof(stack*));
  freq_arr = (double*)calloc(numsources, sizeof(double));
  map_source_list = (int*)calloc(numcmp, sizeof(int));

  int i = 0;
  int j = 0, l = 0;
  int k = numnets;
  int m = numnets+numvoltage; //used for mapping index of current through inductor to index in matrix in case of dc matrix
  for (i = 0; i < numcmp; i++) {
    adjlist[list[i].id1] = push(adjlist[list[i].id1], i);
    adjlist[list[i].id2] = push(adjlist[list[i].id2], i);

    if (list[i].type == voltage || list[i].type == current) {
      map_source_list[i] = j;
      parsed_source[j] = parse_source(list[i].val);
      if(parsed_source[j].dcoff !=0)
      {
        PRINT_DC=1;
      }
      double freq = parsed_source[j].freq;

      for (l = 0; l < freq_arr_len; l++) {
        if (freq_arr[l] == freq) {
          break;
        }
      }
      if (l == freq_arr_len) {
        freq_arr[l] = freq;
        freq_arr_len++;
      }

      if (list[i].type == voltage) {
        index_cur_src[i] = k++;
      }
      sources[j++] = i;
    }
    else if(list[i].type==inductor)
    {
      index_cur_src[i] = m++;
    }
  }
}


void make_matrix_dc() {
  // current_variables of voltage sources are
  matrix = (complex**)calloc((numnets + numvoltage+numinductor), sizeof(complex*));
  values = (complex*)calloc((numnets + numvoltage+numinductor), sizeof(complex));
  int eqn = 0;

  // V_net0 = 0

  matrix[eqn] = (complex*)calloc((numnets + numvoltage+numinductor), sizeof(complex));
  matrix[eqn++][numnets - 1] = make_complex(1, 0);
  // print_matrix(1);

  int i = 0, j = 0;
  // V1 - V2 = V eqns
  for (i = 0; i < numcmp; i++) {
    if (list[i].type == voltage) {
      matrix[eqn] = (complex*)calloc((numnets + numvoltage+numinductor), sizeof(complex));

      if (parsed_source[map_source_list[i]].dcoff != 0) {
        matrix[eqn][list[i].id1] = make_complex(1, 0);
        matrix[eqn][list[i].id2] = make_complex(-1, 0);
        values[eqn++] = make_complex(parsed_source[map_source_list[i]].dcoff, 0);

      } else {
        matrix[eqn][list[i].id1] = make_complex(-1, 0);
        matrix[eqn][list[i].id2] = make_complex(1, 0);
        values[eqn++] = make_complex(0, 0);
      }
    }
    else if(list[i].type==inductor)
    {
      matrix[eqn] = (complex*)calloc((numnets + numvoltage+numinductor), sizeof(complex));
      matrix[eqn][list[i].id1] = make_complex(-1, 0);
      matrix[eqn][list[i].id2] = make_complex(1, 0);
      values[eqn++] = make_complex(0, 0);
    }
  }
  // print_matrix(numvoltage+1);

  i = 0;
  j = 0;
  for (i = 0; i < numnets - 1; i++) {
    // printf("eqn - %d\n",eqn);
    matrix[eqn] = (complex*)calloc((numnets + numvoltage + numinductor), sizeof(complex));
    stack* temp = adjlist[i];
    int id;
    while (temp != NULL) {
      id = temp->id;

      struct source_data data = parsed_source[map_source_list[id]];

      if (list[id].type == voltage) {
        if (list[id].id1 == i) {
          // current outgoing from id1
          matrix[eqn][index_cur_src[id]] = make_complex(1, 0);
        } else {
          // current incoming to id1
          matrix[eqn][index_cur_src[id]] = make_complex(-1, 0);
        }

      } else if (list[id].type == current && data.dcoff != 0) {
        // if current starts from here
        if (list[id].id1 == i) {
          values[eqn] = add(values[eqn], make_complex(-1 *data.dcoff, 0));
        } else {
          values[eqn] = add(values[eqn], make_complex(data.dcoff, 0));
        }
      } else if (list[id].type == inductor) {
        if (list[id].id1 == i) {
          // current outgoing from id1
          matrix[eqn][index_cur_src[id]] = make_complex(1, 0);
        } else {
          // current incoming to id1
          matrix[eqn][index_cur_src[id]] = make_complex(-1, 0);
        }
      } else if (list[id].type == resistor) {
        complex impedance = div_(make_complex(1,0),get_impedance(id, 0));
        int other_net = (list[id].id1 == i) ? (list[id].id2) : (list[id].id1);
        matrix[eqn][i] = add(matrix[eqn][i], impedance);
        matrix[eqn][other_net] = sub(matrix[eqn][other_net], impedance);
      }
      temp = temp->next;
    }
    eqn++;
  }
}

void make_matrix(double cur_freq) {
  // current_variables of voltage sources are
  matrix = (complex**)calloc((numnets + numvoltage), sizeof(complex*));
  values = (complex*)calloc((numnets + numvoltage), sizeof(complex));
  int eqn = 0;

  // V_net0 = 0

  matrix[eqn] = (complex*)calloc((numnets + numvoltage), sizeof(complex));
  matrix[eqn++][numnets - 1] = make_complex(1, 0);
  // print_matrix(1);

  int i = 0, j = 0;
  // V1 - V2 = V eqns
  for (i = 0; i < numsources; i++) {
    if (list[sources[i]].type == voltage) {
      matrix[eqn] = (complex*)calloc((numnets + numvoltage), sizeof(complex));

      if (parsed_source[i].freq == cur_freq) {
        matrix[eqn][list[sources[i]].id1] = make_complex(1, 0);
        matrix[eqn][list[sources[i]].id2] = make_complex(-1, 0);
        values[eqn++] = make_complex(parsed_source[i].ampl*cos(parsed_source[i].phase),parsed_source[i].ampl*sin(parsed_source[i].phase));

      } else {
        matrix[eqn][list[sources[i]].id1] = make_complex(-1, 0);
        matrix[eqn][list[sources[i]].id2] = make_complex(1, 0);
        values[eqn++] = make_complex(0, 0);
      }
    }
  }
  // print_matrix(numvoltage+1);

  i = 0;
  j = 0;
  for (i = 0; i < numnets - 1; i++) {
    // printf("eqn - %d\n",eqn);
    matrix[eqn] = (complex*)calloc((numnets + numvoltage), sizeof(complex));
    stack* temp = adjlist[i];
    int id;
    while (temp != NULL) {
      id = temp->id;

      if (list[id].type == voltage) {
        if (list[id].id1 == i) {
          // current outgoing from id1
          matrix[eqn][index_cur_src[id]] = make_complex(1, 0);
        } else {
          // current incoming to id1
          matrix[eqn][index_cur_src[id]] = make_complex(-1, 0);
        }

      } else if (list[id].type == current &&
                 parsed_source[map_source_list[id]].freq == cur_freq) {
        // if current starts from here
        struct source_data data = parsed_source[map_source_list[id]];

        if (list[id].id1 == i) {
          values[eqn] =
              add(values[eqn],
                  make_complex(-1 * data.ampl*cos(data.phase),-1 *data.ampl*sin(data.phase)));  // TODO: put value here
        } else {
          values[eqn] = add(
              values[eqn], make_complex(data.ampl*cos(data.phase),data.ampl*sin(data.phase)));  // TODO: put value here
        }
      } else {
        complex inductance =
            div_(make_complex(1, 0), get_impedance(id, cur_freq));
        int other_net = (list[id].id1 == i) ? (list[id].id2) : (list[id].id1);
        matrix[eqn][i] = add(matrix[eqn][i], inductance);
        matrix[eqn][other_net] = sub(matrix[eqn][other_net], inductance);
      }
      temp = temp->next;
    }
    eqn++;
  }
}

double calc_angle(complex vec)
{
  double angle = (atan(vec.img / (vec.real + EPSILON)) * 180) / PIE;
  if(vec.real < 0 )
  {
    if(angle < 0)
    {
      angle += 180;
    }
    else
    {
      angle -= 180;
    }
  }
  return angle;
}

void print_soln(int print_dc) {
  int i = 0;
  int j = 0;
  if(print_dc)
  {
    fprintf(resultfile, "FREQ = 0.000Khz\n");
    fprintf(resultfile, "VOLTAGES\n");
    for (i = 0; i < numcmp; i++) {
      complex volt =
          sub(voltage_soln[freq_arr_len][list[i].id1], voltage_soln[freq_arr_len][list[i].id2]);
      fprintf(resultfile, "%s ", list[i].name);
      fprintf(resultfile, "%.3lf\n", volt.real);
    }
    fprintf(resultfile, "\nCURRENTS\n");
    for (i = 0; i < numcmp; i++) {
      complex curr;
      fprintf(resultfile, "%s ", list[i].name);
      if (list[i].type == voltage || list[i].type == inductor) {
        curr = voltage_soln[freq_arr_len][index_cur_src[i]];
      } else if (list[i].type == current && parsed_source[map_source_list[i]].dcoff != 0) {
        curr = make_complex(parsed_source[map_source_list[i]].dcoff,
                            0);
      } else if (list[i].type==resistor){
        curr = div_(
            sub(voltage_soln[freq_arr_len][list[i].id1], voltage_soln[freq_arr_len][list[i].id2]),
            (get_impedance(i, 0)));
      } else {
        curr = make_complex(0,0);
      }
      fprintf(resultfile, "%.3lf\n", curr.real);
    }
    fprintf(resultfile, "\n");
  }
  for (j = 0; j < freq_arr_len; j++) {
    fprintf(resultfile, "FREQ = %.3lfKhz\n", freq_arr[j]/1000);
    fprintf(resultfile, "VOLTAGES\n");
    for (i = 0; i < numcmp; i++) {
      complex volt =
          sub(voltage_soln[j][list[i].id1], voltage_soln[j][list[i].id2]);
      fprintf(resultfile, "%s ", list[i].name);
      fprintf(resultfile, "%.3lf ", abs_(volt));
      fprintf(resultfile, "%.3lf \n",calc_angle(volt));
    }
    fprintf(resultfile, "\nCURRENTS\n");
    for (i = 0; i < numcmp; i++) {
      complex curr;
      fprintf(resultfile, "%s ", list[i].name);
      if (list[i].type == voltage) {
        curr = voltage_soln[j][index_cur_src[i]];
      } else if (list[i].type == current) {
        curr = make_complex(parsed_source[map_source_list[i]].ampl,
                            0);
      } else {
        curr = div_(
            sub(voltage_soln[j][list[i].id1], voltage_soln[j][list[i].id2]),
            (get_impedance(i, freq_arr[j])));
      }
      fprintf(resultfile, "%.3lf ", abs_(curr));
      fprintf(resultfile, "%.3lf\n", calc_angle(curr));
    }
    fprintf(resultfile, "\n");
  }
}

void free_matrix_values() {
  int i = 0;
  for (i = 0; i < numnets - 1; i++) {
    free(matrix[i]);
  }
  free(matrix);
  free(values);
}

void free_list_sources() {
  free(sources);
  int i = 0;
  stack* temp;
  for (i = 0; i < numnets; i++) {
    while (adjlist[i] != NULL) {
      temp = adjlist[i]->next;
      free(adjlist[i]);
      adjlist[i] = temp;
    }
  }
  free(adjlist);
}

void pass(int n) {
  int i, j;
  // printf("N = %d\n",n);
  a = (complex**)calloc((n + 10), sizeof(complex*));
  for (i = 0; i < n; ++i) {
    a[i] = (complex*)calloc((n + 10), sizeof(complex));
  }

  ao = (complex**)calloc((n + 10), sizeof(complex*));
  for (i = 0; i < n; ++i) {
    ao[i] = (complex*)calloc((n + 10), sizeof(complex));
  }


  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      a[i][j].real = matrix[i][j].real;
      a[i][j].img = matrix[i][j].img;
      ao[i][j].real = matrix[i][j].real;
      ao[i][j].img = matrix[i][j].img;
    }
  }
}

void solve_circuit() {
  // i=-2;j=-2;
  make_adjlist();
  voltage_soln = (complex**)calloc((freq_arr_len+ 1 + 10), sizeof(complex*));
  // i=-1;j=-1;
  // printf("numsources - %d\nnumvoltage - %d\nnumnets - %d\nfreq_len - %d\n",
         // numsources, numvoltage, numnets, freq_arr_len);
  int i = 0, j = 0;
  qsort(freq_arr,freq_arr_len,sizeof(double),comparator_double);
  for (i = 0; i < freq_arr_len; i++) {
    // printf("Freq - %lf\n", freq_arr[i]);
    voltage_soln[i] =
        (complex*)calloc((numnets + 10 + numvoltage), sizeof(complex));
    make_matrix(freq_arr[i]);
    // print_matrix(0);
    pass((numnets+numvoltage));
    n = (numvoltage+numnets);
    solve_matrix();
    //test();
    for (j = 0; j < (numnets + numvoltage); j++) {
      // printf("Answer - %.10lf + %.10lf i\n",answer[j].real,answer[j].img);
      voltage_soln[i][j] = answer[j];
    }
    free_matrix_values();
  }


  if(PRINT_DC)//some condition to check whether to print dc offset results
  {
    voltage_soln[freq_arr_len] = (complex*)calloc((numnets + 10 + numvoltage + numinductor), sizeof(complex));
    make_matrix_dc();
    pass((numnets+numvoltage+numinductor));
    n = (numnets+numvoltage+numinductor);
    solve_matrix();
    for (j = 0; j < (numnets + numvoltage+numinductor); j++) {
      // printf("Answer - %.10lf + %.10lf i\n",answer[j].real,answer[j].img);
      voltage_soln[freq_arr_len][j] = answer[j];
    }
    free_matrix_values();
    free_list_sources();
  }

  print_soln(PRINT_DC);
  fclose(resultfile);
}
