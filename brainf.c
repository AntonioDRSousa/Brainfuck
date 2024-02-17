#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void tab(FILE * fp,int ind){
	int i;
	for(i=0;i<ind;i++){
		fprintf(fp,"\t");
	}
}

void error(FILE * fp1, FILE * fp2, char * name){
	fclose(fp1);
	fclose(fp2);
	remove(name);
	exit(0);
}

void comp(char * name1, char * name2){
	FILE * fp1;
	FILE * fp2;
	
	strcat(name2,".c");
	
	fp1 = fopen(name1,"r");
	fp2 = fopen(name2,"w");
	
	if(!fp1){
		printf("There isn't file with this name .....\n");
		error(fp1,fp2,name2);
	}
	
	fprintf(fp2,"#include<stdio.h>\n");
	fprintf(fp2,"#include<stdlib.h>\n\n");
	fprintf(fp2,"int main(){\n");
	fprintf(fp2,"\tint p = 0;\n");
	fprintf(fp2,"\tchar* v = (char*) calloc(30000,sizeof(char));\n\n");
	
	int ind = 1;
	int np = 0;
	char c;
	
	do{
		c = fgetc(fp1);
		switch(c){
			case '>':
				tab(fp2,ind);
				fprintf(fp2,"p++;\n");
				np++;
				break;
			case '<':
				tab(fp2,ind);
				fprintf(fp2,"p--;\n");
				np--;
				break;
			case '+':
				tab(fp2,ind);
				fprintf(fp2,"v[p]++;\n");
				break;
			case '-':
				tab(fp2,ind);
				fprintf(fp2,"v[p]--;\n");
				break;
			case '.':
				tab(fp2,ind);
				fprintf(fp2,"putchar(v[p]);\n");
				break;
			case ',':
				tab(fp2,ind);
				fprintf(fp2,"v[p] = getchar();\n");
				break;
			case '[':
				tab(fp2,ind);
				fprintf(fp2,"while(v[p]){\n");
				ind++;
				break;
			case ']':
				ind--;
				tab(fp2,ind);
				fprintf(fp2,"}\n");
				break;
		}
		if((np<0)||(np>=30000)){
			printf("Compilation Error. Pointer access invalid section ...\n");
			error(fp1,fp2,name2);
		}
	}while(c!=EOF);
	
	if(ind!=1){
		printf("Compilation Error. There isn't equal number of '[' and ']' ...\n");
		error(fp1,fp2,name2);
	}
	
	fprintf(fp2,"\n\treturn 0;\n}\n");
}

void help(){
	printf("-------------------------------\n");
	printf("brainf -> print brainf\n");
	printf("brainf h -> help\n");
	printf("brainf c <name1.bf> <name2> -> compile name1.bf to name2.c\n");
	printf("brainf c <name1.bf> -> compile name1.bf to name1.c\n");
	printf("-------------------------------\n");
}

int main(int argc, char * argv[]){
	if(argc==1){
		printf("brainf");
	}
	else if(argc==2){
		if(strcmp(argv[1],"h")==0){
			help();
		}
	}
	else if(argc==3){
		if(strcmp(argv[1],"c")==0){
			printf("compilar");
			comp(argv[2],argv[2]);
		}
	}
	else if(argc==4){
		if(strcmp(argv[1],"c")==0){
			comp(argv[2],argv[3]);
		}
	}
	return 0;
}