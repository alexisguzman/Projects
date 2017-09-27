#ifndef LISTNODE_H
#define LISTNODE_H


#include "Stack.h"

using std::vector;
using std::string;

class ListNode {
public:
	ListNode(); //constructor
	ListNode(const ListNode& copy); // copy constructor
	~ListNode(); // destructor

	//getters
	ListNode* getPNext() const;
	int getRecordNum() const;
	int getIDnum() const;
	int getNumAbsences() const;
	string getName() const;
	string getEmail() const;
	string getCreditNum() const;
	string getMajor() const;
	string getLevel() const;
	Stack getAbsences() const;
	string getLastAbsence();


	//setters
	void setPNext(ListNode* const & newPNext);
	void setRecordNum(const int newRecordNum);
	void setNumAbsences(const int newNumAbsences);
	void setIDnum(const int newID);
	void setName(const string newName);
	void setEmail(const string newEmail);
	void setCreditNum(const string newCreditNum);
	void setMajor(const string newMajor);
	void setLevel(const string newLevel);
	void setAbsences(const Stack newAbsences);
	
	//Absence function
	void markAbsent();
	void editAbsences(const string& date, const char& option);

private:
	ListNode* pNext;

	int recordNum;
	int IDnum;
	int numOfAbsences;
	string name;
	string email;
	string creditNum;
	string major;
	string level;
	Stack absences;

};


#endif // !LISTNODE_H