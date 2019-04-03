%{
	#include<stdlib.h>
	#include "y.tab.h"
	// TO-DO : Make keywords case in-sensitive. INTO has been dome for you.
%}

%%
INSERT return INSERT;
RECORD return RECORD;
GET return GET;
AND return AND;
OR return OR;
UPDATE return UPDATE;
DELETE return DELETE;
INTO return INTO;
into return INTO;
SET return SET;
TO return TO;
WHERE return WHERE;

[1-9][0-9]* {strcpy(yylval.str,yytext); return NUM;}
\"[A-Za-z0-9.]+\" {strcpy(yylval.str,yytext);return STRING;}
[A-Za-z_][A-Za-z0-9.]* {strcpy(yylval.str,yytext); return VAR;}
\( {strcpy(yylval.str,yytext); return LB;}
\) {strcpy(yylval.str,yytext); return RB;}
\; {strcpy(yylval.str,yytext); return COLON;}
. ;
%%
