/*******************************************************************************************
* Programmer: Alexis Guzman                                                                  *
* Class: CptS 122, Spring 2017; Lab Section                                            	     *
* Programming Assignment: PA 6                                                    			 *
* Date: March 22nd, 2017                                                                     *
* Description: This is a basic c++ program that translates English into morse code by using a 
*		   	   binary search tree															 *
*******************************************************************************************/

#include "BST.h"
#include "BSTNode.h"


int main()
{
	BST t1; //creating new tree
	fstream input("Convert.txt"); //opening input file
	string Text = "";
	int i = 0, line_count = 1;

	//t1.inOrder(); //printing tree in order first


	cout << "Conversion to morse: " << endl;

	while (!input.eof())
	{
		getline(input, Text); //gets line from file
		cout << "Line " << line_count << ": "<< Text << endl;
		i = 0;
		
		while (Text[i] != NULL) //This loop checks if any of the characters are whitespaces, if they are, 
		{						//two spaces are printed out, in addition to the already existing space between each letter in morse
			if (Text[i] != ' ')
			{
				t1.search(Text[i]);
			}
			else {
				cout << "  ";
			}
			i++;
		}
		cout << endl;
		line_count++;
	}	

	input.close();// closing the input file

	return 0;
}