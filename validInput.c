#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"

#define ANSI_RED "\x1b[31m"
#define ANSI_RESET "\x1b[0m"






int validWord(char *word,int size){
	int wordLength,i,tooLong = 0;
	
	//wordLength = (sizeof(word));
	
	for(i = 0; word[i] != '\0'; i++){
		tooLong++;
		if(tooLong >= size - 5){
			printf(ANSI_RED"\nName Too Long \n"ANSI_RESET);
			return 0;
		}
	}
	for(i = 0; i < size && word[i] != '\0'; i++){
	

		if(islower(word[i]) == 0 && isupper(word[i]) == 0){
			printf(ANSI_RED"\nInvalid Name \n"ANSI_RESET);
			
			return 0;
			}
			
	
	}
	
	return 1;

}








	


