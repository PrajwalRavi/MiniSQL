%{
	#include<stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int ind_condition = 0, ind_and_or = 0, ind_result = 0;
	char conditions[100][100];
	int joiners[10],results[100]={0};

	char emp_fields[6][10] = {"eid","ename","eage","eaddress","salary","deptno"};
	char dept_fields[4][10] = {"dnum", "dname", "dlocation"};

	int check_conditions()
	{
		char condition[100];
		int result = 0;
		// Iterate over each condition
		for(int i=0; i<ind_condition; i++)
		{
			result = 0;
			strcpy(condition, conditions[i]);
			char* field = strtok(condition," ");
			for(int i=0; i<6; i++)
				if(strcmp(emp_fields[i],field)!=0)
					result = 1;
			if(result==0)
				break;
		}
		if(result==1)
			return 1;
		result = 1;
		for(int i=0; i<ind_condition; i++)
		{
			result = 0;
			strcpy(condition, conditions[i]);
			char* field = strtok(condition," ");
			for(int i=0; i<3; i++)
				if(strcmp(dept_fields[i],field)!=0)
					result =  1;
			if(result==0)
				return 0;
			// if(!(strcmp(field,"eid") || strcmp(field,"ename") || strcmp(field,"eage") || strcmp(field,"eaddress") || strcmp(field,"salary") || strcmp(field,"deptno")))
			// 	return 0;
			// if(!(strcmp(field,"dnum") || strcmp(field,"dname") || strcmp(field,"dlocation")))
			// 	return 0;
		}
		
		return 1;
	}

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
STMT: INS {printf("Statement executed succesfully.\n");}; | DEL {printf("Statement executed succesfully.\n");};

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
		if(check_conditions()==0)
		{
			printf("Error in conditions\n");
			return 0; 
		}

		FILE *fp = fopen($4,"r");
		FILE *fp_temp = fopen("temp_file.txt","w");
		char line[100], original_line[100];
		char *field_val;
				
		while (fgets(line,100,fp)!=NULL)	// Iterate over each record
		{
			strcpy(original_line,line);
			int field_num = 0;
			char* saveptr1;
			field_val = strtok_r(line," ",&saveptr1);
			int flag = 1;

			while(field_val!=NULL)	// Iterate over each field in the record
			{
				char field_name[10];
				strcpy(field_name,emp_fields[field_num]);
				char condition[100];
				// Iterate over each condition
				for(int i=0; i<ind_condition; i++)
				{
					char* saveptr2;
					strcpy(condition, conditions[i]);
					char* operand1 = strtok_r(condition," ",&saveptr2);
					char* operator = strtok_r(NULL," ",&saveptr2);
					char* operand2 = strtok_r(NULL," ",&saveptr2);
					if(strcmp(operand1,field_name)==0)
					{
						// Checking for integer fields
						if(field_num!=1 && field_num!=3)
						{
							int op = atoi(operand2);
							int val = atoi(field_val);
							if((strcmp(operator,"==")==0 && op!=val)
								|| (strcmp(operator,"!=")==0 && op==val)
								|| (strcmp(operator,">=")==0 && op>val)
								|| (strcmp(operator,"<=")==0 && op<val)
								|| (strcmp(operator,">")==0 && op>=val)
								|| (strcmp(operator,"<")==0 && op<=val)
								)
							{
								results[ind_result++]=0;
								flag=0;
								break;
							}
							else 
								results[ind_result++]=1;
						}
						// For strings
						else if((strcmp(operator,"==")==0 && strcmp(operand2,field_val))
							|| (strcmp(operator,"!=")==0 && strcmp(operand2,field_val)==0)
							|| (strcmp(operator,">=")==0 && strcmp(field_val,operand2)<0)
							|| (strcmp(operator,"<=")==0 && strcmp(field_val,operand2)>0)
							|| (strcmp(operator,">")==0 && strcmp(field_val,operand2)<=0)
							|| (strcmp(operator,"<")==0 && strcmp(field_val,operand2)>=0)
							)
						{
							results[ind_result++]=0;
							flag=0;
							break;
						}
						else 
							results[ind_result++]=1;

					}
				}
				field_num++;
				field_val = strtok_r(NULL," ",&saveptr1);
			}
			if(!flag)
			{
				fprintf(fp_temp, "%s",original_line );
			}
		}
		// TO-DO : Implement And Or stuff
		fclose(fp);
		fclose(fp_temp);
		// Replaces file contents with temp_file
		fp = fopen($4,"w");
		fp_temp = fopen("temp_file.txt","r");
		while (fgets(line,100,fp_temp)!=NULL)
			fprintf(fp, "%s",line );
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