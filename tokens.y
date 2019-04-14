%{
	#include<stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int ind_condition = 0, ind_and_or = 0, ind_result = 0;
	int emp_size = 0,dept_size = 0;
	char *file1 = "EMP.txt";
	char *file2 = "DEPT.txt";
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

	void Delete(char *file,int res[100])
	{
		FILE *fp_temp = fopen("temp_file.txt","w");
		FILE *fp = fopen(file,"r");
		char record[100],line[100];
		int row = -1;
		if(strcmp(file,"DEPT.txt") == 0)
		{
			FILE *fp1 = fopen("EMP.txt","r");
			while (fgets(line,100,fp)!=NULL)
			{
				char* original_line;
				strcpy(original_line,line);
				row++;
				if(res[row])
				{
					char* dsaveptr;
					char *dfields = strtok_r(line," ",&dsaveptr);
					int ddeptno = atoi(dfields);
					while(fgets(record,100,fp1) != NULL)
					{	
						int num_field = 0;
						char *esaveptr;
						char *efields = strtok_r(record," ",&esaveptr);
						while(num_field != 5)
						{	
							efields = strtok_r(NULL," ",&esaveptr);
							num_field++;
						}
						int edeptno = atoi(efields);
						if(edeptno == ddeptno)
						{
							printf("Cannot delete a reference to a foreign key!!\n");
							fprintf(fp_temp, "%s",original_line);	
						}

					}
					
				}
				else
				{
					fprintf(fp_temp,"%s",line);
				}
			}

			fclose(fp1);	
		}

		else
		{
			while (fgets(line,100,fp)!=NULL)
			{
				row++;
				if(!res[row])
					fprintf(fp_temp, "%s",line );
			
			}
		}
		fclose(fp);
		fclose(fp_temp);
		fp = fopen(file,"w");
		fp_temp = fopen("temp_file.txt","r");
		while (fgets(line,100,fp_temp)!=NULL)
			fprintf(fp, "%s",line );
		fclose(fp);
		fclose(fp_temp);
	}
	int Result(char * file,int ind_condition)
	{
		// printf("I sdfam here!!!!!!!!!\n");

		FILE *fp  = fopen(file,"r");
		char line[100], original_line[100];
		char *field_val;
		int row = -1,i = ind_condition;
		while (fgets(line,100,fp)!=NULL)	// Iterate over each record
		{
			row++;
			// printf("%d\n",row);
			strcpy(original_line,line);
			int field_num = 0;
			char* saveptr1;
			field_val = strtok_r(line," ",&saveptr1);

			while(field_val!=NULL)	// Iterate over each field in the record
			{
				// printf("infinite\n");
				char field_name[10];
				if(strcmp(file,"EMP.txt") == 0)
					strcpy(field_name,emp_fields[field_num]);
				else strcpy(field_name,dept_fields[field_num]);
				char condition[100];
				char* saveptr2;
				strcpy(condition, conditions[i]);
				char* operand1 = strtok_r(condition," ",&saveptr2);
				char* operator = strtok_r(NULL," ",&saveptr2);
				char* operand2 = strtok_r(NULL," ",&saveptr2);
				if(strcmp(operand1,field_name)==0)
				{
					// Checkg for integer fields
					// printf("sdfdsdf\n");
					int j = strcmp(file,"EMP.txt")==0?3:2;
					if(field_num!=1 && field_num!=j)
					{
						int op = atoi(operand2);
						int val = atoi(field_val);
						if((strcmp(operator,"==")==0 && op==val)
							|| (strcmp(operator,"!=")==0 && op!=val)
							|| (strcmp(operator,">=")==0 && op<=val)
							|| (strcmp(operator,"<=")==0 && op>=val)
							|| (strcmp(operator,">")==0 && op<val)
							|| (strcmp(operator,"<")==0 && op>val)
							)
						{
							results[row] = 1;
							// printf("Remove%d\n",row);
						}
						else 
						{
							results[row] = 0;
							// printf("Keep%d\n",row);
						}
					}
					// For strings
					else if((strcmp(operator,"==")==0 && strcmp(operand2,field_val)==0)
						|| (strcmp(operator,"!=")==0 && strcmp(operand2,field_val))
						|| (strcmp(operator,">=")==0 && strcmp(field_val,operand2)>=0)
						|| (strcmp(operator,"<=")==0 && strcmp(field_val,operand2)<=0)
						|| (strcmp(operator,">")==0 && strcmp(field_val,operand2)>0)
						|| (strcmp(operator,"<")==0 && strcmp(field_val,operand2)<0)
						)
					{
						results[row] = 1;
						// printf("Remove%d\n",row);
					}
					else 
					{
						results[row] = 0;
						// printf("Keep%d\n",row);
					}

				}
			field_num++;
			field_val = strtok_r(NULL," ",&saveptr1);
			}
		}
		fclose(fp);
		// printf("%d\n",row);
		// for(int k = 0;k <= row;k++){
		// 	printf("%d ",results[k]);
		// }
		printf("\n");
		return row;
					
	}
	int check_uniqueness(char* file_name, char* value)
	{
		char line[100];
		char* field_val;
		FILE* fp = fopen(file_name,"r");
		while (fgets(line,100,fp)!=NULL)	// Iterate over each record
		{
			field_val = strtok(line," ");
			if(strcmp(field_val,value)==0)
				return 0;
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
		if(!check_uniqueness(file_name,$4))
		{
			printf("Eid should be unique\n");
			return 0;
		}
		
		// Check foreign-key constraint
		FILE* dept_fp = fopen("DEPT.txt","r");
		char line[100];
		char* field_val;
		int flag = 1;
		while (fgets(line,100,dept_fp)!=NULL)	// Iterate over each record
		{
			field_val = strtok(line," ");
			if(strcmp(field_val,$9)==0)
			{
				flag=0;
				break;
			}
		}
		if(flag)
		{
			printf("Foreign-key constraint violated\n");
			return 0;
		}

		FILE *fp = fopen($12,"a");
		fprintf(fp, "%s %s %s %s %s %s\n",$4,$5,$6,$7,$8,$9 );
		emp_size++;
		fclose(fp);
	}; | INSERT RECORD LB NUM STRING STRING RB INTO VAR COLON {
		char *file_name = "DEPT.txt";
		if(strcmp($9,file_name))
		{
			printf("File doesn't exist\n");
			return 0;
		}
		if(!check_uniqueness(file_name,$4))
		{
			printf("Deptno should be unique\n");
			return 0;
		}		
		FILE *fp = fopen($9,"a");
		fprintf(fp, "%s %s %s\n",$4,$5,$6);
		dept_size++;
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
		
		
		// Doing for Ands first
		for(int o=0;o<ind_and_or;o++)
		{
			if(joiners[o]==0)
				continue;
			else
			{
				int and_r[100], row = -1;
				for(int ii=0;ii<100;ii++)
					and_r[ii]=1;
				while(joiners[o]==1)
				{
					for(int i=o; i<o+2; i++)
					{
						// printf("jkfnje\n");
						row = Result($4,i);
						for(int k = 0;k<=row;k++)
						{
							and_r[k] *= results[k];
						}
					}
					o++;
				}
				row = -1;
				Delete($4,and_r);
		
		 	}
		 }

		// Doing  for Ors
		for(int o=0;o<ind_and_or;o++)
		{
			FILE *fp = fopen($4,"r");
			FILE *fp_temp = fopen("temp_file.txt","w");
			char line[100], original_line[100];
			char *field_val;
			if(joiners[o]==1)
				continue;
			if(joiners[o]==0 && o==0)
			{
				int r[100] = {0}, row = -1;
				row = -1;
				while (fgets(line,100,fp)!=NULL)	// Iterate over each record
				{
					row++;
					strcpy(original_line,line);
					int field_num = 0;
					char* saveptr1;
					field_val = strtok_r(line," ",&saveptr1);

					while(field_val!=NULL)	// Iterate over each field in the record
					{
						char field_name[10];
						strcpy(field_name,emp_fields[field_num]);
						char condition[100];
						for(int i=0; i<1; i++)
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
									if((strcmp(operator,"==")==0 && op==val)
										|| (strcmp(operator,"!=")==0 && op!=val)
										|| (strcmp(operator,">=")==0 && op<=val)
										|| (strcmp(operator,"<=")==0 && op>=val)
										|| (strcmp(operator,">")==0 && op<val)
										|| (strcmp(operator,"<")==0 && op>val)
										)
									{
										r[row] = 1;
									}
									else 
									{
										r[row] = 0;
									}
								}
								// For strings
								else if((strcmp(operator,"==")==0 && strcmp(operand2,field_val)==0)
									|| (strcmp(operator,"!=")==0 && strcmp(operand2,field_val))
									|| (strcmp(operator,">=")==0 && strcmp(field_val,operand2)>=0)
									|| (strcmp(operator,"<=")==0 && strcmp(field_val,operand2)<=0)
									|| (strcmp(operator,">")==0 && strcmp(field_val,operand2)>0)
									|| (strcmp(operator,"<")==0 && strcmp(field_val,operand2)<0)
									)
								{
									r[row] = 1;
								}
								else 
								{	
									r[row] = 0;
								}

							}
						}
						field_num++;
						field_val = strtok_r(NULL," ",&saveptr1);
					}
					
				}
				fclose(fp);
				row = -1;
				fp = fopen($4,"r");
				while (fgets(original_line,100,fp)!=NULL)
				{
					row++;
					if(!r[row])
						fprintf(fp_temp, "%s",original_line );
				}
				
				fclose(fp);
				fclose(fp_temp);
				fp = fopen($4,"w");
				fp_temp = fopen("temp_file.txt","r");
				while (fgets(line,100,fp_temp)!=NULL)
					fprintf(fp, "%s",line );
				fclose(fp);
				fclose(fp_temp);

			}
			if(joiners[o]==0 && ((joiners[o+1]==0 && o+1<ind_and_or) || o==ind_and_or-1)) 
			{
				int r[100], row = -1;
				fp = fopen($4,"r");
				fp_temp = fopen("temp_file.txt","w");
				row = -1;
				while (fgets(line,100,fp)!=NULL)	// Iterate over each record
				{
					row++;
					strcpy(original_line,line);
					int field_num = 0;
					char* saveptr1;
					field_val = strtok_r(line," ",&saveptr1);

					while(field_val!=NULL)	// Iterate over each field in the record
					{
						char field_name[10];
						strcpy(field_name,emp_fields[field_num]);
						char condition[100];
						for(int i=o+1; i<o+2; i++)
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
									if((strcmp(operator,"==")==0 && op==val)
										|| (strcmp(operator,"!=")==0 && op!=val)
										|| (strcmp(operator,">=")==0 && op<=val)
										|| (strcmp(operator,"<=")==0 && op>=val)
										|| (strcmp(operator,">")==0 && op<val)
										|| (strcmp(operator,"<")==0 && op>val)
										)
									{
										printf("Remove%d\n",row);
										r[row] = 1;
									}
									else 
									{
										printf("Keep%d\n",row);
										r[row] = 0;
									}
								}
								// For strings
								else if((strcmp(operator,"==")==0 && strcmp(operand2,field_val)==0)
									|| (strcmp(operator,"!=")==0 && strcmp(operand2,field_val))
									|| (strcmp(operator,">=")==0 && strcmp(field_val,operand2)>=0)
									|| (strcmp(operator,"<=")==0 && strcmp(field_val,operand2)<=0)
									|| (strcmp(operator,">")==0 && strcmp(field_val,operand2)>0)
									|| (strcmp(operator,"<")==0 && strcmp(field_val,operand2)<0)
									)
								{
									r[row] = 1;
								}
								else 
									r[row] = 0;

							}
						}
						field_num++;
						field_val = strtok_r(NULL," ",&saveptr1);
					}
					
				}
				fclose(fp);
				row = -1;
				fp = fopen($4,"r");
				while (fgets(original_line,100,fp)!=NULL)
				{
					row++;
					if(!r[row])
						fprintf(fp_temp, "%s",original_line );
				}
				
				fclose(fp);
				fclose(fp_temp);
				fp = fopen($4,"w");
				fp_temp = fopen("temp_file.txt","r");
				while (fgets(line,100,fp_temp)!=NULL)
					fprintf(fp, "%s",line );
				fclose(fp);
				fclose(fp_temp);
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