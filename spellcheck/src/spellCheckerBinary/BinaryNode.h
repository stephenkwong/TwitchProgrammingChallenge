
#ifndef BINARYNODE_H_
#define BINARYNODE_H_

#include "string"
#include "cstring"

class BinaryNode
{
public:
	std::string word;
	std::string sortedWord;  //this was going to be used as the key for the hash table to find in 0(1) but didn't implement

	BinaryNode * left;
	BinaryNode * right;

	BinaryNode();
	BinaryNode(std::string s);

	bool sortWord();

private:
    void lowerTheWord(std::string s);
};


#endif
