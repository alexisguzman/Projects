#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "BSTNode.h"
#include <ctype.h>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ostream;

class BST {
public:

	BST(); // constructor
	~BST(); // destructor

	
	void setRoot(BSTNode* const newRoot); //root setter
	void insert(const char newText, const string newMorse); //calls private insert
	void inOrder(); //calls private inOrder
	void search(const char Text); //Calls private search
	

	void inOrderDelete(); //calls private inOrderDelete
private:
	BSTNode* root;
	void search(char Text, BSTNode*& pTree); //Searches for a letter in English and prints it out morse translation
	void insert(BSTNode*& pTree, const char newText, const string newMorse);
	void inOrder(BSTNode*& pTree); // Traverses BST in order from lowest to highest(Ascii) and prints each node
	void inOrderDelete(BSTNode*& pTree); //Traverses BST in order from lowest to highest(Ascii) and deletes each node
};
