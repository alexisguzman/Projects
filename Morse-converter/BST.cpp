#include "BST.h"

/*This constructor creates the binary search tree off a file
called MorseText.txt by reading a character and its respective morse
code string translation in the order they exist in this file. It opens
a stream to the file and after everything is read in, it closes the stream.*/
BST::BST()
{
	fstream input;
	this->root = nullptr;
	input.open("MorseText.txt");
	char newText = '\0', whitespace = '\0';
	string newMorse = "";
	while (!input.eof())
	{
		input >> newText;
		input >> newMorse;
		insert(newText, newMorse);
	}
	input.close();
}

//This destructor calls public inOrderDelete()
BST::~BST()
{
	this->inOrderDelete();
}

//This inOrderDelete() calls the private inOrderDelete
void BST::inOrderDelete()
{
	this->inOrderDelete(this->root);
}

/*Recursively Deletes Nodes by going as far left as it can
then as far right as it can, and finally, if it can't go any farther,
it deletes the node.*/
void BST::inOrderDelete(BSTNode*& pTree)
{
	if (pTree != nullptr)
	{
		inOrderDelete(pTree->getLeft());
		inOrderDelete(pTree->getRight());
		delete pTree;
	}
}
//Sets root to newRoot
void BST::setRoot(BSTNode* const newRoot)
{
	this->root = newRoot;
}

//Calls private insert()
void BST::insert(const char newText, const string newMorse)
{
	this->insert(root, newText, newMorse);
}

/*Recursively inserts a node by traversing list, comparing values to value being inserted,
and once the pointer to the side that it should follow is a nullptr, that pointer is set
to point to a new node with the */
void BST::insert(BSTNode*& pTree, const char newText, const string newMorse)
{
	if (pTree == nullptr)
	{
		pTree = new BSTNode(newText, newMorse);
	}
	else if (newText > pTree->getText())
	{
		insert(pTree->getRight(), newText, newMorse);
	}
	else if ( newText< pTree->getText()){
		insert(pTree->getLeft(), newText, newMorse);
	}
}
//calls private inOrder()
void BST::inOrder()
{
	this->inOrder(root);
}
/*Recursively prints out every node in the tree, the tree is traversed by going 
as far left as it can, then processing the node(printing it), and finally going all
the way right.*/
void BST::inOrder(BSTNode*& pTree)
{
	if (pTree != nullptr)
	{
		inOrder(pTree->getLeft());
		cout << pTree->getText() << " " << pTree->getMorse() << endl;
		inOrder(pTree->getRight());
	}
}

/* If char passed in is a lowercase letter, it turns it into an upper case
so that the private search functions works the way it should when called in this
public search function*/
void BST::search(char Text)
{
	char lowerText = '\0';
	if ((Text >= 65 && Text <= 90) || (Text >= 97 && Text <=122))
	{
		 lowerText = toupper(Text);
		 this->search(lowerText, root);
	}
	else {
		this->search(Text, root);
	}
	
}

/*Recursively searches for the char passed in in the same way nodes are inserted.
Depending on ascii value, the function calls itself passing in the right or
left pointer of the current tree, as needed. When found, Morse translation of char 
is printed out to the screen.*/
void BST::search(const char Text, BSTNode*& pTree)
{
	if (pTree != nullptr)
	{
		if (Text == pTree->getText())
		{
			cout << pTree->getMorse() << " ";
		}
		else if (Text > pTree->getText())
		{
			search(Text, pTree->getRight());
		}
		else if (Text < pTree->getText())
		{
			search(Text, pTree->getLeft());
		}
	}
}


