#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>

extern float LINE_WIDTH;
extern float CIRCLE_WIDTH;
int start_svg(int rows, int cols, FILE* ptr);
int draw_line(int x1,int y1, int x2, int y2,FILE* ptr);
int draw_circle(int x,int y, FILE* ptr);
int end_svg(FILE* ptr);
int place_resistor(int x, int y, FILE* ptr);
int place_capacitor(int x, int y, FILE* ptr);
int place_inductor(int x, int y, FILE* ptr);
int place_ac(int x,int y, FILE* ptr);
int place_current(int x,int y, FILE* ptr);
int draw_resistor(int x1,int y1, int x2, int y2,FILE* ptr);
int draw_capacitor(int x1,int y1, int x2, int y2,FILE* ptr);
int draw_inductor(int x1,int y1, int x2, int y2,FILE* ptr);
int draw_ac(int x1,int y1, int x2, int y2,FILE* ptr);
int draw_current(int x1,int y1, int x2, int y2,FILE* ptr);

#endif