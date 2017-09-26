#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class BSTNode {
public:

	BSTNode(); // constructor
	BSTNode(const char& newText, const string& newMorse); // custom constructor
	BSTNode( BSTNode& copy); // copy constructor
	
	//getters
	char getText() const; 
	string getMorse() const;
	BSTNode*& getRight() ;
	BSTNode*& getLeft() ;

	//setters
	void setText(const char& newText);
	void setMorse(const string& newMorse);
	void setRight(BSTNode* const newRight);
	void setLeft(BSTNode* const newLeft);
	 
private:
	char text;
	string morse;
	BSTNode* rightPtr;
	BSTNode* leftPtr;
};