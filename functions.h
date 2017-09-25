#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

typedef enum attributes {
	ARTIST, SONGTITLE, ALBUM, GENRE, RATE
} Attribute;
typedef struct duration {
	int min;
	int sec;
} Duration;

typedef struct record {
	char artist[40];
	char album[40];
	char songTitle[40];
	char genre[40];
	Duration length;
	int timesPlayed;
	int rate;
	int played;
} Record;

typedef struct node {
	Record data;
	struct node* pNext;
	struct node* pPrevious;
} Node;

typedef struct nodeShuffle {
	int order;
	struct nodeShuffle* pNext;
	struct nodeShuffle* pPrevious;
} nodeShuffle;

//Main functions
int printMainMenu(void);
int promptOption(void);
void chooseOption(Node** pHead, int option);
void load(Node** pHead);
void insertNewSong(Node** pHead);
void store(Node* pHead);
void display(Node* pHead);
void edit(Node* pHead);
void rate(Node* pHead);
void sort(Node** pHead);
void play(Node* pHead);
void deleteSong(Node** pHead);
void shuffle(Node* pHead);
void exitProgram(void);


//Helping functions
void insertNodeFront(Node** pHead, Node* pNew);
Node* makeNode(char* data);
void sortAlbum(Node** pHead);
void sortArtist(Node** pHead);
void sortTimesPlayed(Node** pHead);
void sortRate(Node** pHead);
void printAllRecords(Node* pHead);
int printByArtist(Node* pHead, char* artist);
Node* findSong(Node* pHead, char* input, int titleOrArtist);
void printAllRecords(Node* pHead);
void editSpecific(Node* pHead, Attribute Edited, char* edit, int rate);
nodeShuffle* shuffleLinkedList(int size);