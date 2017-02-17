%{
#include "y.tab.h"
#include "ac.h"
%}
digit [0-9]
natural [0-9]+
sp [ \t]+
alphabet [a-zA-Z_]
real {natural}("."{natural})?
name ({alphabet}|{natural})+
resistance {real}{unit}?
capacitance {real}{unit}?[Ff]
inductance {real}{unit}?[Hh]
frequency {real}{unit}?([Hh][Zz])
voltage [Vv]({alphabet}|{natural})*
current [Ii]({alphabet}|{natural})*
unit ("F"|"P"|"N"|"U"|"M"|"K"|([Mm][Ee][Gg]))

%s TERMINAL1
%s TERMINAL2
%s value
%s SOURCE
%s EXPECTINGEND
%s ERR
%%
[ \t]+ 			{/*printf("Consuming space - \"%s\"\n",yytext);*/}
<INITIAL>{voltage} { yylval.s=strdup(yytext); /*printf("Intial = \"%s\"\n",yytext);*/BEGIN TERMINAL1;/*printf("1\n");*/ return VSOURCE;}
<INITIAL>{current} { yylval.s=strdup(yytext); /*printf("Intial = \"%s\"\n",yytext);*/BEGIN TERMINAL1;/*printf("2\n");*/ return ISOURCE;}
<INITIAL>{name}    { yylval.s=strdup(yytext); /*printf("Intial = \"%s\"\n",yytext);*/BEGIN TERMINAL1;/*printf("3\n");*/ return COMPONENT;}
<TERMINAL1>{name}  { yylval.s=strdup(yytext); /*printf("T1 = \"%s\"\n",yytext);*/BEGIN TERMINAL2;/*printf("4\n");*/ return TERMINAL;}
<TERMINAL2>{name}  { yylval.s=strdup(yytext); /*printf("T2 = \"%s\"\n",yytext);*/BEGIN value;/*printf("7\n");*/ return TERMINAL;}
<value>{inductance} { yylval.s=strdup(yytext);/*	printf("Val = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND;/*printf("8\n");*/ return INDUCTANCE; }
<value>{capacitance} { yylval.s=strdup(yytext);	/*printf("Val = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND;/*printf("9\n");*/ return CAPACITANCE; }
<value>{resistance} { yylval.s=strdup(yytext); /*printf("Val = \"%s\"\n",yytext);*/BEGIN EXPECTINGEND;/*printf("10\n");*/ return RESISTANCE; }
<value>[sS][iI][nN][eE] { /*printf("Val = \"%s\"\n",yytext)*/;BEGIN SOURCE;/*printf("11\n");*/ return SINE; }
<value>[^ \t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/ BEGIN ERR;}
<ERR>[^ \t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/ BEGIN ERR;}
<INITIAL>[^ \t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/BEGIN ERR;}
<TERMINAL1>[^ \t\n]* {/* printf("Err match = \"%s\"\n",yytext);*/BEGIN ERR;}
<TERMINAL2>[^ \t\n]* { /*printf("Err match = \"%s\"\n",yytext);*/BEGIN ERR;}
<EXPECTINGEND>[.\n] {/*printf("Matched End\n");*/BEGIN INITIAL;/*printf("12\n");*/ yylineno++;return END;}
<SOURCE>.* { yylval.s=strdup(yytext);/*printf("Src = \"%s\"\n",yytext);*/ BEGIN EXPECTINGEND;/*printf("13\n");*/ return SOURCEDATA;}
.                   {printf("Unrec char = \"%s\"\n",yytext);yyerror ("Error - Format of input file is wrong 2\n");}
\n {/*printf("Matched stray \"\\n\"\n");*/ BEGIN INITIAL; printf("Syntax Error in line no. %d\n",yylineno);yylineno++; return er;}
%%

int yywrap (void) 
{return 1;}
