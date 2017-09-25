/*******************************************************************************************
* Programmer: Alexis Guzman                                                                      *
* Class: CptS 122, Spring 2017; Lab Section 9                                             *
* Programming Assignment: PA 3                                                  *
* Date: February 8th, 2017                                                                          *
* Description: This program simulates a music manager by reading an actual record and writing 
			   back to it if any modifications are made.     *
*******************************************************************************************/
#include "functions.h"

int main(void)
{
	/*I'm assuming main should have more in it but last semester my main was really messy
	so I just need to find the perfect balance. By the time I realized I had only a couple 
	statements in my main, I was too far into it to go back. I hope it's not an issue.*/
	
	
	Node* pHead = NULL;
	chooseOption(&pHead, printMainMenu());
	

	return 0;

}