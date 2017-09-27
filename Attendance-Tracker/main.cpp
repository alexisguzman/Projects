/*******************************************************************************************
* Programmer: Alexis Guzman                                                                       *
* Class: CptS 122, Spring 2017; Lab Section 9                                             *
* Programming Assignment: PA 7                                                     *
* Date: April 5, 2017                                                                          *
* Description: This program is a simple but very useful attendance tracker that allows professors
				or TAs to mark students absent and record the dates automatically. If a mistake
				is committed, the user can go back and fix it with the Edit Absences feature.
				This program is achieved by creating a main class representing a student and
				what I would consider a secondary class such as the list of a class which points 
				to a list of student classes. A tertiary but important class would be the class
				representing the stack of absences which allows for easy access to last absence*
*******************************************************************************************/

#include "functions.h"


using std::cout;
using std::cin;
using std::endl;



int main(void)
{	
	List l1;
	int option = 0;
	bool exit = false;

	//Main menu loop
	while (exit == false)
	{
		cout << "1. Import couse list\n";
		cout << "2. Load master list\n";
		cout << "3. Store master list \n";
		cout << "4. Mark absences\n";
		cout << "5. Edit absences\n";
		cout << "6. Generate report\n";
		cout << "7. Exit\n";
		option = 0;

		cout << "Choose an option: \n";
		cin >> option;
		while (option > 7 || option < 1) //making sure option is valid
		{
			cout << "Please enter a number 1-7.\n";
			cin >> option;
		}

		switch (option)  //switch for option chosen
		{
		case 1:
			readRecordsList(l1);
			system("cls");
			break;
		case 2:
			readMasterList(l1);
			system("cls");
			break;
		case 3:
			writeMaster(l1);
			system("cls");
			break;
		case 4:
			markAbsences(l1);
			system("cls");
			break;
		case 5:
			system("cls");
			editAbsence(l1);
			system("cls");
			break;
		case 6:
			reportType(l1);
			system("cls");
			break;
		case 7:
			exit = true;
			break;
		}
	}
	return 0;
}