%{
#include "y.tab.h"
%}
digit [0-9]
natural [0-9]+
sp [ \t]+
alphabet [a-zA-Z_]
real {natural}("."{natural})?
name [a-zA-Z_]({alphabet}|{natural})*
zero "0"
resistance {real}{unit}?
capacitance {real}{unit}?[Ff]
inductance {real}{unit}?[Hh]
frequency {real}{unit}?([Hh][Zz])
voltage [Vv]({alphabet}|{natural})*
current [Ii]({alphabet}|{natural})*
unit ("F"|"P"|"N"|"U"|"M"|"K"|"MEG")

%s TERMINAL1
%s TERMINAL2
%s value
%s SOURCE
%s EXPECTINGEND
%%
[ \t]+ 			{;}
<INITIAL>{voltage} { yylval.s=strdup(yytext); BEGIN TERMINAL1;printf("1\n"); return VSOURCE;}
<INITIAL>{current} { yylval.s=strdup(yytext); BEGIN TERMINAL1;printf("2\n"); return ISOURCE;}
<INITIAL>{name}    { yylval.s=strdup(yytext); BEGIN TERMINAL1;printf("3\n"); return COMPONENT;}
<TERMINAL1>{name}  { yylval.s=strdup(yytext); BEGIN TERMINAL2;printf("4\n"); return TERMINAL;}
<TERMINAL1>{zero}  { yylval.s=strdup(yytext); BEGIN value;printf("5\n"); return TERMINAL;}
<TERMINAL2>{zero}  { yylval.s=strdup(yytext); BEGIN value;printf("6\n"); return TERMINAL;}
<TERMINAL2>{name}  { yylval.s=strdup(yytext); BEGIN value;printf("7\n"); return TERMINAL;}
<value>{inductance} { yylval.s=strdup(yytext);	BEGIN EXPECTINGEND;printf("8\n"); return INDUCTANCE; }
<value>{capacitance} { yylval.s=strdup(yytext);	BEGIN EXPECTINGEND;printf("9\n"); return CAPACITANCE; }
<value>{resistance} { yylval.s=strdup(yytext); BEGIN EXPECTINGEND;printf("10\n"); return RESISTANCE; }
<value>[sS][iI][nN][eE] { BEGIN SOURCE;printf("11\n"); return SINE; }
<EXPECTINGEND>[\n]+ {BEGIN INITIAL;printf("12\n"); return END;}
<SOURCE>.* { yylval.s=strdup(yytext); BEGIN EXPECTINGEND;printf("13\n"); return SOURCEDATA;}
.                   {printf("%s\n",yytext);yyerror ("Error:- Format of input file is wrong 2\n");}
%%

int yywrap (void) 
{return 1;}
