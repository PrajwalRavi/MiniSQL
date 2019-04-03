%{
	#include<stdio.h>
	#include <stdlib.h>
	#include <string.h>
%}

%token <str> INSERT 
%token <str> RECORD 
%token <str> NUM 
%token <str> GET 
%token <str> AND 
%token <str> OR 
%token <str> UPDATE 
%token <str> DELETE 
%token <str> INTO 
%token <str> SET 
%token <str> TO 
%token <str> WHERE 
%token <str> VAR 
%token <str> STRING
%token <str> LB
%token <str> RB
%token <str> COLON

%union {
        char str[200];              /* Ptr to constant string (strings are malloc'd) */
    };

%%	
STMT: INS | GET {printf("Statement executed succesfully.\n");};
INS: INSERT RECORD LB NUM STRING NUM STRING NUM NUM RB INTO VAR COLON {
		char *file_name = "EMP.txt";
		if(strcmp($12,file_name))
		{
			printf("File doesn't exist\n");
			return 0;
		}
		FILE *fp = fopen($12,"a");
		fprintf(fp, "%s %s %s %s %s %s\n",$4,$5,$6,$7,$8,$9 );
		fclose(fp);
	}; | INSERT RECORD LB NUM STRING STRING RB INTO VAR COLON {
		char *file_name = "DEPT.txt";
		if(strcmp($9,file_name))
		{
			printf("File doesn't exist\n");
			return 0;
		}
		FILE *fp = fopen($9,"a");
		fprintf(fp, "%s %s %s\n",$4,$5,$6);
		fclose(fp);
	};
GET: 
%%