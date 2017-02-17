%{
#include "y.tab.h"
%}
digit [0-9]
natural (digit)+
unit ("F"|"P"|"N"|"U"|"M"|"K"|"MEG"|"")
%%
[sS][iI][nN][eE]		{printf("sine returned\n");return sine;}
[a-zA-Z][^ \t]*			{printf("alnum returned\n");return alnum;}
[0-9]*(\.[0-9]+)? 		{printf("number returned\n"); return number;}
[ \t]*                	   {printf("space returned\n"); return space;}
(\n)+			   {printf("new_line returned\n");return new_line;}
"("|")"           	   {printf("%s returned\n",yytext);return yytext[0];}
.                      	   {yyerror ("Unrecognized character");exit(1);}
%%

int yywrap (void) 
{return 1;}




