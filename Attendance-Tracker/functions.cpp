#include "functions.h"


using std::fstream;
using std::getline;
using std::stoi;
using std::cout;
using std::cin;
using std::endl;




fstream& readRecordsNode(ListNode*& node, fstream& is) {
	
	string recordNumString, IDnumString, numOfAbsencesString, name, last, first, email, creditNum, major, level;
	int recordNum = 0, IDnum = 0, numOfAbsences = 0;


	if (node != NULL && is.is_open() == true)
	{
		getline(is, recordNumString, ',');
		if (recordNumString == "")
		{
			return is;
		}
		recordNum = stoi(recordNumString);
		node->setRecordNum(recordNum);
		
		getline(is, IDnumString, ',');
		IDnum = stoi(IDnumString);
		node->setIDnum(IDnum);

		getline(is, last, ',');
		getline(is, first, ',');
		first.pop_back();
		last[0] = ' ';
		name = first + last;
		node->setName(name);

		getline(is, email, ',');
		node->setEmail(email);

		getline(is, creditNum, ',');
		node->setCreditNum(creditNum);

		getline(is, major, ',');
		node->setMajor(major);

		getline(is, level);
		node->setLevel(level);

	}
	else {
		cout << "Error reading records." << endl;
	}
	return is;
}

bool readRecordsList(List& list)
{
	bool success = false;
	string firstLine;
	fstream is;
	is.open("classList.csv"); //opening input file
	

	if (is.is_open() == true) //checking input file being open
	{
		success = true;
		getline(is, firstLine);
		while (is.eof() == false) //loop to read from file while end of file hasnt been reached
		{
			list.insertAtFront();
			readRecordsNode(list.getPHead(), is);
		}
		list.deleteNodeAtFront(); //Extra node is inserted at front after eof is reached so it must be deleted
	}

	return success;
}

bool writeMaster(List& list)
{
	bool success = false;

	if (list.getPHead() != nullptr)
	{
		ListNode* pTemp = list.getPHead();
		fstream os;
		os.open("master.txt", 'w'); //opening output file

		success = true;

		while (pTemp != nullptr) //Loop writing out data of one student every iteration
		{
			os << pTemp->getRecordNum() << endl << pTemp->getIDnum() << endl << pTemp->getNumAbsences() << endl << pTemp->getName() << endl;
			os << pTemp->getEmail() << endl << pTemp->getCreditNum() << endl << pTemp->getMajor() << endl << pTemp->getLevel() << endl;
			Stack tempAbsences = pTemp->getAbsences();

			for (int i = 0; i < pTemp->getNumAbsences(); i++) //Loop prints out dates of absences using the number of absences as a reference to how many times to loop
			{
				os << tempAbsences.getnAbsence(i) << endl;
			}
			os << endl;
			pTemp = pTemp->getPNext();
		}
	}
	else
	{
		cout << "Sorry, this class has no students." << endl;
	}

	return success;
}


fstream& readMasterNode(ListNode*& pNode, fstream& is)
{
	
	string recordNumString, IDnumString, numOfAbsencesString, name, last, first, email, creditNum, major, level;
	int recordNum = 0, IDnum = 0, numOfAbsences = 0;

	/*Attributes are read from a file one by one
	and stored into a string that can then be passed into the 
	ListNode's setter functions. If the attribute is an int,
	the function stoi() is used to convert it before storing it.
	If the first thing read in is a blank line, a return is called because 
	it means the eof has been reached*/
	if (pNode != NULL && is.is_open() == true) 
	{
		getline(is, recordNumString);
		if (recordNumString == "")
		{
			return is;
		}
		recordNum = stoi(recordNumString);
		pNode->setRecordNum(recordNum);

		getline(is, IDnumString);
		IDnum = stoi(IDnumString);
		pNode->setIDnum(IDnum);

		getline(is, numOfAbsencesString);
		numOfAbsences = stoi(numOfAbsencesString);
		pNode->setNumAbsences(numOfAbsences);

		getline(is, name);
		pNode->setName(name);

		getline(is, email);
		pNode->setEmail(email);

		getline(is, creditNum);
		pNode->setCreditNum(creditNum);

		getline(is, major);
		pNode->setMajor(major);

		getline(is, level);
		pNode->setLevel(level);

		Stack tempAbsences;
		string abs;
		while (1) //This loop goes on reading as many dates of absences as the student has and is broken when the string read is blank, meaning there are no more absences to be read
		{
			getline(is, abs);
			if (abs == "")
			{
				break;
			}
			tempAbsences.manualPush(abs); //Dates are first pushed into a temporary stack 
		}
		pNode->setAbsences(tempAbsences); //Temporary stack is passed into the absences setter of the ListNode
	}
	else
	{
		cout << "Error reading Master List.";
	}


	return is;
}

bool readMasterList(List& list)
{
	bool success = false;
	fstream is;

	is.open("master.txt");

	if (is.is_open() == true)
	{

		if (list.getPHead() == nullptr)
		{
			while (is.eof() == false) //This loop reads students from a master.txt file one by one
			{
				list.insertAtFront();
				readMasterNode(list.getPHead(), is);
				
			}
			list.deleteNodeAtFront(); //An extra node is inserted at front after the eof has been reached so it must be deleted
		}
		else {
			ListNode* pTemp = list.getPHead();
			while (pTemp != nullptr) //If list is already made and is simply being overwritten, then no new nodes must be inserted so this loop just stores data into attribute fields for each student
			{
				readMasterNode(pTemp, is);
				pTemp = pTemp->getPNext();
			}
		}
	}
	return success;
}

void reportType(List& list)
{
	system("cls");
	int reportType = 0;

	if (list.getPHead() != nullptr) // This prompts the user for the type of report they want to make
	{
		cout << "1. Make report of all students." << endl;
		cout << "2. Make report with students with or above a certain number of absences." << endl;
		cout << "Please choose the type of report you would like to make." << endl;
		cin >> reportType;

		while (reportType > 2 || reportType < 0)
		{
			cout << "Please enter a number 1-2." << endl;
			cin >> reportType;
		}

		switch (reportType)
		{
		case 1:
			writeReportLastAbsence(list);
			break;
		case 2:
			writeReportThreshold(list);
			break;
		}
	}
	else {
		cout << "Sorry, class has no students." << endl;
	}
}

/*This function is called by reportType() and writes a report in a fashion that
every student is output to the screen along with the date of their most
recent absence*/
bool writeReportLastAbsence(List& list)  
{
	bool success = false;
	ListNode* pTemp = list.getPHead();
	fstream os;
	
	os.open("report.txt", 'w');


	if (list.getPHead() != nullptr) 
	{
		success = true;
		while (pTemp != nullptr)
		{
			os << "Record Number: " << pTemp->getRecordNum() << endl;
			os << "ID Number: " << pTemp->getIDnum() << endl;
			os << "Name: " << pTemp->getName() << endl;
			os << "Email: " << pTemp->getEmail() << endl;
			os << "Number of Credits: " << pTemp->getCreditNum() << endl;
			os << "Major: " << pTemp->getMajor() << endl;
			os << "Level: " << pTemp->getLevel() << endl;
			os << "Number of Absences: " << pTemp->getNumAbsences() << endl;
			
			if (pTemp->getNumAbsences() > 0)
			{
				os << "Date of Last Absence: " << pTemp->getLastAbsence() << endl;

			}
			os << endl;
			pTemp = pTemp->getPNext();
		}
	}
	

	return success;
}

/*This function is called by reportType() and writes a report in a fashion that only
students above a specific threshold number of absences are output along with the date of
their most recent absence*/
bool writeReportThreshold(List& list)
{
	bool success = false;
	ListNode* pTemp = list.getPHead();
	fstream os;
	int threshold = 0;
	int numAboveThreshold = 0;
	os.open("reportThreshold.txt", 'w');

	if (list.getPHead() != nullptr)
	{
		cout << "Please, enter the number of absences you want as a threshold." << endl;
		cin >> threshold;
		while (pTemp != nullptr)
		{
			if (pTemp->getNumAbsences() >= threshold)
			{
				numAboveThreshold++;
				os << "Record Number: " << pTemp->getRecordNum() << endl;
				os << "ID Number: " << pTemp->getIDnum() << endl;
				os << "Name: " << pTemp->getName() << endl;
				os << "Email: " << pTemp->getEmail() << endl;
				os << "Number of Credits: " << pTemp->getCreditNum() << endl;
				os << "Major: " << pTemp->getMajor() << endl;
				os << "Level: " << pTemp->getLevel() << endl;
				os << "Number of Absences: " << pTemp->getNumAbsences() << endl;

				if (pTemp->getNumAbsences() > 0)
				{
					os << "Date of Last Absence: " << pTemp->getLastAbsence() << endl;

				}

				os << endl;
			}
			pTemp = pTemp->getPNext();
		}
		if (numAboveThreshold == 0)
		{
			cout << "Sorry, there are students with " << threshold << " absences." << endl;
			system("pause");
		}

	}
	
	
	return success;
}

/*This function is used when the option mark absences is chosen
and it prompts the user for a (absent) or p (present) for every student 
in the class. Note: If used the same day, and somebody previously marked as absent is
now marked as present it will not change it to present but if they were previously marked
present, it WILL change to absent. If there was a mistake and edit must be made from absent 
to present, edit absences option must be used.*/
void markAbsences(List& list)
{
	system("cls");
	ListNode* pTemp = list.getPHead();
	char attendance = '\0';

	if (list.getPHead() != nullptr)
	{
		while (pTemp != nullptr)
		{
			cout << pTemp->getName() << endl;
			cout << "Absent(A/a) or Present(P/p)?" << endl;
			cin >> attendance;
			attendance = tolower(attendance);

			while (attendance != 'a' && attendance != 'p')
			{
				cout << "Please, enter a valid character." << endl;
				cin >> attendance;
				attendance = tolower(attendance);
			}
			if (attendance == 'a')
			{
				pTemp->markAbsent();
			}
			pTemp = pTemp->getPNext();
			system("cls");
		}
	}
}

/*Extra Credit: This function prompts the user for the type
of search for student that they would like to make (Name or ID)
then the respective function is called.*/
void editAbsence(List& list)
{
	int option = 0;

	if (list.getPHead() != nullptr)
	{
		cout << "Look up student by: \n1. Name.\n2. ID number." << endl;
		cout << "Please choose and option." << endl;
		cin >> option;

		while (option > 2 || option < 1)
		{
			cout << "Please enter a number 1-2." << endl;
			cin >> option;
		}

		switch (option)
		{
		case 1:
			editByName(list);
			break;
		case 2:
			editByIDnum(list);
			break;
		}
	}
	else
	{
		cout << "Sorry, this class has no students." << endl;
	}
}

/*This function searches for a student by name and if it finds them,
it will call the editHelper() function.*/
void editByName(List& list)
{
	ListNode* pTemp = list.getPHead();
	string name = "", nameCmp = "", first = "", last = "";
	int i = 0, found = 0;
	cout << "Please enter student's name." <<endl;
	cin >> first;
	cin >> last;
	name = first + " " + last;
	while (name[i]) //Turning input name into all lowercase to be able to compare to all of the names in the list
	{
		name[i] = tolower(name[i]);
		i++;
	}

	while (pTemp != nullptr)
	{
		i = 0;
		nameCmp = pTemp->getName(); // Getting name of student

		while (nameCmp[i]) // Loop makes turns name of current student to lowercase to be able to compare to name input by user
		{
			nameCmp[i] = tolower(nameCmp[i]);
			i++;
		}

		if (nameCmp == name)
		{
			found = 1;
			break;
		}
		pTemp = pTemp->getPNext();
	}

	if (found == 1) // If name input by user is found in list, then editHelper() function is called
	{
		editHelper(pTemp);
	}
	else
	{
		system("cls");
		cout << "Sorry, that student wasn't found." << endl;
		system("pause");
	}
}

void editByIDnum(List& list)
{
	int IDnum = 0;
	bool found = false;
	ListNode* pTemp = list.getPHead();


	cout << "Please enter the students ID number." << endl; //User is prompter for ID number
	cin >> IDnum;

	while (pTemp != nullptr) // This loop compares the input ID number to the IDs of every student
	{
		if (IDnum == pTemp->getIDnum()) 
		{
			found = true;
			break;
		}
		pTemp = pTemp->getPNext();
	}

	if (found == true) // If student with ID input by user is found then the editHelper() function is called
	{
		editHelper(pTemp);
	}
	else
	{
		cout << "Sorry, student not found." << endl;
		system("pause");
	}
}

/*This function  calls a ListNode function that edits Stack of absences
since it doesnt have access to the stack itself*/
void editHelper(ListNode*& pNode)
{
	string date = "";
	char option = '\0';
	bool validInput = false;
	cout << "Please enter the date you would like to edit. (mm/dd/yyyy)" <<endl; // Prompting user for date they want to modify
	cin >> date;

	system("cls");

	while (date[2] != '/' || date[5] != '/') // Making sure input is valid
	{
		cout << "Please enter date in the right format. (mm/dd/yyyy)" << endl;
		cin >> date;
	}
	cout << pNode->getName() << endl;
	cout << "Absent(A/a) or present(P/p)?" << endl; //Prompting for absent or present
	cin >> option;
	option = tolower(option);

	while (option != 'a' && option != 'p') //Making sure input is valid
	{
		cout << "Please enter a valid option." << endl;
		cin >> option;
	}
	
	pNode->editAbsences(date, option); // calling a ListNode function to edit Stack of absences

}