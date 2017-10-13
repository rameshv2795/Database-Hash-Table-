#include <stdio.h>
#include <stdlib.h>

struct list{
	int key;
	int linkNumber;
	char *firstName;
	char *lastName;
	int age;
	struct list* next;

};

struct hashTable{
	int buckets,links;
	struct list** array;

};

struct hashTable* createHashTable();
void initHashTable(struct hashTable*,int);
int getBucket(struct hashTable* table);
int hashFunction(char*);
void addLink(struct hashTable* table,int,char*,char*,int);
void printTable(struct hashTable* table);
int hashFunction2(char *str);
int deleteLink(struct hashTable * table,int,char*);
void printName(struct list * person, int);
struct list* findPerson(struct hashTable * table, int k, char*); 
void saveList(struct hashTable* table);
void printNameToFile(struct list* person,int size,FILE *filept);
struct hashTable* loadDatabase();
int loadFactor(struct hashTable * table);