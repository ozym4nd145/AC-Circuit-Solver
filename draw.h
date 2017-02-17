#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>

extern float LINE_WIDTH;
extern float CIRCLE_WIDTH;
int start_svg(int rows, int cols, FILE* ptr);
int draw_line(int x1,int y1, int x2, int y2,FILE* ptr);
int draw_circle(int x,int y, FILE* ptr);
int end_svg(FILE* ptr);

#endif