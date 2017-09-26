#include "BSTNode.h"

// constructor
BSTNode::BSTNode()
{
	this->rightPtr = nullptr;
	this->leftPtr = nullptr;
	this->text = '\0';
	this->morse = "";
}

//custom constructor, takes a char newText and a string newMorse
BSTNode::BSTNode(const char& newText, const string& newMorse)
{
	this->rightPtr = nullptr;
	this->leftPtr = nullptr;
	this->text = newText;
	this->morse = newMorse;
}
//copy constructor
BSTNode::BSTNode(BSTNode& copy)
{
	this->text = copy.getText();
	this->morse = copy.getMorse();
	this->leftPtr = copy.getLeft();
	this->rightPtr = copy.getRight();
}

//Returns chat text
char BSTNode::getText() const
{
	return this->text;
}

//Sets text to newText
void BSTNode::setText(const char& newText)
{
	this->text = newText;
}

//Returns morse string
string BSTNode::getMorse() const
{
	return this->morse;
}

//Sets morse to newMorse
void BSTNode::setMorse(const string& newMorse)
{
	this->morse = newMorse;
}

//Returns rightPtr
BSTNode*& BSTNode::getRight()
{
	return this->rightPtr;
}

//Sets rightPtr to newRight
void BSTNode::setRight(BSTNode* const newRight)
{
	this->rightPtr = newRight;
}

//Returns LeftPtr
BSTNode*& BSTNode::getLeft() 
{
	return this->leftPtr;
}

//Sets leftPtr to newLeft
void BSTNode::setLeft(BSTNode* const newLeft)
{
	this->leftPtr = newLeft;
}

