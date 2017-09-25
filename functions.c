#include "functions.h"
/*Prints main menu and calls function promptOption,
gets back an int and returns it.*/
int printMainMenu(void)
{
	int option = 0;
	puts("(1) Load");
	puts("(2) Store");
	puts("(3) Display");
	puts("(4) Insert");
	puts("(5) Delete");
	puts("(6) Edit");
	puts("(7) Sort");
	puts("(8) Rate");
	puts("(9) Play");
	puts("(10) Shuffle");
	puts("(11) Exit");
	option = promptOption();
	return option;
}
/*This function prompts the user for the option they would like to choose*/
int promptOption(void)
{
	int option = 0, valid = 0;
	
	printf("Enter the number of an option:\n");
	scanf("%d", &option);
	if (option > 0 && option < 12)
		valid = 1;
	while (!valid)
	{
		printf("Please enter a number 1- 11:\n");
		scanf("%d", &option);
		if (option > 0 && option < 12)
			valid = 1;
	}
	return option;
}
/*This function uses the user's input to decide which function it should use.
Takes a pointer to a pointer to a Node, and an int as parameters. It doesn't 
return anything.*/
void chooseOption(Node** pHead, int option)
{
	switch (option)
	{
	case 1:
		load(pHead);
		break;
	case 2:
		store(*pHead);
		break;
	case 3: 
		display(*pHead);
		system("pause");
		break;
	case 4:
		insertNewSong(pHead);
		break;
	case 5: 
		deleteSong(pHead);
		break;
	case 6:
		edit(*pHead);
		break;
	case 7:
		sort(pHead);
		break;
	case 8:
		rate(*pHead);
		break;
	case 9:
		play(*pHead);
		break;
	case 10:
		shuffle(*pHead);
		break;
	case 11:
		exitProgram();
		break;
	default:
		break;
	}
	system("cls");
	chooseOption(pHead, printMainMenu()); // returns to the function that prints menu out and asks user for input
}
/*Stores all of the data in an excel file into a linked list.
Takes a pointer to a pointer to a Node as parameter and doesn't
return anything.*/
void load(Node** pHead)
{
	FILE* infile = fopen("musicPlayList.csv", "r");
	char temp1[80] = { '\0' };
	Node* pTemp = NULL;
	if (infile == NULL) //If file is not successfully opened, an error message will be displayed
	{
		printf("Error opening file.");
		system("pause");
		printMainMenu();
	}
	
	//Grabbing each line from the file one by one and adding it to the linked list
	while (fgets(temp1, 80, infile) != NULL)
	{
		pTemp = makeNode(temp1); //Creating new node, passing in String to be read and stored into Node
		insertNodeFront(pHead, pTemp); // Parameters are head of list as well as pointer to the newly created node
	}
	
}
/*Connects a new node to a linked list by pointing its pNext to 
the head, followed by pointing the pPrevious of head to the New Node.
Finally, it points the pointer to Head to the new node. It takes
in a pointer to a pointer to a Node and a pointer to a Node as parameters
and doesn't return anything.It is called by the load() function*/
void insertNodeFront(Node** pHead, Node* pNew)
{
	if (*pHead == NULL)
	{
		*pHead = pNew;//Setting pHead to point to the new Node
	}
	else {
		pNew->pNext = *pHead; //pointing pNext of new Node to the beginning of the list
		(*pHead)->pPrevious = pNew; //pointing pPrevious of first node of list to new Node
		*pHead = pNew;//Setting pHead to point to the new Node
	}
}
/*This function creates each individual Node and stores all of the info read from each
line into each Node. It takes a string of characters, representing the data read in,
as a parameter and returns a pointer to a Node*/
Node* makeNode(char* data)
{
	int numCommas = 0, i1 = 0, i2 = 0;
	Node* ptemp1 = (Node*)malloc(sizeof(Node));
	ptemp1->pNext = NULL;
	ptemp1->pPrevious = NULL; 
	char first[20] = { 0 }, last[20] = { 0 };

	while (data[i1] != NULL) //Counting commas
	{
		if (data[i1] == ',')
			numCommas++;
		i1++;
	}
	/*If there are more than six commas, it means the formas of artist is Last, First Name.
	Because of this a two while loops are used to store the first and last name into to different
	character arrays. Then at the end, the last name is concatanated to the first. Then it is
	stored into the songTitle section of the Node. Finally, two strtok() are used to skip
	the first and last name.*/
	if (numCommas > 6) 
	{
		i1 = 0;
		while (data[i1] != ',')
		{
			if (data[i1] != '"')
			{
				last[i2] = data[i1];
				i2++;
			}
			i1++;
		}
		i1++;
		i2 = 0;
		while (!(data[i1] == ',' && data[i1 + 1] != ' '))
		{
			if (data[i1] != '"' && data[i1] != ' ')
			{
				first[i2] = data[i1];
				i2++;
			}
			i1++;
		}
		first[i2] = ' ';
		strcat(first, last);
		strcpy(ptemp1->data.artist, first);
		strtok(data, ",");
		strtok(NULL, ",");
	}
	else //If there are exactly 6 commas, the first strtok will be stored
	{
		strcpy(ptemp1->data.artist, strtok(data, ","));
	}
	strcpy(ptemp1->data.album, strtok(NULL, ","));
	strcpy(ptemp1->data.songTitle, strtok(NULL, ","));
	strcpy(ptemp1->data.genre, strtok(NULL, ","));
	ptemp1->data.length.min = atoi(strtok(NULL, ":"));
	ptemp1->data.length.sec = atoi(strtok(NULL, ","));
	ptemp1->data.timesPlayed = atoi(strtok(NULL, ","));
	ptemp1->data.rate = atoi(strtok(NULL, ","));
	ptemp1->data.played = 0;
	return ptemp1;
}
/*This function opens a .csv file to write all of the information within the linked list 
to it. It takes in a pointer to a Node as a parameter and doesn't retrun anything.*/
void store(Node* pHead)
{
	FILE* outfile = fopen("musicPlayList.csv", "w"); //Open file to write to
	char artistTemp[40] = { NULL };
	int i = 0, i2 = 0, printed = 0;
	
	while (pHead->pNext != NULL) //Points local head at end of list so that data is stored in the same order it was loaded
	{
		pHead = pHead->pNext;
	}

	while (pHead != NULL)
	{
		printed = 0;
		i = 0;
		i2 = 0;
		strcpy(artistTemp, "\0");
		while (pHead->data.artist[i] != NULL)//This algorithm modifies an artist with TWO names, back to the format it was loaded in
		{
			if (pHead->data.artist[i] == ' ')
			{
				while (pHead->data.artist[i] != NULL)
				{
					artistTemp[i2] = pHead->data.artist[i];
					i++;
					i2++;
				}
				i = 0;
				artistTemp[i2] = ',';
				i2++;
				artistTemp[i2] = ' ';
				i2++;
				while (pHead->data.artist[i] != ' ')
				{
					artistTemp[i2] = pHead->data.artist[i];
					i++;
					i2++;
				}
				fprintf(outfile, "\"%s\"", artistTemp); // quotation marks signify using only ONE box in excel
				printed = 1;
			}
			i++;
		}
		if (printed == 0) //this function prints name out to the file if it is only one word, 
		{
			fprintf(outfile, "%s", pHead->data.artist);
		}
		fprintf(outfile, ",%s,%s,%s,", pHead->data.album, pHead->data.songTitle, pHead->data.genre);
		fprintf(outfile, "%d:%d,%d,%d\n", pHead->data.length.min, pHead->data.length.sec, pHead->data.timesPlayed, pHead->data.rate);
		pHead = pHead->pPrevious; // moving through list
	}
}
/*This function prompts the user for whether they want to display all
of the songs or by specific artist. Depending on the choice, two different
functions could be called. Takes in a pointer to a Node and doesn't return anything.*/
void display(Node* pHead)
{
	int option = 0;
	char artist[40] = { NULL };
	system("cls");

	printf("(1) Display all items\n(2) Display all items by artist\n");
	scanf("%d", &option);
	while (option > 2 || option < 1)
	{
		printf("Please choose either 1 or 2:\n");
		scanf("%d", &option);
	}
	if (option == 1)
	{
		printAllRecords(pHead);
	}
	else {
		printByArtist(pHead, artist);
	}
}
/*This function transverses through list and prints all records. Takes pointer to Node
as parameter and doesn't return anything.*/
void printAllRecords(Node* pHead)
{
	system("cls");
	while (pHead != NULL)
	{
		printf("Artist: %s\n", pHead->data.artist);
		printf("Album: %s\n", pHead->data.album);
		printf("Title: %s\n", pHead->data.songTitle);
		printf("Genre: %s\n", pHead->data.genre);
		if (pHead->data.length.sec < 10)
		{
			printf("Duration: %d:0%d\n", pHead->data.length.min, pHead->data.length.sec);
		}
		else {
			printf("Duration: %d:%d\n", pHead->data.length.min, pHead->data.length.sec);
		}
		printf("Times Played: %d\n", pHead->data.timesPlayed);
		printf("Rate: %d\n", pHead->data.rate);
		printf("------------------------------\n");
		pHead = pHead->pNext;
	}
}
/*This function prompts the user for the name of an artist
and prints out info for all the songs that match the artist. 
Takes in a pointer to a Node as a parameter and doesn't return
anything.*/
int printByArtist(Node* pHead, char* artist)
{
	char temp[40];
	int found = 0, counter = 0;
	system("cls");
	printf("Type the name of the artist:\n");
	getchar();
	gets(temp);
	strcpy(artist, temp);
	system("cls");

	while (findSong(pHead, temp, ARTIST) != NULL)
	{ 
		pHead = findSong(pHead, temp, 0);
		printf("Artist: %s\n", pHead->data.artist);
		printf("Album: %s\n", pHead->data.album);
		printf("Title: %s\n", pHead->data.songTitle);
		printf("Genre: %s\n", pHead->data.genre);
		if (pHead->data.length.sec < 10)
		{
			printf("Duration: %d:0%d\n", pHead->data.length.min, pHead->data.length.sec);
		}
		else {
			printf("Duration: %d:%d\n", pHead->data.length.min, pHead->data.length.sec);
		}
		printf("Times Played: %d\n", pHead->data.timesPlayed);
		printf("Rate: %d\n", pHead->data.rate);
		printf("------------------------------\n");
		pHead = pHead->pNext;
		counter++;
		found = 1;
	}
	if (found == 0)
	{
		printf("No songs matched that artist.\n");
	}
	return counter;
}
/*Transverses list and returns a pointer to Node if a song that matches the 
input is found. Takes in a array of character an pointer to a pointer as
parameters.*/
Node* findSong(Node* pHead, char* input, int titleOrArtist)
{
	int i1 = 0;
	if (titleOrArtist == 0)
	{
		char artistTemp[40] = { NULL }; //To store a copy of the artist name in each node 
										//in order to not modify the original when converting to lower case
		while (input[i1] != NULL)
		{
			if (isalnum(input[i1])) //If character is alphanum it will be changed to lowercase
			{
				input[i1] = tolower(input[i1]);
			}
			i1++;
		}
		while (pHead != NULL)
		{
			i1 = 0;
			strcpy(artistTemp, pHead->data.artist); //copies name of artist into temp
			while (artistTemp[i1] != NULL)
			{
				artistTemp[i1] = tolower(artistTemp[i1]); //Turns every letter of the temp artist to lowercase
				i1++;
			}
			if (strcmp(input, artistTemp) == 0) //compares artist entered by user to artist in each node(each song)
			{
				return pHead; //returns a pointer to the node if it is the desired artist
			}
			pHead = pHead->pNext; //goes on to next pointer if artist doesnt match
		}
		return pHead; //returning a pointer to NULL
	}
	else //Same as if statement except this is in the case the search is with the title of song instead of the artist
	{
		char titleTemp[40] = { NULL };

		while (input[i1]!= NULL)
		{
			if (isalnum(input[i1]))
			{
				input[i1] = tolower(input[i1]);
			}
			i1++;
		}
		while (pHead != NULL)
		{
			i1 = 0;
			strcpy(titleTemp, pHead->data.songTitle);
			while (titleTemp[i1] != NULL)
			{
				if (isalnum(titleTemp[i1]))
				{
					titleTemp[i1] = tolower(titleTemp[i1]);
				}
				i1++;
			}
			if (strcmp(input, titleTemp) == 0)
			{
				return pHead;
			}
			pHead = pHead->pNext;

		}
		return pHead;
	}
}
/*This function prompts user for type of sort they would like to implement. Then,
depending on what the user chooses, a specific function to the chosen sort is
called. This function takes a double pointer to a Node as a parameter and
doesn't return anything.*/
void sort(Node** pHead)
{
	system("cls");
	int option = 0;
	printf("What would you like to sort by?\n(1)Artist\n(2)Album\n(3)Rate\n(4)Times played\n");
	scanf("%d", &option);
	while (option > 5 || option < 1)
	{
		printf("Please enter a number 1-4.\n");
		scanf("%d", &option);
	}
	switch (option)
	{
	case 1:
		sortArtist(pHead);
		break;
	case 2:
		sortAlbum(pHead);
		break;
	case 3:
		sortRate(pHead);
		break;
	case 4:
		sortTimesPlayed(pHead);
		break;
	}
	
}
/*Sorts by Rate and takes a double pointer to a Node as a parameter, but 
doesnt return anything.*/
void sortRate(Node** pHead)
{
	Node* pPrev = NULL, *pCur = *pHead, *pNext = NULL;
	int counter = 0;

	while (pCur != NULL) // counting songs in list to see how many sorts are needed
	{
		counter++;
		pCur = pCur->pNext;
	}
	if (counter == 1) //If there is only one song, there is no need to sort
	{
		return;
	}
	for (int i1 = 0; i1 < counter - 1; i1++) //Bubble sort-like implementation
	{
		pCur = *pHead; pPrev = pCur->pPrevious; pNext = pCur->pNext;
		for (int i2 = 0; i2 < counter - 1; i2++)
		{
			if (pCur->data.rate < pNext->data.rate)
			{
				pCur->pPrevious = pNext;
				pCur->pNext = pNext->pNext;
				if (pNext->pNext != NULL)
				{
					pNext->pNext->pPrevious = pCur;
				}
				pNext->pNext = pCur;

				if (pPrev != NULL)
				{
					pPrev->pNext = pNext;
					pNext->pPrevious = pPrev;
					pPrev = pNext;
				}
				else {
					pNext->pPrevious = NULL;
					pPrev = pNext;
					*pHead = pNext;
				}
				pNext = pCur->pNext;
			}
			else
			{
				pPrev = pCur;
				pCur = pCur->pNext;
				pNext = pCur->pNext;
			}
		}
	}
}
/*Sorts by Times Played and takes a double pointer to a Node as a parameter, but 
doesnt return anything.*/
void sortTimesPlayed(Node** pHead)
{
	Node* pPrev = NULL, * pCur = *pHead, *pNext = NULL;
	int counter = 0;
	
	while (pCur != NULL) // counting songs in list to see how many sorts are needed
	{
		counter++;
		pCur = pCur->pNext;
	}
	if (counter == 1) //If there is only one song, there is no need to sort
	{
		return;
	}
	for (int i1 = 0; i1 < counter - 1; i1++) //Bubble sort-like implementation
	{
		pCur = *pHead; pPrev = pCur->pPrevious; pNext = pCur->pNext;
		for (int i2 = 0; i2 < counter - 1; i2++)
		{
			if (pCur->data.timesPlayed < pNext->data.timesPlayed)
			{
				pCur->pPrevious = pNext;
				pCur->pNext = pNext->pNext;
				if (pNext->pNext != NULL)
				{
					pNext->pNext->pPrevious = pCur;
				}
				pNext->pNext = pCur;

				if (pPrev != NULL)
				{
					pPrev->pNext = pNext;
					pNext->pPrevious = pPrev;
					pPrev = pNext;
				}
				else {
					pNext->pPrevious = NULL;
					pPrev = pNext;
					*pHead = pNext;
				}
				pNext = pCur->pNext;
			}
			else
			{
				pPrev = pCur;
				pCur = pCur->pNext;
				pNext = pCur->pNext;
			}
		}
	}
}
/*Sorts by Artist and takes a double pointer to a Node as a parameter, but
doesnt return anything.*/
void sortArtist(Node** pHead)
{
	Node* pPrev = NULL, *pCur = *pHead, *pNext = NULL;
	char temp1[40] = { NULL }, temp2[40] = { NULL };
	int counter = 0, i3 = 0;

	while (pCur != NULL) // counting songs in list to see how many sorts are needed
	{
		counter++;
		pCur = pCur->pNext;
	}
	if (counter == 1) //If there is only one song, there is no need to sort
	{
		return;
	}
	for (int i1 = 0; i1 < counter - 1; i1++) //Bubble sort-like implementation
	{
		pCur = *pHead; pPrev = pCur->pPrevious; pNext = pCur->pNext;
		for (int i2 = 0; i2 < counter - 1; i2++)
		{
			i3 = 0;
			strcpy(temp1, pCur->data.artist);
			strcpy(temp2, pNext->data.artist);
			while (!(temp1[i3] == NULL || temp2[i3] == NULL))
			{
				if (temp1[i3] != NULL)
				{
					temp1[i3] = tolower(temp1[i3]);
				}
				if (temp2[i3] != NULL)
				{
					temp2[i3] = tolower(temp2[i3]);
				}
				i3++;
			}
			if (strcmp(temp1, temp2) == 1)
			{
				pCur->pPrevious = pNext;
				pCur->pNext = pNext->pNext;
				if (pNext->pNext != NULL)
				{
					pNext->pNext->pPrevious = pCur;
				}
				pNext->pNext = pCur;

				if (pPrev != NULL)
				{
					pPrev->pNext = pNext;
					pNext->pPrevious = pPrev;
					pPrev = pNext;
				}
				else {
					pNext->pPrevious = NULL;
					pPrev = pNext;
					*pHead = pNext;
				}
				pNext = pCur->pNext;
			}
			else
			{
				pPrev = pCur;
				pCur = pCur->pNext;
				pNext = pCur->pNext;
			}
		}
	}
}
/*Sorts by Album and takes a double pointer to a Node as a parameter, but
doesnt return anything.*/
void sortAlbum(Node** pHead)
{
	Node* pPrev = NULL, *pCur = *pHead, *pNext = NULL;
	char temp1[40] = { NULL }, temp2[40] = { NULL };
	int counter = 0, i3 = 0;

	while (pCur != NULL) // counting songs in list to see how many sorts are needed
	{
		counter++;
		pCur = pCur->pNext;
	}
	if (counter == 1) //If there is only one song, there is no need to sort
	{
		return;
	}
	for (int i1 = 0; i1 < counter - 1; i1++) //Bubble sort-like implementation
	{
		pCur = *pHead; pPrev = pCur->pPrevious; pNext = pCur->pNext;
		for (int i2 = 0; i2 < counter - 1; i2++)
		{
			i3 = 0;
			strcpy(temp1, pCur->data.album);
			strcpy(temp2, pNext->data.album);
			while (!(temp1[i3] == NULL || temp2[i3] == NULL))
			{
				if (temp1[i3] != NULL)
				{
					temp1[i3] = tolower(temp1[i3]);
				}
				if (temp2[i3] != NULL)
				{
					temp2[i3] = tolower(temp2[i3]);
				}
				i3++;
			}
			if (strcmp(temp1, temp2) == 1)
			{
				pCur->pPrevious = pNext;
				pCur->pNext = pNext->pNext;
				if (pNext->pNext != NULL)
				{
					pNext->pNext->pPrevious = pCur;
				}
				pNext->pNext = pCur;

				if (pPrev != NULL)
				{
					pPrev->pNext = pNext;
					pNext->pPrevious = pPrev;
					pPrev = pNext;
				}
				else {
					pNext->pPrevious = NULL;
					pPrev = pNext;
					*pHead = pNext;
				}
				pNext = pCur->pNext;
			}
			else
			{
				pPrev = pCur;
				pCur = pCur->pNext;
				pNext = pCur->pNext;
			}
		}
	}
}
/*This function prompts user for input to see what song they'd like to modify and
what specific attribute. It calls another function in order to actually modify attribute.
It takes in a pointer to a Node as a parameter and doesnt return anything.*/
void edit(Node* pHead)
{
	char stringTemp[40] = { NULL };
	int rate = 0, numBySameArtists = printByArtist(pHead, stringTemp);
	Node* ptemp = NULL;
	int i = 0;
	if (numBySameArtists  > 1) //If there are more than one song by the same artist
	{
		printf("Which song would you like to edit? Type the title.\n"); //Asks for specific title of song
		gets(stringTemp);
		ptemp = findSong(pHead, stringTemp, SONGTITLE);
		if (ptemp == NULL) // song not found
		{
			printf("Sorry, the title you entered wasn't found within your music.\n");
		}
		else // song found
		{
			printf("What would you like ot edit? (Artist, album, title, etc)\n");
			gets(stringTemp);
			while (stringTemp[i] != NULL)
			{
				stringTemp[i] = tolower(stringTemp[i]);
				i++;
			}
			if (strcmp(stringTemp, "artist") == 0)
			{
				printf("What would you like to change the artist to?\n");
				gets(stringTemp);
				editSpecific(ptemp, ARTIST, stringTemp, rate);
			}
			else if (strcmp(stringTemp, "album") == 0)
			{
				printf("What would you like to change the album to?\n");
				gets(stringTemp);
				editSpecific(ptemp, ALBUM, stringTemp, rate);
			}
			else if (strcmp(stringTemp, "title") == 0)
			{
				printf("What would you like to change the title to?\n");
				gets(stringTemp);
				editSpecific(ptemp, SONGTITLE, stringTemp, rate);
			}
			else if (strcmp(stringTemp, "genre") == 0)
			{
				printf("What would you like to change the genre to?\n");
				gets(stringTemp);
				editSpecific(ptemp, GENRE, stringTemp, rate);
			}
			else if (strcmp(stringTemp, "rate") == 0)
			{
				printf("What would you like to change the rate to? (1-5)\n");
				scanf("%d", &rate);
				while (rate < 1 || rate > 5)
				{
					printf("Please enter a number between 1-5!\n");
					scanf("%d", &rate);
				}
				editSpecific(ptemp, RATE, stringTemp, rate);
			}
			else if (strcmp(stringTemp, "duration") == 0 || strcmp(stringTemp, "times played") == 0)
			{
				printf("Sorry, duration and times played cannot be edited!\n");
				system("pause");
			}
			return;
		}
	}
	else if (numBySameArtists == 1)
	{
		ptemp = findSong(pHead, stringTemp, ARTIST);
		printf("What would you like ot edit? (Artist, album, title, etc)\n");
		gets(stringTemp);
		while (stringTemp[i] != NULL)
		{
			stringTemp[i] = tolower(stringTemp[i]);
			i++;
		}
		if (strcmp(stringTemp, "artist") == 0)
		{
			printf("What would you like to change the artist to?\n");
			gets(stringTemp);
			editSpecific(ptemp, ARTIST, stringTemp, rate);
		}
		else if (strcmp(stringTemp, "album") == 0)
		{
			printf("What would you like to change the album to?\n");
			gets(stringTemp);
			editSpecific(ptemp, ALBUM, stringTemp, rate);
		}
		else if (strcmp(stringTemp, "title") == 0)
		{
			printf("What would you like to change the title to?\n");
			gets(stringTemp);
			editSpecific(ptemp, SONGTITLE, stringTemp, rate);
		}
		else if (strcmp(stringTemp, "genre") == 0)
		{
			printf("What would you like to change the genre to?\n");
			gets(stringTemp);
			editSpecific(ptemp, GENRE, stringTemp, rate);
		}
		else if (strcmp(stringTemp, "rate") == 0)
		{
			printf("What would you like to change the rate to? (1-5)\n");
			scanf("%d", &rate);
			while (rate < 1 || rate > 5)
			{
				printf("Please enter a number between 1-5!\n");
				scanf("%d", &rate);
			}
			editSpecific(ptemp, RATE, stringTemp, rate);
		}
		else if (strcmp(stringTemp, "duration") == 0 || strcmp(stringTemp, "times played") == 0)
		{
			printf("Sorry, duration and times played cannot be edited!\n");
			system("pause");
		}
		return;
	}
	else if (numBySameArtists == 0)
	{
		system("pause");
	}
	
}
/*This function is called by edit() and actually modifies the attribute of the song by using input
stored from edit() as a parameter. It takes in a pointer to a Node, an Attribute, a pointer to a char
and an int as parameters and it doesn't return anything.*/
void editSpecific(Node* chosenSong, Attribute Edited, char* edit, int rate)
{
	switch (Edited)
	{
	case ARTIST:
		strcpy(chosenSong->data.artist, edit);
		break;
	case SONGTITLE:
		strcpy(chosenSong->data.songTitle, edit);
		break;
	case ALBUM:
		strcpy(chosenSong->data.album, edit);
		break;
	case GENRE:
		strcpy(chosenSong->data.genre, edit);
		break;
	case RATE:
		chosenSong->data.rate = rate;
		break;
	}
}

/*This function Prompts the user for the song they would like to rerate and
and it replaces the old rate by the new user input. Takes a pointer to a Node as
a parameter*/
void rate(Node* pHead)
{
	char temp[40];
	int found = 0, rating = 0;
	system("cls");
	printf("Type the name of the song that you would like to rate:\n");
	getchar();
	gets(temp);

	if (findSong(pHead, temp, SONGTITLE))
	{
		pHead = findSong(pHead, temp, SONGTITLE);
		printf("What rating would you like to give this song? (1-5)\n");
		scanf("%d", &rating);
		while (rating < 1 || rating > 5)
		{
			printf("Please enter a number 1-5:\n");
			scanf("%d", rating);
		}
		pHead->data.rate = rating;
		found = 1;
		
	}
	else
	{
		printf("Sorry, we couldn't find a match for the title you entered!\n");
		system("pause");
	}
	
}
/*This function asks user for the name of the song they would like to play, it 
searches for it and if it is found, it displays the data for a few seconds
then skips to the next one until all songs are played. It also adds one to the 
"times played" piece of data. If song isn't found, sorry message is displayed.
It takes a pointer to a node as a parameter and doesnt return anything.*/
void play(Node* pHead)
{
	char songTemp[40] = { NULL }, songTemp2[40] = { NULL };
	int i = 0, found = 0;
	puts("Which song would you like to play?");
	getchar();
	gets(songTemp);
	system("cls");
	while (songTemp[i] != NULL) //making input all lower case
	{
		songTemp[i] = tolower(songTemp[i]);
		i++;
	}
	
	while (pHead != NULL) //Going through list checking if song exists in list
	{
		i = 0;
		strcpy(songTemp2, pHead->data.songTitle); //Storing name of song at current node
		while (songTemp2[i] != NULL) //Making song name stored all to lower case
		{
			songTemp2[i] = tolower(songTemp2[i]);
			i++;
		}
		if (strcmp(songTemp, songTemp2) == 0) //comparing input to song in current node
		{
			while (pHead != NULL)
			{
			pHead->data.timesPlayed++; //The number of times played is incremented by one every time song is played
			printf("Artist: %s\n", pHead->data.artist);
			printf("Album: %s\n", pHead->data.album);
			printf("Title: %s\n", pHead->data.songTitle);
			printf("Genre: %s\n", pHead->data.genre);
			if (pHead->data.length.sec < 10)
			{
				printf("Duration: %d:0%d\n", pHead->data.length.min, pHead->data.length.sec);
			}
			else {
				printf("Duration: %d:%d\n", pHead->data.length.min, pHead->data.length.sec);
			}
			printf("Times Played: %d\n", pHead->data.timesPlayed);
			printf("Rate: %d\n", pHead->data.rate);
			printf("------------------------------\n");
			for (int i1 = 0; i1 < 5000000; i1++)
			{
				printf("");
			}
			system("cls");
			pHead = pHead->pNext;
			}
			puts("That is all your music!");
			system("pause");
			found = 1; //Song with that title was found
		}
		else
		{
			pHead = pHead->pNext;
		}

	}
	if (found == 0) //If song wasn't found sorry message is displayed
	{
		puts("Sorry, that song was not found within your music.");
		system("pause");
	}
}
/*This function prompts the user for the title of the song they would like to delete.
It goes throught the list searching for it and if it finds it fixes pointers and
deallocates memory of the respective song. If it doesn't find it, it displays a sorry
message. This takes a double pointer to a Node as a parameter and doesn't return anything.*/
void deleteSong(Node** pHead)
{
	char title[40] = { NULL };
	Node* pCur = *pHead;
	char temp1[40] = { NULL };
	int i = 0;
	system("cls");
	printf("What is the title of the song you would like to delete?\n");
	getchar();
	gets(title);

	while (title[i] != NULL)
	{
		title[i] = tolower(title[i]);
		i++;
	}
	while (pCur != NULL)
	{
		i = 0;
		strcpy(temp1, pCur->data.songTitle);
		while (temp1[i] != NULL)
		{
			temp1[i] = tolower(temp1[i]);
			i++;
		}
		if (strcmp(title, temp1) == 0)
		{
			if (pCur->pPrevious == NULL)
			{
				*pHead = pCur->pNext;
				if (pCur->pNext != NULL)
				{
					pCur->pNext->pPrevious = NULL;
				}
			}
			else if (pCur->pNext == NULL)
			{
				pCur->pPrevious->pNext = NULL;
			}
			else {
				pCur->pPrevious->pNext = pCur->pNext;
				pCur->pNext->pPrevious = pCur->pPrevious;
			}
			free(pCur);
			return;
		}
		pCur = pCur->pNext;
	}
	printf("Sorry, that title wasn't found within your songs.\n");
	system("pause");
}
/*This function creates a new node and prompts the user for
all of the pieces of information required to fill all of the attributes
out, then it calls insertNodeFront() to insert Node. It takes a double pointer
to a Node as a parameter and doesnt return anything*/
void insertNewSong(Node** pHead)
{
	system("cls");
	char temp[40] = { NULL };
	int temp1 = 0, temp2;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->pNext = NULL;
	newNode->pPrevious = NULL;
	printf("What is the title of the new song?\n");
	getchar();
	gets(temp);
	strcpy(newNode->data.songTitle, temp);
	printf("What is the artist of the new song?\n");
	gets(temp);
	strcpy(newNode->data.artist, temp);
	printf("What is the name of the album of the new song?\n");
	gets(temp);
	strcpy(newNode->data.album, temp);
	printf("What is the genre of the new song?\n");
	gets(temp);
	strcpy(newNode->data.genre, temp);
	printf("What is the duration or your song? (In the format min sec)\n");
	scanf("%d%d", &temp1, &temp2);
	while (temp1 < 0 || temp1 > 59 || temp2 < 0 || temp2 > 59)
	{
		printf("Sorry, both your minutes and seconds must be 0-59.\nPlease re-enter values (use format min sec):\n");
		scanf("%d%d", &temp1, &temp2);
	}
	newNode->data.length.min = temp1;
	newNode->data.length.sec = temp2;
	printf("How many times has it been played?\n");
	scanf("%d", &temp1);
	newNode->data.timesPlayed = temp1;
	printf("What rate would you like to give it? (1-5)\n");
	scanf("%d", &temp1);
	while (temp1 < 1 || temp1 > 5)
	{
		printf("Please make sure you re-enter a value 1-5:\n");
		scanf("%d", &temp1);
	}
	newNode->data.rate = temp1;
	insertNodeFront(pHead, newNode);
}
void shuffle(Node* pHead)
{
	system("cls");
	int counter1 = 0, i1 = 0, i2 = 0;
	Node* pTempSong = pHead;
	nodeShuffle* pTempOrder = NULL;
	
	while (pTempSong != NULL)
	{
		pTempSong = pTempSong->pNext;
		counter1++;
	}
	pTempSong = pHead;
	pTempOrder = shuffleLinkedList(counter1);

	while (pTempOrder != NULL) // Keeps repeating until every song has been played
	{
		if (pTempOrder->pPrevious != NULL) 
		{								   
			if (pTempOrder->pPrevious->order > pTempOrder->order)
			{
				for (int i = 0; i < -(pTempOrder->order - pTempOrder->pPrevious->order); i++)
				{
					pTempSong = pTempSong->pPrevious;
				}
			}
			else //We know we are at position 1 of the order linked list because pPrevious is NULL and There is a different algorithm used when we are at the beginning of the list
			{
				for (int i = 0; i < (pTempOrder->order - pTempOrder->pPrevious->order); i++)
				{
					pTempSong = pTempSong->pNext;
				}
			}
		}
		else
		{
			for (int i = 0; i < pTempOrder->order - 1; i++)
			{
				pTempSong = pTempSong->pNext;
			}
		}

		
		pTempOrder = pTempOrder->pNext; //moving through "order" list
		pTempSong->data.timesPlayed++; //The number of times played is incremented by one every time song is played
		printf("Artist: %s\n", pTempSong->data.artist);
		printf("Album: %s\n", pTempSong->data.album);
		printf("Title: %s\n", pTempSong->data.songTitle);
		printf("Genre: %s\n", pTempSong->data.genre);
		if (pHead->data.length.sec < 10)
		{
			printf("Duration: %d:0%d\n", pTempSong->data.length.min, pTempSong->data.length.sec);
		}
		else {
			printf("Duration: %d:%d\n", pTempSong->data.length.min, pTempSong->data.length.sec);
		}
		printf("Times Played: %d\n", pTempSong->data.timesPlayed);
		printf("Rate: %d\n", pTempSong->data.rate);
		printf("------------------------------\n");
		for (int i1 = 0; i1 < 5000000; i1++) //Displaying information to the screen for a finite amount of time
		{
			printf("");
		}
		system("cls");
	}



	printf("That is all your music\n");
	system("pause");

}
/*This function creates a doubly linked list that stores a number in
each node representing the song that is going to be played next within 
the shuffle feature. It takes the size of the list of songs as a parameter
and returns a pointer to a nodeSHuffle*/
nodeShuffle* shuffleLinkedList(int size)
{
	nodeShuffle* pTemp = NULL,* pHead = NULL, * pTemp2 = NULL;
	int temp = 0, used = 0, success = 1;
	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		pTemp = (nodeShuffle*)malloc(sizeof(nodeShuffle)); // Allocating space for each node
		pTemp->order = NULL;
		if (pHead != NULL)
		{
			while (pTemp->order == NULL) //This loop repeats itself until a value not already used is found for the field "order" in the current node
			{
				success = 1;
				pTemp2 = pHead;
				temp = (rand() % size) + 1;
				while (pTemp2 != NULL && pTemp2->order != temp) //This conditional makes sure the "order number" isn't taken already
				{
					pTemp2 = pTemp2->pNext;
				}
				if (pTemp2 != NULL && pTemp2->order == temp) //If the "order number" is taken, then success is 0 and look starts over
				{
					success = 0;
				}
				if (success == 1) //If "order number" isnt taken, it is assigned to the order field of the current node
					pTemp->order = temp;
			}
		}
		else
		{
			pTemp->order = rand() % size;
		}
		pTemp->pNext = pHead;       //Pointers are assigned as necessary
		pTemp->pPrevious = NULL;
		if(pHead != NULL) //In case list is empty, we make sure not to try to access a field within a NULL node.
			pHead->pPrevious = pTemp;
		pHead = pTemp;
	}
	return pHead;
}
//Exits program
void exitProgram(void)
{
	exit(0);
}