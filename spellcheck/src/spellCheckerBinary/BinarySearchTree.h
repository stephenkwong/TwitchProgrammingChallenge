
//BinarSearchTree.h


#ifndef BINARSEARCHTREE_H_
#define BINARSEARCHTREE_H_

#include "string"
#include "BinaryNode.h"
#include "vector"

class BinarySearchTree
{

public:
	BinarySearchTree();
	~BinarySearchTree();

	bool insert(std::string s);
	bool find(std::string s);
	std::string suggest(std::string s);
	void deleteTree(void);

private:
	int heightOfTree(BinaryNode *node);
	void deleteTree(BinaryNode *node);
	BinaryNode* insert(BinaryNode *node, BinaryNode *insertNodeIntoTree);


	//the four rotation functions to make sure that we have a balanced tree
	BinaryNode * rotateLL(BinaryNode *fakeRoot);
	BinaryNode * rotateRR(BinaryNode *fakeRoot);
	BinaryNode * rotateLR(BinaryNode *fakeRoot);
	BinaryNode * rotateRL(BinaryNode * fakeRoot);

	bool find(BinaryNode *node, BinaryNode *search);

	void putIntoVec(BinaryNode *node, std::vector<BinaryNode *> *vec);
	int findNumOfCharacterDifference(BinaryNode *node1, BinaryNode *node2);

	BinaryNode * findGreatGrandParent(BinaryNode *node, BinaryNode *search, std::vector<BinaryNode *> *stackVisited);
	std::string findThreeCharacterDifference(BinaryNode *node, BinaryNode *search);

	BinaryNode *root; //the only member variable


};



#endif
