%{
	#include<stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int ind_condition = 0, ind_and_or = 0;
	char conditions[100][100];
	int joiners[10];
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
%token <str> FROM
%token <str> VAR 
%token <str> STRING
%token <str> LB
%token <str> RB
%token <str> COLON
%token <str> REL_OP

%type <str> CONDITION
%type <str> CONDITIONS
%type <str> JOINER

%union {
        char str[200];              /* Ptr to constant string (strings are malloc'd) */
    };

%%	
STMT: INS | DEL {printf("Statement executed succesfully.\n");};

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

DEL: DELETE RECORD FROM VAR WHERE CONDITIONS COLON {
		if(strcmp($4,"EMP.txt")!=0 && strcmp($4,"DEPT.txt")!=0)
		{
			printf("File doesn't exist\n");
			return 0;
		}
		FILE *fp = fopen($4,"r");
	    char line[100];
	    char* token;
    	while (fgets(line,sizeof(line),fp)!=NULL)
		{
			printf("%s",line );
			int field_num = 1;
			token = strtok(line," ");
			while(token!=NULL)
			{
				// printf("%s\n",token );
				char condition[100];
				for(int i=0; i<ind_condition; i++)
				{
					strcpy(condition, conditions[i]);
					char* operand1 = strtok(condition," ");
					char* operator = strtok(NULL," ");
					char* operand2 = strtok(NULL," ");
				}
				token = strtok(NULL," ");
			}
		}
	};

CONDITIONS: CONDITION JOINER CONDITIONS {strcpy(conditions[ind_condition++],$1);}
			| CONDITION {strcpy(conditions[ind_condition++],$1);};  

CONDITION: VAR REL_OP STRING {
		strcpy($$,$1);
		strcat($$," ");
		strcat($$,$2);
		strcat($$," ");
		strcat($$,$3);
		};
	| VAR REL_OP NUM {
		strcpy($$,$1);
		strcat($$," ");
		strcat($$,$2);
		strcat($$," ");
		strcat($$,$3);
		};


JOINER: AND { joiners[ind_and_or++] = 1; }
		| OR { joiners[ind_and_or++] = 0; };
%%