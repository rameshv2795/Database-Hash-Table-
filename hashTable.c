#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_RESET "\x1b[0m"
#define ANSI_CYAN "\x1b[36m"


int hashFunction(char * word){
	int i,intChar,total = 0,wordSize;
	wordSize = (sizeof(word))/(sizeof(char)) - 2;
	//printf("SIZE: %d \n",wordSize);
	for(i = 0; i < wordSize; i++){
		//printf("%c ",word[i]);
		intChar = word[i] - '0'; //Converts char to int
		total += intChar;
		//printf("%d",total);
		//printf(" %d", intChar);
		//printf("\n");
	}
	return total;
	//printf("TOTAL: %d",total);
}

int hashFunction2(char *str){
	int i;
	int r = 0;
	
	for (i = 0; str[i] != '\0'; i++){
		r += str[i];
		
	}	
	//printf("Hash Value: %d \n",r);
	//printf("Character: %c \n",*str);
	
	return r;

}

struct hashTable* createHashTable(){
	struct hashTable* h;
	h = malloc(sizeof(struct hashTable));
	return h;
}

void initHashTable( struct hashTable* table, int arraySize){
	int i;
	table -> array =  (struct list**)malloc(arraySize * (sizeof(struct list*)));
	table -> buckets = arraySize;
	table -> links = 0;
	for(i = 0; i < arraySize; i++){
		table -> array[i] = NULL;
		
	}
	
/*
	for(i=0; i<arraySize; i++){
		table -> array[i] = malloc(sizeof(struct list));
		table -> array[i] -> key = 23;
	}

	
	for(i=0; i<arraySize; i++){
		printf("%d",table -> array[i] -> key);
		printf(" ");
		
	}
	*/
}

int getBucket(struct hashTable* table){
	return table -> buckets;

}

void addLink(struct hashTable* table,int k,char*n,char*l,int years){
	int i;
	struct list* iter;
	k =   k % getBucket(table);

	for(i = 0; i < getBucket(table); i++){ 
	
	  if(i == k){
		if(table -> array[i] == NULL ){ //NO COLLISION
			table -> array[i] = malloc(sizeof(struct list));
			table -> array[i] -> next = NULL;
			table -> array[i] -> key = k;
			table -> array[i] -> firstName = n; 
			table -> array[i] -> lastName = l;
			table -> array[i] -> age = years;
			table -> links = table -> links++;
			//printf("In Database: %s\n",table -> array[i] -> lastName);
			
				
			//printf("HERE \n");
			break;
		}
		else if(table -> array[i] -> key == k){ //COLLISION
			iter = table -> array[i];
			while(1){
				if(iter -> next == NULL){
					iter -> next = malloc(sizeof(struct list));
					iter -> next -> next = NULL;
					iter -> next -> key = k;
					iter -> next -> firstName = n;
					iter -> next -> lastName = l;
					iter -> next -> age = years;
					table -> links = table -> links++;
					//printf("In Database: %s\n",iter -> next -> lastName);
					break;
				}
				else{
					iter = iter -> next;
				}
			
			}
			break;
		}
	  }		
	}


}

void printTable(struct hashTable* table){
	int i,arraySize;
	struct list* iter;
	arraySize = table -> buckets;
	
	printf("HASH TABLE: \n\n");
	
	for(i=0; i<arraySize; i++){
		if(table -> array[i] == NULL){
			printf("-> NULL \n");
		}
		else{
			iter = table -> array[i];
			while(1){
						
				if(iter -> next == NULL){
					//printf("HERE \n");
					printf("-> %d ",table -> array[i] -> key);
					//printf("Name: %s\n",table -> array[i] -> firstName);
					break;
				}	
				else{
					//printf("HERE \n");
					printf("-> %d ",iter -> next -> key);
					//printf("Name: %s\n",iter -> next -> firstName);
					iter = iter -> next;
				}
				
					
			}
			printf("\n");
		
		}
		
	}

}

int deleteLink(struct hashTable * table, int k, char *first){

	int i,behind = 0;
	k = k % getBucket(table);
	struct list* iter = table -> array[k];
	struct list* iterBefore = iter; //Points behind iter so can go back
	
	
	while(1){
		if(iter == NULL){
			//printf("\n NOT IN DATABASE \n");
			return 0;
		}
		
		else{
			if(strcmp(iter -> lastName, first) == 0 ){
				if(behind > 0){
					iterBefore -> next = iter -> next;
					free(iter);
				}
				else{
					table -> array[k] = iter -> next;
					free(iter);
					
				}
				return 1;
			}
			else{
				iter = iter -> next;
				if(behind > 0){ //If not at beginning of collision
					iterBefore = iterBefore -> next; 
				}
				behind++;
			}
		}
	
	}

	

}

//STILL NEED TO TEST AND COMPLETE THIS FUNCTION
void printName(struct list* person,int size){
	int i,arrayLength;
	
	arrayLength = (sizeof(person -> lastName))/(sizeof(char)) - 2;
	printf("\nName: ");
	for(i = 0; i < size && person -> lastName[i] != '\0' ; i++){
		printf(ANSI_CYAN "%c"ANSI_RESET,person -> lastName[i]);
	}
	arrayLength = sizeof(person -> firstName);
	
	 //printf(" %d ",arrayLength);
	printf(", ");
	
	
	for(i = 0; i < size && person -> firstName[i] != '\0' ; i++){
		printf( ANSI_CYAN "%c"ANSI_RESET,person -> firstName[i]);
	}
	
	

	printf("\n");
	
	printf( "Age: " ANSI_CYAN"%d"ANSI_RESET, person -> age);
		
	
	printf("\n\n");
	
	
}

struct list* findPerson(struct hashTable * table, int k, char *first){ //return struct list?
	int i;
	k = k % getBucket(table);
//	printf("SEARCH: %d\n",k);
	struct list* iter = table -> array[k];
	
	while(iter != NULL){
	//	printf("In Search: %s\n",table -> array[k] -> lastName);
		if(strcmp(iter -> lastName, first) == 0 ){
			
			//printf("\n IN DATABASE!!! \n");
			return iter;
		}
		
		else{
	//	printf("Find Last: %c\n",iter -> lastName[0]);

			iter = iter -> next;
				
		}
		
	
	}
	//printf("NOT IN DATABASE... \n");
	return iter;

}

void saveList(struct hashTable* table){
	
	int i,arraySize;
	struct list* iter;
	arraySize = table -> buckets;
	FILE *filep;
	filep = fopen("database","a+");
	printf("HASH TABLE: \n\n");
	
	for(i=0; i<arraySize; i++){
		if(table -> array[i] == NULL){
		//	fprintf(file,"-> NULL \n");
		}
		else{
			iter = table -> array[i];
			while(1){
						
				if(iter -> next == NULL){
					//printf("HERE \n");
					//fprintf(file,"-> %d ",table -> array[i] -> key);
					//printNameToFile(table -> array[i],80,file); WAS THERE!!!!!
					break;
				}	
				else{
					//printf("HERE \n");
					//fprintf(file,"-> %d ",iter -> next -> key);
		//			printNameToFile(iter -> next,80,file); WAS THERE!!!!!
					iter = iter -> next;
				}
				
					
			}
			//fprintf(file,"\n"); WAS THERE!!!!!
		
		}
		
	}
	
	fclose(filep);
}

void printNameToFile(struct list* person,int size,FILE *file){ //Helper function for saveList
	int i,arrayLength;
	
	//arrayLength = (sizeof(person -> lastName))/(sizeof(char)) - 2;
	fprintf(file,"\nName: ");
	for(i = 0; i < size && person -> lastName[i] != '\0' ; i++){
		fprintf(file,"%c",person -> lastName[i]);
	}
	//arrayLength = sizeof(person -> firstName);
	
	 //printf(" %d ",arrayLength);
	fprintf(file,", ");
	
	
	for(i = 0; i < size && person -> firstName[i] != '\0' ; i++){
		fprintf(file,"%c",person -> firstName[i]);
	}
	
	

	fprintf(file,"\n");
	
	fprintf(file, "Age: " "%d", person -> age);
		
	
	fprintf(file,"\n\n");
	
	
}

struct hashTable* loadDatabase(){
	FILE *fp;
	int first = 1,whichText = 0;
	char buffer[80];
	char *fname,*lname,*ageHolder;
	struct hashTable* database = NULL;
	database = createHashTable();
	initHashTable(database,4);
	
	fp = fopen("load","a+");
	
	
	
	while(fgets(buffer,80,fp) != NULL){ //iterate through load file
		 
		if(first != 1 && buffer[0] != '\n'){
			strtok(buffer, "\n"); //remove new line

			if(whichText == 0){
				
				lname = malloc(sizeof(char)*80);
				strcpy(lname,buffer);
				
				whichText++;
			}
			
			else if(whichText == 1){
			
				fname = malloc(sizeof(char)*80);
				strcpy(fname,buffer);
				
				whichText++;
			}			
			
			else if(whichText == 2){
			
				ageHolder = malloc(sizeof(char)*80);
				strcpy(ageHolder,buffer);
			//	printf("Age: %s",ageHolder);
				whichText++;
			}
			
			else if(whichText == 3){ //all data gathered
				int age = atoi(ageHolder);
			//	printf("HERE!!\n");
				addLink(database,hashFunction2(lname),fname,lname,age);
				whichText = 0;
			//	printf("HASH:%d\n",hashFunction2(lname));
			//	printf("LAST:%s\n",lname);			
				lname = NULL;
				fname = NULL;
				ageHolder = NULL;

			}			
			
			
			
		}
		
		else //Skip first line of file
			first = 0;
	
	}
	

	fclose(fp);
	return database;
}

int loadFactor(struct hashTable * table){ // number entries / number buckets

	return (table -> links) / (table -> buckets); 


}

void copyToNewMap(struct hashTable * table){

	struct hashTable * newMap = createHashTable();
	//initHashTable(newMap, loadFactor(hashTable));
	
	
	

}



















