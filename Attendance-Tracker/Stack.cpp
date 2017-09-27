#include "Stack.h"


using std::cout;
using std::endl;
using std::to_string;


// constructor
Stack::Stack()
{
	this->size = 0;
	this->daysAbsent;
}

// copy constructor
Stack::Stack(const Stack& copy)
{
	this->daysAbsent = copy.daysAbsent;
	this->size = copy.size;
}

//destructor
Stack::~Stack()
{
}

//Overloaded assignment operator
Stack& Stack::operator=(const Stack& copy)
{

	this->daysAbsent = copy.daysAbsent;
	this->size = copy.size;

	return (*this);
}

/*This function deletes the last element in the stack and returns it 
as well as reduces the attribute size by one.*/
string Stack::pop()
{
	this->size--;

	string temp = "";
	
	temp = this->daysAbsent.back();
	
	this->daysAbsent.pop_back();

	return temp;
}

/*This function just looks at the last element of the 
stack and returns it but without deleting element or
modifying the size*/
string Stack::peek() 
{
	string temp = this->daysAbsent[this->size - 1];
	if (this->isEmpty() == false)
	{
		return temp;
	}
}

/*This function just checks whether the stack is empty*/
bool Stack::isEmpty()
{
	bool isEmpty = false;
	if (this->size == 0)
	{
		isEmpty = true;
	}
	return isEmpty;
}

/*This function obtains the current date from the computer
 and stores it into a string in  the mm/dd/yyyy format
 then pushes it into the stack (adds it as the last element)*/
bool Stack::push()
{
	bool pushed = false;
	

	time_t t = time(0);
	struct tm *now = localtime(&t);
	int month, day, year;
	string monthString, dayString, yearString, date;

	month = now->tm_mon;
	day = now->tm_mday;
	year = now->tm_year;

	
	if (month > 8)
	{
		monthString = to_string(month + 1);
	}
	else //making sure format stays as mm/dd/yyyy by adding a zero if month is less than 10
	{
		monthString = "0" + to_string(month + 1);
	}

	if (day > 9)
	{
		dayString = to_string(day);
	}
	else // making sure format stays as mm/dd/yyyy by adding a zero if day is less than 10
	{
		dayString = "0" + to_string(day);
	}
	yearString = to_string(year + 1900);

	date = monthString + "/" + dayString + "/" + yearString; // makes date string by adding all three of the strings together

	if (daysAbsent.empty() == true || daysAbsent.back() != date) //Checking if date has already been marked as absent but first checking if list is empty to not try to access memory we shouldn't
	{
		pushed = true;
		this->daysAbsent.push_back(date);
		this->size++;
	}
	return pushed;
}

/*This function is used in the editAbsences() function because when
editing, the date pushed is not directly from the computer, it's one 
that the user inputs*/
void Stack::manualPush(const string& copy)
{
	this->size++;
	this->daysAbsent.push_back(copy);
}

/*This function returns the date of the absence in the position of the stack needed*/
string Stack::getnAbsence(int n) const
{
	return this->daysAbsent[n];
}

//getter
int Stack::getSize() const
{
	return this->size;
}



//Used for testing
void Stack::printStack()
{
	for (int i = 0; i < size; i++)
	{
	cout << this->daysAbsent[i] << endl;
	}
}