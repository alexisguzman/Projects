#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>
#include <time.h>
#include <string>

using std::vector;
using std::string;




class Stack {
public:
	Stack(); //constructor
	Stack(const Stack& copy); //copy constructor
	~Stack(); // destructor
	Stack& operator=(const Stack& copy); //overloaded assignemnt operator

	//Stack operations
	string pop();
	string peek();
	bool isEmpty();
	bool push();
	void manualPush(const string& copy);
	

	//Getters
	string getnAbsence(int n) const;
	int getSize() const;


	//for testing
	void printStack();

private:
	vector<string> daysAbsent;
	int size;
};


#endif // !STACK_H