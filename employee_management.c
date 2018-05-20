#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RED 	"\x1B[31m"
#define RESET 	"\x1B[0m"
typedef struct Employee{
	char empid[20];
	char fname[20];
	char lname[20];
	int age;
	float bsal;
	long phone;
}Employee;
FILE *fp;
Employee emp;
char filename[]="emp.dat";
char tempfilename[]="temp.dat";
void addemployee();
void listemployee();
void searchemployee();
void modifyemployee();
void deleteemployee();
void first();
char file();
void main(){
	char ch='a';
	system("clear");
	first();
	fp=fopen(filename,"r+");
	if(fp==NULL){
		fp=fopen(filename,"w+");
		if(fp==NULL){
			printf("cannot open file\n");
			exit(1);
		}
	}
	while(ch){
		ch=file();
		switch(ch){
			case '1':
				addemployee();
				break;
			case '2':
				listemployee();
				break;
			case '3':
				searchemployee();
				break;
			case '4':
				modifyemployee();
				break;
			case '5':
				deleteemployee();
				break;
			case '6':
				system("clear");
				exit(0);
			default:
				printf("wrong choice\n");
				printf("press enter to continue\n");
				getchar();
				break;
		}
	}
}
void first(){
	char i;
	printf(RED " \t\t\t\temployee information system\n" RESET);
	printf(RED "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\npress enter to continue\n" RESET);
}
char file(){
	char i;
	getchar();
	system("clear");
	printf(" \t\t\t\temployee information system\n\n");
	printf("main menu\n\n\n");
	printf("1.add employee record\n");
	printf("2.list employee record\n");
	printf("3.search employee\n");
	printf("4.modify employee\n");
	printf("5.delete employee\n");
	printf("6.exit this program\n");
	printf("\n\nenter your choice\n");
	i=getchar();
	return i;
}
void addemployee(){
	char another,ch;
	char employeeid[20]={0};
	do{
		system("clear");
		fseek(fp,0,SEEK_END);
		printf(" \t\t\t\tadd employee record\n");
		getchar();
		printf("1.enter employee id:\n");
		fgets(employeeid,20,stdin);
		fseek(fp,0,SEEK_SET);
		while(fread(&emp,sizeof emp,1,fp)==1){
			if(strcmp(emp.empid,employeeid)==0){
				printf("record exists\n");
				printf("press enter to continue\n");
				getchar();
				main();
				exit(0);
			}
		}
		strncpy(emp.empid,employeeid,20);
		printf("2.enter employee first name:\n");
		fgets(emp.fname,20,stdin);
		printf("3.enter employee last name:\n");
		fgets(emp.lname,20,stdin);
		printf("4.enter employee age:\n");
		scanf("%d",&emp.age);
		printf("5.enter employee salary:\n");
		scanf("%f",&emp.bsal);
		printf("6.enter employee phone number:\n");
		scanf("%ld",&emp.phone);
		printf("save change (y/n)?\n");
		getchar();
		ch=getchar();
		if(ch=='y'||ch=='Y')
			fwrite(&emp,sizeof emp,1,fp);
		getchar();
		printf("add another employee(y/n)?\n");
		another=getchar();
	}while(another=='y'||another=='Y');
}
void listemployee(){
	int i;
	system("clear");
	fseek(fp,0,SEEK_SET);
	for(i=0;i<=79;i++)
		printf("-");
	printf(" \t\t\t\tlist of employee record:\n");
	for(i=0;i<=79;i++)
		printf("-");
	while(fread(&emp,sizeof emp,1,fp)==1){
		printf("employee id:\t %s",emp.empid);
		printf("first name:\t %s",emp.fname);
		printf("last name:\t %s",emp.lname);
		printf("age:\t\t %d\n",emp.age);
		printf("salary:\t\t %.2f\n",emp.bsal);
		printf("phone:\t\t %ld\n",emp.phone);
	}
	printf(" \n\n\t\t\t\tpress enter to continue\n");
	getchar();
}
void searchemployee(){
	int datafound=0;
	char employeeid[20];
	char another;
	do{
		system("clear");
		fseek(fp,0,SEEK_SET);
		printf("search employee record\n");
		printf("enter employee id:");
		getchar();
		fgets(employeeid,20,stdin);
		while(fread(&emp,sizeof emp,1,fp)==1){
			datafound=0;
			if(strcmp(emp.empid,employeeid)==0){
				datafound=1;
				break;
			}
		}
		if(datafound==1){
			printf("employee record\n");
			printf("-----------------\n");
			printf("employee id: %s",emp.empid);
			printf("first name: %s",emp.fname);
			printf("last name: %s",emp.lname);
			printf("age: %d\n",emp.age);
			printf("basic salary: %.2f\n",emp.bsal);
			printf("phone: %ld\n",emp.phone);
		}else
			printf("no record\n");
		printf("search another employee(y/n)\n");
		another=getchar();
	}while(another=='y'||another=='Y');
}

void modifyemployee(){
	int datafound=0,recordno=0;
	char employeeid[20];
	char another;
	do{
		system("clear");
		fseek(fp,0,SEEK_SET);
		printf("modify employee\n");
		printf("enter employee id:");
		getchar();
		fgets(employeeid,20,stdin);
		while(fread(&emp,sizeof emp,1,fp)==1){
			datafound=0;
			if(strcmp(emp.empid,employeeid)==0){
				datafound=1;
				break;
			}
			recordno++;
		}
		if(datafound==1){
			printf("old record is\n\n");
			printf("employee id: %s",emp.empid);
			printf("first name: %s",emp.fname);
			printf("last name: %s",emp.lname);
			printf("age: %d\n",emp.age);
			printf("salary: %.2f\n",emp.bsal);
			printf("phone: %ld\n\n\n",emp.phone);
			printf("please enter new record\n");
			printf("employee id:");
			fgets(emp.empid,20,stdin);
			printf("first name:");
			fgets(emp.fname,20,stdin);
			printf("last name:");
			fgets(emp.lname,20,stdin);
			printf("age:");
			scanf("%d",&emp.age);
			printf("salary:");
			scanf("%f",&emp.bsal);
			printf("phone:");
			scanf("%ld",&emp.phone);
			fseek(fp,sizeof(emp)*(recordno),SEEK_SET);
			if(fwrite(&emp,sizeof emp,1,fp)==1){
				printf("modified\n");
				getchar();
			}else
				printf("error\n");
		}else
			printf("no record\n");
		printf("modify another employee(y/n)\n");
		another=getchar();
	}while(another=='y'||another=='Y');
}
void deleteemployee(){
	int datafound=0;
	char employeeid[20];
	FILE *fptemp;
	char another;
	do{
		system("clear");
		fseek(fp,0,SEEK_SET);
		printf("delete employee record\n\n");
		getchar();
		printf("enter employee id:");
		fgets(employeeid,20,stdin);
		while(fread(&emp,sizeof emp,1,fp)==1){
			datafound=0;
			if(strcmp(emp.empid,employeeid)==0){
				datafound=1;
				break;
			}
		}
		if(datafound==1){
			fptemp=fopen(tempfilename,"wb+");
			rewind(fp);
			while(fread(&emp,sizeof emp,1,fp)==1){
				if(strcmp(emp.empid,employeeid)!=0)
					fwrite(&emp,sizeof emp,1,fptemp);
			}
			fclose(fp);
			fclose(fptemp);
			remove(filename);
			rename(tempfilename,filename);
			fp=fopen(filename,"r+");
			printf("deleted\n");
		}else
			printf("no record\n");
		printf("delete another record(y/n)\n");
		another=getchar();
	}while(another=='y'||another=='Y');

}
