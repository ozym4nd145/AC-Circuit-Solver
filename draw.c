#include "draw.h"
#include <stdio.h>
#include <assert.h>
#include "ac.h"

float LINE_WIDTH=0.05;
float CIRCLE_WIDTH=0.07;
float WIDTH = 2000;
float HEIGHT = 2000;

/**
 * Convention: parameters x and y in functions
 * X : -> Horizontal shift
 * Y : -> Vertical shift
 */

int start_svg(int rows, int cols, FILE* ptr)
{
	fprintf(ptr, "<svg width=\"%f\" height=\"%f\" viewBox=\"0 0 %d %d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" transform=\"translate(100 100)\">\n",WIDTH,HEIGHT,(cols+10),(rows+10));
}
int draw_line(int x1,int y1, int x2, int y2,FILE* ptr)
{
	if(x1==x2 && y1==y2) { return 0; }
	fprintf(ptr, "<line x1=\"%d\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke-width=\"%f\" stroke=\"black\"/>\n",x1,x2,y1,y2,LINE_WIDTH);
}
int draw_circle(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<circle cx=\"%d\" cy=\"%d\" r=\"%f\"/>\n",x,y,CIRCLE_WIDTH);
}
int end_svg(FILE* ptr)
{
	fprintf(ptr, "</svg>\n");
}

int draw_resistor(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_resistor(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

int draw_capacitor(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_capacitor(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

int draw_inductor(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_inductor(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

int draw_ac(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_ac(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

int draw_current(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_current(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

int draw_text(int x, int y, char* text, enum component_type type, FILE* ptr)
{
	switch(type)
	{
		case resistor:
			place_text(x,y,0.2,text,"red",ptr);
			break;
		case inductor:
			place_text(x,y,0.2,text,"green",ptr);
			break;
		case capacitor:
			place_text(x,y,0.33,text,"blue",ptr);
			break;
		case voltage:
			place_text(x,y,0.4,text,"brown",ptr);
			break;
		case current:
			place_text(x,y,0.4,text,"purple",ptr);
			break;
	}
}

int draw_net_text(int x, int y, int is_up,char* text, FILE* ptr)
{
	float off_y;
	if(is_up)
	{
		off_y = -1.5*CIRCLE_WIDTH;
	}
	else
	{
		off_y = 3.0*CIRCLE_WIDTH;
	}
	fprintf(ptr, "<text x = \"%f\" y=\"%f\" font-size=\"%f\" fill=\"black\">%s</text>\n",x-0.15,y+off_y,LINE_WIDTH*3,text);	
}

int place_text(int x,int y, float off_x,char* text, char* color, FILE* ptr)
{
	fprintf(ptr, "<text x = \"%f\" y=\"%f\" font-size=\"%f\" style=\"writing-mode: tb;\" fill=\"%s\">%s</text>\n",x+off_x,y+0.2,LINE_WIDTH*3,color,text);
}

int place_resistor(int x, int y, FILE* ptr)
{
	fprintf(ptr,"<path d=\" M 0 0 l 0.25 0 l 0.04166666667 -0.08333333334 l 0.08333333334 0.166666666667 l 0.08333333334 -0.166666666667 l 0.08333333334 0.166666666667 l 0.08333333334 -0.166666666667 l 0.08333333334 0.166666666667 l 0.04166666667 -0.08333333334 l 0.25 0 \" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"  transform=\"translate(%d %d) rotate(90)\"/>\n",LINE_WIDTH,x,y);
}

int place_capacitor(int x, int y, FILE* ptr)
{
	fprintf(ptr," \
	<g transform = \"translate(%d,%d)\"> \
		<path d=\" \
			M 0 0 \
			l 0 0.4 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M -0.25 0.4 \
			l 0.5 0 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M -0.25 0.6 \
			l 0.5 0 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M 0 0.6 \
			l 0 0.4 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
 	</g> \
 	",x,y,LINE_WIDTH,LINE_WIDTH,LINE_WIDTH,LINE_WIDTH);
}

int place_inductor(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<path \
		d=\" \
			M 0,0 \
			L 5.5,0 \
			C 5.5,0 5.5,-4 9.5,-4 \
			C 13.5,-4 13.5,0 13.5,0 \
			C 13.5,0 13.5,-4 17.5,-4 \
			C 21.5,-4 21.5,0 21.5,0 \
			C 21.5,0 21.5,-4 25.5,-4 \
			C 29.5,-4 29.5,0 29.5,0 \
			C 29.5,0 29.5,-4 33.5,-4 \
			C 37.5,-4 37.5,0 37.5,0 \
			L 43,0 \
		\" \
		stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"miter\" fill=\"none\" fill-rule=\"evenodd\" fill-opacity=\"0.75\" stroke-linecap=\"butt\" stroke-opacity=\"1\" transform=\"translate(%d,%d) scale(0.02325581395) rotate(90) \" />\n ",(43*LINE_WIDTH),x,y);
}

int place_ac(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<g transform=\"translate(%d,%d) scale(0.02125,0.022727272727272728)\"> <g transform=\"translate(-25.08161,-2.992383)\"> <path d=\"m 40,25 c 0,8.284271 -6.715729,15 -15,15 -8.284271,0 -15,-6.715729 -15,-15 0,-8.284271 6.715729,-15 15,-15 8.284271,0 15,6.715729 15,15 l 0,0 z\" style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:%f;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\"/> <path d=\"M 25,10 25,3\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25,40 0,7\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 16,25.000005 c 0,0 1.5,-5.000001 4.5,-5.000001 3,0 6,10.000002 9,10.000002 3,0 4.5,-5.000001 4.5,-5.000001\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> </g> </g>\n",x,y,(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH));
}

int place_current(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<g transform=\"translate(%d,%d) scale(0.02125,0.022727272727272728)\"> <g transform=\"translate(-25.08161,-2.992383)\"> <path d=\"m 40,25 c 0,8.284271 -6.715729,15 -15,15 -8.284271,0 -15,-6.715729 -15,-15 0,-8.284271 6.715729,-15 15,-15 8.284271,0 15,6.715729 15,15 l 0,0 z\" style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:%f;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\" /> <path d=\"M 25,10 25,3\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25,40 0,7\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25.136017,23.540261 0,11.951034\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path style=\"fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:1\" d=\"m 25.136017,18.552775 -3.210011,4.951033 6.63765,0.05441 z\"/> </g> </g>\n",x,y,(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH));
}

int make_element(int x1,int y1,int x2,int y2,enum component_type type,char* name,FILE* ptr)
{
	draw_text(x1,y1,name,type,ptr);
	switch(type)
	{
		case resistor:
			draw_resistor(x1,y1,x2,y2,ptr);
			break;
		case inductor:
			draw_inductor(x1,y1,x2,y2,ptr);
			break;
		case capacitor:
			draw_capacitor(x1,y1,x2,y2,ptr);
			break;
		case voltage:
			draw_ac(x1,y1,x2,y2,ptr);
			break;
		case current:
			draw_current(x1,y1,x2,y2,ptr);
			break;
	}
}

// int main()
// {
// 	FILE* fl = fopen("test_2.svg","w");
// 	start_svg(10,10,fl);
// 	draw_line(0,0,10,0,fl);
// 	draw_line(0,1,10,1,fl);
// 	draw_line(0,2,10,2,fl);
// 	draw_line(0,3,10,3,fl);
// 	draw_line(0,4,10,4,fl);
// 	draw_resistor(1,0,1,4,fl);
// 	draw_capacitor(3,2,3,4,fl);
// 	draw_inductor(2,1,2,3,fl);
// 	draw_ac(5,1,5,3,fl);
// 	draw_current(6,1,6,3,fl);
// 	draw_text(1,0,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",resistor,fl);
// 	draw_text(3,2,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",capacitor,fl);
// 	draw_text(2,1,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",inductor,fl);
// 	draw_text(5,1,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",voltage,fl);
// 	draw_net_text(1,0,1,"Net1",fl);
// 	end_svg(fl);
// 	fclose(fl);
// }