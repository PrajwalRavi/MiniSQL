%{
	#include<stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int ind_condition = 0, ind_and_or = 0, ind_result = 0, ind_field=0;
	int emp_size = 0,dept_size = 0;
	char *file1 = "EMP.txt";
	char *file2 = "DEPT.txt";
	char conditions[100][100], field_list[100][100];
	int joiner[10],joiners[10],results[100]={0};
	char emp_fields[6][10] = {"eid","ename","eage","eaddress","salary","deptno"};
	char dept_fields[4][10] = {"dnum", "dname", "dlocation"};
	char update_string[100];

	int check_conditions()
	{
		for(int k = ind_and_or-1;k >=0;k--)
			joiners[ind_and_or-k-1] = joiner[k];
		char condition[100];
		int result = 0;
		for(int i=0; i<ind_condition; i++)
		{
			result = 0;
			strcpy(condition, conditions[i]);
			char* field = strtok(condition," ");
			for(int i=0; i<6; i++)
				if(strcmp(emp_fields[i],field)==0)
					result = 1;
			if(result==0)
				break;
		}
		if(result==1)
			return 1;
		result = 0;
		for(int i=0; i<ind_condition; i++)
		{
			result = 0;
			strcpy(condition, conditions[i]);
			char* field = strtok(condition," ");
			for(int i=0; i<3; i++)
				if(strcmp(dept_fields[i],field)==0)
					result =  1;
			if(result==0)
				return 0;
		}
		
		return 1;
	}

	int check_uniqueness(char* file_name, char* value)
	{
		char line[100];
		char* field_val;
		FILE* fp = fopen(file_name,"r");
		while (fgets(line,100,fp)!=NULL)
		{
			field_val = strtok(line," ");
			if(strcmp(field_val,value)==0)
				return 0;
		}
		return 1;
	}

	int check_constraint(char* value)
	{
		FILE* dept_fp = fopen("DEPT.txt","r");
		char line[100];
		char* field_val;
		int flag = 1;
		while (fgets(line,100,dept_fp)!=NULL)	// Iterate over each record
		{
			field_val = strtok(line," ");
			if(strcmp(field_val,value)==0)
			{
				return 1;
			}
		}
		return 0;
	}

	int check_constraint2(char* value)
	{
		FILE *fp1 = fopen("EMP.txt","r");
		char record[100];
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
			strcat(value,"\n");
			if(strcmp(value,efields)==0)
			{
				fclose(fp1);
				return 0;
			}

		}
		fclose(fp1);
		return 1;
	}

	int check_fields(char *file)
	{
		for(int i = 0; i <ind_field; i++)
		{
			int result = 0;
			if(strcmp(file,"EMP.txt") == 0)
			{
				result=0;
				for(int j=0;j<6;j++)
					if(strcmp(emp_fields[j],field_list[i])==0)  
						result=1;
				if(result==0)
					return 0;
			}
			else if(strcmp(file,"DEPT.txt") == 0)
			{
				result = 0;
				for(int j=0;j<3;j++)
					if(strcmp(dept_fields[j],field_list[i])==0) 
						result=1;
				if(result==0)
					return 0;
			}
		}
		return 1;
	}

	void Delete(char *file,int res[100])
	{
		FILE *fp_temp = fopen("temp_file.txt","w");
		FILE *fp = fopen(file,"r");
		char line[100];
		int row = -1;
		if(strcmp(file,"DEPT.txt") == 0)
		{
			while (fgets(line,100,fp)!=NULL)
			{
				char original_line[100];
				strcpy(original_line,line);
				row++;
				if(res[row])
				{
					char* dsaveptr;
					char *dfields = strtok_r(line," ",&dsaveptr);
					if(check_constraint2(dfields)==0)
					{
						printf("Cannot delete a reference to a foreign key!!\n");
						fprintf(fp_temp, "%s",original_line);
						break;
					}	
				}
				else
					fprintf(fp_temp,"%s",line);
			}

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
		FILE *fp  = fopen(file,"r");
		char line[100], original_line[100];
		char *field_val;
		int row = -1,i = ind_condition;
		while (fgets(line,100,fp)!=NULL)
		{
			row++;
			strcpy(original_line,line);
			int field_num = 0;
			char* saveptr1;
			field_val = strtok_r(line," ",&saveptr1);

			while(field_val!=NULL)
			{
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
						}
						else 
							results[row] = 0;
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
					}
					else 
						results[row] = 0;

				}
			field_num++;
			field_val = strtok_r(NULL," ",&saveptr1);
			}
		}
		fclose(fp);
		printf("\n");
		return row;				
	}

	void Select(char *file,int res[100])
	{
		if(check_fields(file) == 0)
		{
			printf("Wrong fields given !!!\n");
			return;
		}
		FILE *fp = fopen(file,"r");
		char line[100],original_line[100];
		int row = -1;
		int field_num = -1;
		while(fgets(line,100,fp) != NULL)
		{	
			row++;
			if(!res[row]) continue;
			strcpy(original_line,line);
			char *saveptr;
			char *fields = strtok_r(line," ",&saveptr);
			field_num = 0;
			while(fields != NULL)
			{
				if(strcmp(file,"EMP.txt") == 0)
				{
					for(int k = 0; k <ind_field;k++)
						if(strcmp(field_list[k],emp_fields[field_num]) == 0)
							printf("%s ",fields);
				}
				else
				{
					for(int k = 0; k <ind_field;k++)
						if(strcmp(field_list[k],dept_fields[field_num]) == 0)
							printf("%s ",fields);
				}
				fields = strtok_r(NULL," ",&saveptr);
				field_num++;

			}
			printf("\n");
		}
		fclose(fp);
	}

	void Update(char *file,int res[100],char *upfield)
	{
		strcpy(field_list[0],upfield);
		ind_field=1;
		if(check_fields(file) == 0)
		{
			printf("Wrong field given !!!\n");
			return;
		}
		FILE *fp = fopen(file,"r");
		FILE *fp1 = fopen("Update.txt","w");
		char line[100],original_line[100];
		int row = -1;
		int field_num = -1;
		while(fgets(line,100,fp) != NULL)
		{	
			row++;
			if(!res[row]){
				fprintf(fp1,"%s",line);
				continue;
			}
			strcpy(original_line,line);
			char *saveptr;
			char *fields = strtok_r(line," ",&saveptr);
			field_num = 0;
			while(fields != NULL)
			{
				int flag = 0;
				if(strcmp(file,"EMP.txt") == 0)
				{
					if(strcmp(upfield,emp_fields[field_num])==0)
					{
						if(field_num!=1 && field_num!=3)
						{
							flag=1;
							char *ptr;
							strtol(update_string, &ptr, 10);
							if(*ptr!='\0')
								printf("Given field should be integer\n");
						}
						if(field_num==5 && !check_constraint(update_string))
						{
							flag = 1;
							printf("Foreign-key constraint violated\n");
						}
						if(field_num==0 && !check_uniqueness(file,update_string))
						{
							flag=1;
							printf("Eid should be unique\n");
						}
						if(flag==0)
						{
							strcpy(fields,update_string);
							if(field_num==5)
								strcat(update_string,"\n");
						}
					}
					if(field_num==5)
						fprintf(fp1,"%s",fields);
					else
						fprintf(fp1,"%s ",fields);
				}
				else
				{
					if(strcmp(upfield,dept_fields[field_num])==0)
					{
						if(field_num!=1 && field_num!=2)
						{
							flag=1;
							char *ptr;
							strtol(update_string, &ptr, 10);
							if(*ptr!='\0')
								printf("Given field should be integer\n");
						}
						if(field_num==0 && !check_uniqueness(file,update_string))
						{
							flag=1;
							printf("dnum should be unique\n");
						}
						if(field_num==0 && !check_constraint2(fields))
						{
							flag=1;
							printf("Foreign-key constraint violated\n");
						}
						if(flag==0)
						{
							strcpy(fields,update_string);
							if(field_num==2)
								strcat(update_string,"\n");
						}
					}
					if(field_num==2)
						fprintf(fp1,"%s",fields);
					else
						fprintf(fp1,"%s ",fields);
				}
				fields = strtok_r(NULL," ",&saveptr);
				field_num++;
			}
		}
		fclose(fp);
		fclose(fp1);
		fp = fopen(file,"w");
		fp1 = fopen("Update.txt","r");
		while (fgets(line,100,fp1)!=NULL)
			fprintf(fp, "%s",line );
		fclose(fp);
		fclose(fp1);
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
%token <str> IN
%token <str> COLON
%token <str> REL_OP
%type <str> VALUE
%type <str> CONDITION
%type <str> CONDITIONS
%type <str> FIELDLIST
%type <str> JOINER

%union {
		char str[200];
	};

%%	

STMT: INS {printf("Statement executed succesfully.\n");} 
	| DEL {printf("Statement executed succesfully.\n");}
	| SELECT {printf("Statement executed succesfully.\n");}
	| UPD {printf("Statement executed succesfully.\n");};
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
		if(!check_constraint($9))
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
		int and_r[100],final_r[100];
		for(int ii=0;ii<100;ii++)
			final_r[ii]=0;
		int row = -1;
		if(ind_and_or==0)
		{
			row = Result($4,0);
			for(int k = 0; k <= row ;k++)
	 			final_r[k] = results[k];
		}
		for(int o=0;o<ind_and_or;o++)
		{
			if(joiners[o]==0)
				continue;
			else
			{
				for(int ii=0;ii<100;ii++)
					and_r[ii]=1;
				while(joiners[o]==1)
				{
					for(int i=o; i<o+2; i++)
					{
						row = Result($4,i);
						for(int k = 0;k<=row;k++)
							and_r[k] *= results[k];
					}
					o++;
				}
				for(int k = 0; k <=row ;k++)
				final_r[k] |= and_r[k];
		 	}
		 }
		for(int o=0;o<ind_and_or;o++)
		{
			if(joiners[o]==1)
				continue;
			if(joiners[o]==0 && o==0)
			{
				row = Result($4,o);
	 			for(int k = 0; k <100;k++)
	 				final_r[k] |= results[k];
			}
			if(joiners[o]==0 && ((joiners[o+1]==0 && o+1<ind_and_or) || o==ind_and_or-1)) 
			{
				row = Result($4,o+1);
	 			for(int k = 0; k <100;k++)
	 				final_r[k] |= results[k];
			}		
		}
		Delete($4,final_r);
	};

SELECT: GET FIELDLIST FROM VAR WHERE CONDITIONS COLON {
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
	int and_r[100],final_r[100];
	for(int ii=0;ii<100;ii++)
		final_r[ii]=0;
	int row = -1;
	if(ind_and_or==0)
	{
		int row = Result($4,0);
		for(int k = 0; k <= row ;k++)
	 			final_r[k] = results[k];

	}
	for(int o=0;o<ind_and_or;o++)
	{
		if(joiners[o]==0)
			continue;
		else
		{
			for(int ii=0;ii<100;ii++)
				and_r[ii]=1;
			while(joiners[o]==1)
			{
				for(int i=o; i<o+2; i++)
				{
					row = Result($4,i);
					for(int k = 0;k<=row;k++)
						and_r[k] *= results[k];
				}
				o++;
			}
			for(int k = 0; k <=row ;k++)
				final_r[k] |= and_r[k];
	 	}
	 }
	 for(int o=0;o<ind_and_or;o++)
	 {
	 	if(joiners[o]==1)
	 		continue;
	 	if(joiners[o]==0 && o==0)
	 	{
	 		row = Result($4,o);
	 		for(int k = 0; k <100;k++)
	 			final_r[k] |= results[k];
	 	}
	 	if(joiners[o]==0 && ((joiners[o+1]==0 && o+1<ind_and_or) || o==ind_and_or-1)) 
	 	{
	 		row = Result($4,o+1);
	 		for(int k = 0; k <100;k++)
	 			final_r[k] |= results[k];
	 	}		
	 }
	 Select($4,final_r);
	};

UPD : UPDATE RECORD IN VAR SET VAR TO VALUE WHERE CONDITIONS COLON {
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
	int and_r[100],final_r[100];
	for(int ii=0;ii<100;ii++)
		final_r[ii]=0;
	int row = -1;
	if(ind_and_or==0)
	{
		int row = Result($4,0);
		for(int k = 0; k <= row ;k++)
	 			final_r[k] = results[k];
	}
	for(int o=0;o<ind_and_or;o++)
	{
		if(joiners[o]==0)
			continue;
		else
		{
			for(int ii=0;ii<100;ii++)
				and_r[ii]=1;
			while(joiners[o]==1)
			{
				for(int i=o; i<o+2; i++)
				{
					row = Result($4,i);
					for(int k = 0;k<=row;k++)
						and_r[k] *= results[k];
				}
				o++;
			}
			for(int k = 0; k <=row ;k++)
				final_r[k] |= and_r[k];
	 	}
	 }
	 for(int o=0;o<ind_and_or;o++)
	 {
	 	if(joiners[o]==1)
	 		continue;
	 	if(joiners[o]==0 && o==0)
	 	{
	 		row = Result($4,o);
	 		for(int k = 0; k <100;k++)
	 			final_r[k] |= results[k];
	 	}
	 	if(joiners[o]==0 && ((joiners[o+1]==0 && o+1<ind_and_or) || o==ind_and_or-1)) 
	 	{
	 		row = Result($4,o+1);
	 		for(int k = 0; k <100;k++)
	 			final_r[k] |= results[k];
	 	}		
	 }
	Update($4,final_r,$6);
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


JOINER: AND { joiner[ind_and_or++] = 1; }
		| OR { joiner[ind_and_or++] = 0; };

FIELDLIST: VAR FIELDLIST{strcpy(field_list[ind_field++],$1);}
		| VAR{strcpy(field_list[ind_field++],$1); };

VALUE : NUM {strcpy(update_string,$1);} | STRING {strcpy(update_string,$1);};
%%