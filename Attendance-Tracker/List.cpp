#include "List.h"

//constructor
List::List()
{
	this->pHead = nullptr;
}

//copy constructor
List::List(const List& copy)
{
	this->pHead = copy.pHead;
}
//destructor
List::~List()
{
	ListNode* pTemp = this->pHead;
	while (this->pHead != nullptr)
	{
		this->pHead = this->pHead->getPNext();
		delete pTemp;
		pTemp = this->pHead;
	}
}

//pointer to head setter
void List::setPHead(ListNode* const & newPHead)
{
	this->pHead = newPHead;
}

//pointer to head getter (must not be constant because pHead is returned by reference)
ListNode*& List::getPHead()
{
	return this->pHead;
}

/*This function simply inserts a node at the front of the list*/
bool List::insertAtFront()
{
	bool success = false;
	ListNode* temp = makeNode();

	if (temp != NULL)
	{ 
		temp->setPNext(this->pHead);
		this->pHead = temp;
		success = true;
	}
	return success;
}

/*This function deletes the node at the front of the list
(doesn't check for empty list because that case isn't possible
in this program)*/
void List::deleteNodeAtFront()
{
	ListNode* pTemp = this->pHead;

	this->pHead = this->pHead->getPNext();

	delete pTemp;
}

/*Allocates node in heap and return pointer to it*/
ListNode*& List::makeNode()
{
	
	ListNode* temp = new ListNode;

	return temp;
}