#ifndef LIST_H
#define LIST_H


#include "ListNode.h"



class List {
public:
	List(); //constructor
	List(const List& copy); //copy constructor
	~List(); //destructor

	void setPHead(ListNode* const & newPHead); // pHead setter
	ListNode*& getPHead(); // pHead getter

	//Node functions
	bool insertAtFront();
	void deleteNodeAtFront();
	ListNode*& makeNode();

private:
	ListNode* pHead;
};


#endif // !LIST_H