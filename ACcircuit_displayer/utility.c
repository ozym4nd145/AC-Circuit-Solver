#include "ac.h"

void make_point(int x,int y)
{
fprintf(outfile,"<circle cx=\"%d\" cy=\"%d\" r=\"4\"/>\n",x,y);//TODO check radius
}

void make_line(int x1,int y1,int x2,int y2)
{
fprintf(outfile,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"2\" stroke=\"black\"/>\n",x1,y1,x2,y2);
}

void make_element()
{

}
