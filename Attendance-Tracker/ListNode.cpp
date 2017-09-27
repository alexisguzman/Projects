#include "ListNode.h"


using std::stoi;


//constructor
ListNode::ListNode()
{
	this->recordNum = 0;
	this->IDnum = 0;
	this->numOfAbsences = 0;
	this->name = "";
	this->email = "";
	this->creditNum = "";
	this->major = "";
	this->level = "";
	this->pNext = nullptr;
}

//copy constructor
ListNode::ListNode(const ListNode& copy)
{

	this->recordNum = copy.recordNum;
	this->IDnum = copy.IDnum;
	this->numOfAbsences = copy.numOfAbsences;
	this->name = copy.name;
	this->email = copy.email;
	this->creditNum = copy.creditNum;
	this->major = copy.major;
	this->level = copy.level;

	for (int i = 0; i < copy.numOfAbsences; i++)
	{
		this->absences.push();
		
	}

}

//destructor
ListNode::~ListNode()
{
}

//getters
ListNode* ListNode::getPNext() const
{
	return this->pNext;
}
int ListNode::getRecordNum() const
{
	return this->recordNum;
}
int ListNode::getIDnum() const
{
	return this->IDnum;
}
int ListNode::getNumAbsences() const
{
	return this->numOfAbsences;
}
string ListNode::getName() const
{
	return this->name;
}
string ListNode::getEmail() const
{
	return this->email;
}
string ListNode::getCreditNum() const
{
	return this->creditNum;
}
string ListNode::getMajor() const
{
	return this->major;
}
string ListNode::getLevel() const
{
	return this->level;
}
Stack ListNode::getAbsences() const
{
	return this->absences;
}
string ListNode::getLastAbsence() 
{
	return this->absences.peek();
}




//setters
void ListNode::setPNext(ListNode* const & newPNext)
{
	this->pNext = newPNext;
}
void ListNode::setRecordNum(const int newRecordNum)
{
	this->recordNum = newRecordNum;
}
void ListNode::setIDnum(const int newID)
{
	this->IDnum = newID;
}
void ListNode::setNumAbsences(const int newNumAbsences)
{
	this->numOfAbsences = newNumAbsences;
}
void ListNode::setName(const string newName)
{
	this->name = newName;
}
void ListNode::setEmail(const string newEmail)
{
	this->email = newEmail;
}
void ListNode::setCreditNum(const string newCreditNum)
{
	this->creditNum = newCreditNum;
}
void ListNode::setMajor(const string newMajor)
{
	this->major = newMajor;
}
void ListNode::setLevel(const string newLevel)
{
	this->level = newLevel;
}
void ListNode::setAbsences(const Stack newAbsences)
{
	this->absences = newAbsences;
}


/*This function pushes current date to the absence
stack and adds one to the size member*/
void ListNode::markAbsent()
{
	bool pushed = false;

	pushed = this->absences.push();
	if (pushed == true)
	{
		this->numOfAbsences++;
	}
}

/*This is where the functions for the extra credit option arrive to at the very end.
This function checks whether the date entered is already on the stack. If it is and 
the "edit" is to absent, then nothing happens since it's already there but if it is
marked as present, it gets deleted from stack. On the other hand, if the "edit" is to 
absent and the date isn't in the stack, the date gets pushed but in chronological order
and it is marked as present and date isn't in the stack, then nothing is done since date
shouldn't be in it. The date and a "mode" (absent or present) are passed
in as parameters.*/
void ListNode::editAbsences(const string& date, const char& option)
{
	Stack sTemp;
	string temp, cmpDate;
	int i = this->numOfAbsences -1, numDate = 0, found = 0; //variables for "present" algorithm
	int insertPosition = 0, index = this->numOfAbsences - 1, newDateValue = 0, cmpDateValue = 0; //variables for "absent" algorithm
	
	while (numDate < this->numOfAbsences) //Checking is date has already been marked as absent
	{
		if (this->absences.getnAbsence(i) == date)
		{
			found = 1;
			break;
		}
		numDate++; // This variable is used in case date IS found, this way we know, without having to compare each element to the entered date, when the element we want has been popped off
		i--;
	}

	if (found == 1) //If date is already in stack (marked as absent)
	{
		if (option == 'p') //If change is to present then every element will be popped off until the wanted date is popped off then the elements will be pushed back on after date wanted is gone
		{
			this->numOfAbsences--;
			for (int i2 = 0; i2 < numDate; i2++) // popping elements covering element we want to discard and pushing into a temporary stack
			{
				temp = this->absences.pop();
				sTemp.manualPush(temp);
			}
			this->absences.pop(); //popping element being discarted

			for (int i2 = 0; i2 < numDate; i2++) //pushing elements from the temporary stack back into the absences stack of the student
			{
				temp = sTemp.pop();
				this->absences.manualPush(temp);
			}
		}
	}
	else
	{
		if (option == 'a') //If date is not found but "edit" is to absent then date must be added. Note, it must be in chronological order.
		{
			if (this->numOfAbsences == 0) //If the stack is empty and there are no absences then the date simply gets pushed and we return
			{
				numOfAbsences++;
				absences.manualPush(date);
				return;
			}
			this->numOfAbsences++;
			string monthString = "  ", dayString = "  ", yearString = "    ";
			int month = 0, day = 0, year = 0;

			monthString[0] = date[0]; monthString[1] = date[1];														//
			dayString[0] = date[3]; dayString[1] = date[4];															//This algorithm needs the date to be in the format mm/dd/yyyy and the function that 
			yearString[0] = date[6]; yearString[1] = date[7]; yearString[2] = date[8]; yearString[3] = date[9];		//prompts for a date makes sure it is in that format. From this, the mm, dd, and yyyy strings
																													//are turned into integers and this way we can classify each day by a certain value.
			month = stoi(monthString);																				//It could be done in different ways but I decided to multiply my month integer by 30, my year integer
			day = stoi(dayString);																					//by 365, and leave the day integer as is, then add them up and the date has a value that can be compared.
			year = stoi(yearString);																				//This way we can be sure to push the date in chronological order. We turn the the date entered by
																													// user into a "value" first then as we go down the stack, we turn each date into a comparable "value" 
			newDateValue = (month * 30) + day + (year * 365);														//as well until the "value" of the entered date is no longer smaller than the compared value.		
			
			cmpDate = this->absences.getnAbsence(index);
			index--;
			monthString[0] = cmpDate[0]; monthString[1] = cmpDate[1];
			dayString[0] = cmpDate[3]; dayString[1] = cmpDate[4];
			yearString[0] = cmpDate[6]; yearString[1] = cmpDate[7]; yearString[2] = cmpDate[8]; yearString[3] = cmpDate[9];

			month = stoi(monthString);
			day = stoi(dayString);
			year = stoi(yearString);

			cmpDateValue = (month * 30) + day + (year * 365);
			if (newDateValue < cmpDateValue)
			{
				insertPosition++;
			}
			while (newDateValue < cmpDateValue) {

				/*This loop just turns dates in stack into comparable "values"*/
				cmpDate = this->absences.getnAbsence(index);
				monthString[0] = cmpDate[0]; monthString[1] = cmpDate[1];
				dayString[0] = cmpDate[3]; dayString[1] = cmpDate[4];
				yearString[0] = cmpDate[6]; yearString[1] = cmpDate[7]; yearString[2] = cmpDate[8]; yearString[3] = cmpDate[9];

				month = stoi(monthString);
				day = stoi(dayString);
				year = stoi(yearString);

				cmpDateValue = (month * 30) + day + (year * 365);
				index--;
				if (newDateValue < cmpDateValue) //creating a number to know how many dates we need to pop off without having to compare a second time
				{
					insertPosition++;
				}
				
			} 

			for (int i2 = 0; i2 < insertPosition; i2++) //popping elements off
			{
				temp = this->absences.pop();
				sTemp.manualPush(temp);
			}

			this->absences.manualPush(date); //Pushing new date

			for (int i2 = 0; i2 < insertPosition; i2++) //pushing elements back on
			{
				temp = sTemp.pop();
				this->absences.manualPush(temp);
			}

		}
	}

}