#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"


#define ANSI_GREEN "\x1b[32m"
#define ANSI_RED "\x1b[31m"
#define ANSI_RESET "\x1b[0m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_BOLD "\x1b[1m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_Uknown "\x1b[44m"
#define ANSI_REDBACK "\x1b[7m"
#define nameSize 80


void initChoice(char*);
int intChoiceValid(char*);
int intChoiceValid2(char*);
void databaseIntro();
void databaseOptions(struct hashTable*,int choice);
struct hashTable* load();


int main(){

	
	printf("\e[1;1H\e[2J"); //Not sure how this works (clears screen)
	
    /*               STARTS HERE            */
	////////////////////////////////////////////////////////////////////
	
	/*printf(ANSI_Uknown"1 - Load"ANSI_RESET "  " ANSI_Uknown"2 - New "ANSI_RESET "  " ANSI_Uknown"3 - Exit "ANSI_RESET ": ");
	scanf("%s",&addRemove);
	printf("\n");
	*/
	printf("\n");
	//printf("%d",getBucket(database));
	//addLink(database,hashFunction2(last),name,last);

	databaseIntro();

	//printName(findPerson(database,hashFunction2(name2),name2));
	
	//printf("    %d   ",hashFunction2(name));

	return 0;

}

void databaseIntro(){

	char choice[1];
	struct hashTable* database = NULL;
	
	printf(ANSI_Uknown"1 - Load"ANSI_RESET "  " ANSI_Uknown"2 - New "ANSI_RESET "  " ANSI_Uknown"3 - Quit "ANSI_RESET ": ");

	scanf("%c",choice);
	printf("\n");
	
	
	if(intChoiceValid2(choice) == 1){
		database = load();
		//printTable(database);
		databaseOptions(database,1);		
	}
	
	else if(intChoiceValid2(choice) == 2){
		
		database = createHashTable();
		initHashTable(database,4);
		
		databaseOptions(database,2);

	

	}




}

void databaseOptions(struct hashTable* database,int choice){
	
	FILE* fp;
	char *name = "Vinod";
	char *last = "Ramesh";
	char *name2 = "Tupac";
	char *last2 = "Shakur";
	char firstNameInput[nameSize],lastNameInput[nameSize],addRemove[1];
	int age;
	char *longName = "sdfsdffffffffffffffffaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaP";
	char *longLast = "find";
	char fileName[nameSize];
	char* path;
	
	if(choice == 2){ //If new database
	
		printf("File Name: ");
		scanf("%s",fileName);
		printf("\n");
		
		int d = mkdir(fileName, 0777); //Makes directory for rooms rwx-rwx-rwx
		//fp = fopen(fileName,"w");
		
		/* This all creates a directory with files for loading and saving*/	
		path = malloc(sizeof(char)*1000);
		strcpy(path,fileName);
		strcat(path,"/database"); //to make file in directory
		fp = fopen(path,"w");
		fclose(fp);
		free(path);
		path = malloc(sizeof(char)*1000);
		strcpy(path,fileName);
		strcat(path,"/load");		
		fp = fopen(path,"w");
		fclose(fp);	
		//initChoice(addRemove);

		//addLink(database,hashFunction2(last),name,last,20);
		//addLink(database,hashFunction2(last2),name2,last2,45);
		//addLink(database,hashFunction2(longLast),longName,longLast,83);
		chdir(fileName); //go into savefile directory 
		//char *name = "Vinod";
		
	}	
 while(1){
	 
	printf(ANSI_Uknown"1 - Add"ANSI_RESET "  " ANSI_Uknown"2 - Remove "ANSI_RESET "  " ANSI_Uknown"3 - Find "ANSI_RESET"  " ANSI_Uknown"4 - Quit(saves)"ANSI_RESET ": ");
	scanf("%s",&addRemove);
	printf("\n");
	

	if(intChoiceValid(addRemove) == 1){
		
		fp = fopen("load","a+");
		fprintf(fp,"\n");
		printf("Last Name: ");
		scanf("%s",lastNameInput);
		//printf("Array Number: %d \n",sizeof(lastNameInput));
		while(validWord(lastNameInput,80) == 0){
			
			printf("Last Name: ");
			scanf("%s",lastNameInput);
			
		}
			//free(lastNameInput);
		fprintf(fp,"%s\n",lastNameInput);//adding to load file
		
		printf("First Name: ");
		scanf("%s",firstNameInput);
		
		while(validWord(firstNameInput,80) == 0){
			
			printf("First Name: ");
			scanf("%s",firstNameInput);
			
		}
		fprintf(fp,"%s\n",firstNameInput);
		
		printf("Age: ");
		scanf("%d",&age);
		fprintf(fp,"%d\n;",age);
		//printf("%d  ",hashFunction2(firstNameInput) % 4);
		//printf("HERE");
		addLink(database,hashFunction2(lastNameInput),firstNameInput,lastNameInput,age);	
		printf(ANSI_GREEN"\nPerson successfully added \n\n"ANSI_RESET);
		fclose(fp);
		
		
	}
	
	else if(intChoiceValid(addRemove) == 2){
		
		printf("\nLast Name: ");
		scanf("%s",lastNameInput);
		if(deleteLink(database,hashFunction2(lastNameInput),lastNameInput) == 1)
			printf(ANSI_GREEN"\nPerson successfully deleted \n\n"ANSI_RESET);
		else
			printf(ANSI_RED"\nError: Person not in database \n\n"ANSI_RESET);
	
	}
 
	else if(intChoiceValid(addRemove) == 3) {
		//printTable(database);
		printf("Last Name: ");
		scanf("%s",lastNameInput);
		
		if(findPerson(database,hashFunction2(lastNameInput),lastNameInput) != NULL)
			printName(findPerson(database,hashFunction2(lastNameInput),lastNameInput),80);
		else
			printf(ANSI_RED"\nError: Person not in database \n\n"ANSI_RESET);
		
	
	}
	
	else if(intChoiceValid(addRemove) == 4) {

		//printTable(database);

		
		saveList(database); //Calls function to save hashtable
		printf("\nFile has been saved!\n\n");
		
		
		//fclose(fp);
		exit(0);	
		
		
	
	
	}
	
	else if(intChoiceValid(addRemove) == 0)
		printf(ANSI_RED"\nError: Invalid Command \n\n"ANSI_RESET);
	
	//printTable(database);

 }
	//printName(findPerson(database,hashFunction2(name),name),80);







}





void initChoice(char *array){

	int i;
	for(i = 0;i<3;i++){
	
		array[i] = '\0';
	}	

}

int intChoiceValid(char* choice){
	int i, inputNum;
	for(i = 0; i < 1; i++){
		if(isdigit(choice[i]) == 0){
			//printf(" HERE \n");
			return 0;
		}	
	}
	
	inputNum = atoi(choice);
	
	if(inputNum == 1)
		return 1;

	if(inputNum == 2)
		return 2;

	if(inputNum == 3)
		return 3;	
	
	if(inputNum = 4)
		return 4;

	return 0;
}

int intChoiceValid2(char* choice){
	int i, inputNum;
	for(i = 0; i < 1; i++){
		if(isdigit(choice[i]) == 0){
			//printf(" HERE \n");
			return 0;
		}	
	}
	
	inputNum = atoi(choice);
	
	if(inputNum == 1)
		return 1;

	if(inputNum == 2)
		return 2;

	if(inputNum == 3)
		return 3;	


	return 0;
}

struct hashTable* load(){
	
	
	char* path;
	char loadName[1000]; //constant string 
	struct hashTable* database = NULL;
	while(1){
	
	printf("File To Load: ");
	scanf("%s",loadName);
	

	if(chdir(loadName) == -1) //directory does not exist
		printf(ANSI_RED"\nError: Invalid Directory \n\n"ANSI_RESET);
	
	else
		break;
	
	}
	
	database = loadDatabase();
	
	return database;





}











