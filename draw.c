#include "draw.h"
#include <stdio.h>

float LINE_WIDTH=0.1;
float CIRCLE_WIDTH=0.1;


/**
 * Convention: parameters x and y in functions
 * X : -> Horizontal shift
 * Y : -> Vertical shift
 */

int start_svg(int rows, int cols, FILE* ptr)
{
	fprintf(ptr, "<svg viewBox=\"0 0 %d %d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" >\n",(cols+10),(rows+10));
}
int draw_line(int x1,int y1, int x2, int y2,FILE* ptr)
{
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

int main()
{
	FILE* fl = fopen("test_2.svg","w");
	start_svg(5,10,fl);
	draw_line(0,0,0,10,fl);
	draw_line(1,0,1,10,fl);
	draw_line(2,0,2,10,fl);
	draw_line(3,0,3,10,fl);
	draw_line(2,3,2,4,fl);
	draw_line(1,0,1,4,fl);
	draw_circle(1,0,fl);
	draw_circle(1,4,fl);
	end_svg(fl);
	fclose(fl);
}