%{
	#include<stdlib.h>
	#include "y.tab.h"
	// TO-DO : Make keywords case in-sensitive. INTO has been dome for you.
%}

%%
[iI][nN][sS][eE][rR][tT] return INSERT;
[rR][eE][cC][oO][rR][dD] return RECORD;
[gG][eE][tT] return GET;
[aA][nN][dD] return AND;
[oO][rR] return OR;
[uU][Pp][Dd][aA][tT][eE] return UPDATE;
[dD][eE][lL][eE][Tt][Ee] return DELETE;
[iI][nN][Tt][Oo] return INTO;
[sS][eE][tT] return SET;
[tT][oO] return TO;
[wW][hH][eE][rR][eE] return WHERE;
[fF][rR][Oo][mM] return FROM;

[0]|[1-9][0-9]* {strcpy(yylval.str,yytext); return NUM;}
\"[A-Za-z0-9._]+\" {strcpy(yylval.str,yytext);return STRING;}
[A-Za-z_][A-Za-z0-9.$_]* {strcpy(yylval.str,yytext); return VAR;}
\( {strcpy(yylval.str,yytext); return LB;}
\) {strcpy(yylval.str,yytext); return RB;}
\; {strcpy(yylval.str,yytext); return COLON;}
">="|"<="|"!="|"=="|"<"|">" {strcpy(yylval.str,yytext); return REL_OP;}
. ;
%%
