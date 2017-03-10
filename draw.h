#ifndef DRAW_H
#define DRAW_H

#include "ac.h"

extern float LINE_WIDTH;
extern float CIRCLE_WIDTH;
void start_svg(int rows, int cols, FILE* ptr);
void draw_line(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_circle(int x,int y, FILE* ptr);
void end_svg(FILE* ptr);
void place_resistor(int x, int y, FILE* ptr);
void place_capacitor(int x, int y, FILE* ptr);
void place_inductor(int x, int y, FILE* ptr);
void place_ac(int x,int y, FILE* ptr);
void place_current(int x,int y, FILE* ptr);
void draw_resistor(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_capacitor(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_inductor(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_ac(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_current(int x1,int y1, int x2, int y2,FILE* ptr);
void make_element(int x1,int y1,int x2,int y2,enum component_type type,char* name, FILE* ptr);
void place_text(int x,int y, float off_x,char* text, char* color, FILE* ptr);
void draw_text(int x, int y, char* text, enum component_type type, FILE* ptr);
void draw_net_text(int x, int y, int is_up,char* text, FILE* ptr);
void draw_ground(int x,int y, FILE* ptr);
#endif