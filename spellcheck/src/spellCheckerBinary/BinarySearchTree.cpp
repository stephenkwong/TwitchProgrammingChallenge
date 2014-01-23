
 // BinarySearchTree.cpp


#include "BinarySearchTree.h"
#include "string"
#include "math.h"
#include "stdlib.h"

#include "stdio.h"
#include "iostream"
#include "regExHelper.h"



//constructor
BinarySearchTree::BinarySearchTree()
{
	root = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
	if (root!= NULL)
	{
	   deleteTree(root);  //make sure we delete every single Node in the tree
	   root = NULL;
	}
}

int BinarySearchTree::heightOfTree(BinaryNode *node)
{
	if (node == NULL)
		return 0;

	return std::max(heightOfTree(node->left), heightOfTree(node->right)) + 1;
}

//public function so that somebody can free all the Nodes in our tree, since
//they won't have access to root
void BinarySearchTree::deleteTree(void)
{
	if (root != NULL)
	{
	   deleteTree(root);
	   root = NULL;
	}
}

void BinarySearchTree::deleteTree(BinaryNode *node)
{
   if (node != NULL)
   { //post-order traversal so we make sure that we get every node in tree
	   deleteTree(node->left);
	   deleteTree(node->right);
	   free (node);
	   node = NULL;
   }
}

//public function to insert into our binaryTree will always return true that insertion was successful
bool BinarySearchTree::insert(std::string s)
{
   BinaryNode *newNode = new BinaryNode(s);

   if (root == NULL)
   {
	   root = newNode;
	   return true;
   }

   root = insert(root, newNode);

   return true;
}

BinaryNode* BinarySearchTree::insert(BinaryNode *node, BinaryNode *insertNodeIntoTree)
{
    if (node->word.compare(insertNodeIntoTree->word) == 0)
    {
    	//no reason to re-add something in the list
        free (insertNodeIntoTree);
        insertNodeIntoTree = NULL;
    } //our nodeWord is greater so we need to go to the left of the tree
    else if (node->word.compare(insertNodeIntoTree->word) > 0)
    {
        if (node->left == NULL) //if the slot is open insert it there
        {
        	node->left = insertNodeIntoTree;
        }
        else //else keep traversing the tree until we find a free spot
        	node->left = insert(node->left, insertNodeIntoTree);
    }
    else
    {
       if (node->right == NULL)
       {
    	   node->right = insertNodeIntoTree;
       }
       else
    	   node->right = insert (node->right, insertNodeIntoTree);
    }


    //balancing the tree
    int balance = heightOfTree(node->left) - heightOfTree(node->right);

    if (balance > 1 && insertNodeIntoTree->word.compare(node->left->word) < 0)
      	return rotateLL(node);

    if (balance < -1 && insertNodeIntoTree->word.compare(node->right->word) > 0)
    	return rotateRR(node);

    if (balance > 1 && insertNodeIntoTree->word.compare(node->left->word) > 0)
    	return rotateLR(node);

    if (balance < -1 && insertNodeIntoTree->word.compare(node->right->word) < 0)
    	return rotateRL(node);

    return node;

}

//left rotate
BinaryNode * BinarySearchTree::rotateLL(BinaryNode *fakeRoot)
{
   BinaryNode *newRoot = fakeRoot->left;
   fakeRoot->left = newRoot->right;
   newRoot->right = fakeRoot;

   return newRoot;
}

//right rotate
BinaryNode * BinarySearchTree::rotateRR(BinaryNode *fakeRoot)
{
   BinaryNode *newRoot = fakeRoot->right;
   fakeRoot->right = newRoot->left;
   newRoot->left = fakeRoot;

   return newRoot;

}

//left right rotate
BinaryNode * BinarySearchTree::rotateLR(BinaryNode *fakeRoot)
{
   BinaryNode *left, *leftRight;

   left = fakeRoot->left;
   leftRight = left->right;

   left->right = leftRight->left;
   fakeRoot->left = leftRight->right;
   leftRight->left = left;
   leftRight->right = fakeRoot;


   return leftRight;
}

//right left rotate
BinaryNode * BinarySearchTree::rotateRL(BinaryNode * fakeRoot)
{
  BinaryNode *right, *rightLeft;

  right = fakeRoot->right;
  rightLeft = right->left;

  fakeRoot->right = rightLeft->left;
  right->left = rightLeft->right;
  rightLeft->left = fakeRoot;
  rightLeft->right = right;

  return rightLeft;
}

//this find is O(log n) time, we could have improved this by using the sortedWord
//member variable in our BinaryNode.  We would use the sortedWord as the key to the hash table
//then our find would be O(1)
bool BinarySearchTree::find(std::string s)
{
   BinaryNode *search = new BinaryNode(s);

   bool flag = find(root, search);

   free(search);
   search = NULL;

   if (flag)
	   return true;
   else
	   return false;
}

bool BinarySearchTree::find(BinaryNode *node, BinaryNode *search)
{
   if (node == NULL)
	   return false;

   if (node->word.compare(search->word) == 0)
	   return true;
   else if (node->word.compare(search->word) > 0)
	   return find(node->left, search);
   else
	   return find(node->right, search);
}


std::string BinarySearchTree::suggest(std::string s)
{
	BinaryNode *search = new BinaryNode(s);
	std::string NOSUGGEST = "NO SUGGESTION";

    if (find(s))
       return search->word;
    else
    { //change vowels and shorten multiple of words, and search through and see if we get lucky
      //and find our word
      std::vector<std::string> multiChars = regExHelper::multipleChars(search->word);


      for (int i = 0; i < multiChars.size(); i++)  //create list of all our multiple characters
      {                                                //and search through our tree to see if we find it
    	 if (find(multiChars[i]))                      //if we do then return the string
    	 {
    		 return multiChars[i];
    	 }
      }


      //now for all the multiple chars, call multiple vowels on each multiple chars to handle mistyped vowels
      std::vector<std::string> multiVowels;


      for (int i = 0; i < multiChars.size(); i++)
      {
    	  multiVowels = regExHelper::vowels(multiChars[i]);
    	  for (int j = 0; j < multiVowels.size(); j++)
    	  {
    		  if (find (multiVowels[j]))
    		  {
    			  return multiVowels[j];
    		  }
    	  }
      }
    }


    //if none of those returned, then we are going to take a huge guess
    //we are going to take our look at our great-grandparent in our binarySearchTree, and all of its siblings
    //and look for one that has less than 3 character differences, and then if there is one we will return
    //that value in the tree, else we are going to return no suggestion
    std::vector<BinaryNode *> *dontcare = new std::vector<BinaryNode *>();

    BinaryNode *greatGrandParent = findGreatGrandParent(root, search, dontcare);

    free(dontcare);
    dontcare = NULL;

    //BinaryNode found;
    return findThreeCharacterDifference(greatGrandParent, search);
}

//Goes to every sibling of the great-grandparent node, and then compares each one
//with the word that we are searching for, and then we pick one that has less than 4 character difference
//if there is more than a 4 character difference then we send back a NO SUGGESTION.
std::string BinarySearchTree::findThreeCharacterDifference(BinaryNode *node, BinaryNode *search)
{
   std::vector<BinaryNode *> temp;
   putIntoVec(node, &temp);  //puts all the siblings into an array
   BinaryNode * found;
   std::string NOSUGGEST = "NO SUGGESTION";

   int minDifference = search->word.length();
   int calcDifference = minDifference;


   //go through all the siblings and find the closet word
   for (int i = 0; i < temp.size(); i++)
   {
	  calcDifference = findNumOfCharacterDifference(search, temp[i]);

      if (calcDifference < minDifference)
      {
    	  minDifference = calcDifference;
    	  found = temp[i];
      }
   }

   //if found return
   if (minDifference < 4)
	   return found->word;

   //else we return NO SUGGESTION
   return NOSUGGEST;

}

//find difference in characters between binaryNodes
int BinarySearchTree::findNumOfCharacterDifference(BinaryNode *node1, BinaryNode *node2)
{
  int length1 = node1->word.length();
  int length2 = node2->word.length();

  int length = std::min(length1, length2);
  int difference = 0;

  //if one word is longer count those as differences
  difference = length2 - length1;
  if (difference < 0)
	  difference *= -1;

  //goes through both words, and when there is a difference adds one
  for (int i = 0; i < length; i++)
  {
	  if (node1->word[i] != node2->word[i])
		  difference ++;
  }

  return difference;
}

//inorder traversal puts all the nodes into a vector
//this is used when we find our great grand parent and we want every single node, so we can
//check to our word.
void BinarySearchTree::putIntoVec(BinaryNode *node, std::vector<BinaryNode *> *vec)
{
	if (node != NULL)
	{
		putIntoVec(node->left, vec);
		vec->push_back(node);
		putIntoVec(node->right, vec);
	}
}

//we are going to find the great grand parent while we are traversing the tree.  this will take O(log n) time
//Every Node we visit we are going to push onto the stack, until we get to the bottom of the tree
//once we get to the bottom we just have to pop off the top 4 nodes and return the 4th node.
//if there are less than 4 nodes in our stack, then just grab the one at the bottom since that will be the highest
//parent
BinaryNode * BinarySearchTree::findGreatGrandParent(BinaryNode *node, BinaryNode *search, std::vector<BinaryNode *> *stackVisited)
{
	//reached the bottom of the tree
   if (node == NULL)
   {
	   if (stackVisited->size() < 0)
		   return new BinaryNode("NO SUGGESTION");
	   if (stackVisited->size() <= 4)  //our tree wasn't that big, and we didn't even travel 4 levels down, so just grab the
	   {                               //one that is at the bottom of the stack or in this case first element in vector
		   return stackVisited->front();
	   }
	   else
	   {  //by popping the 4 nodes this one will be the great grand parent.
		   stackVisited->pop_back();
		   stackVisited->pop_back();
		   stackVisited->pop_back();
		   return stackVisited->back();
	   }
   }

   stackVisited->push_back(node);

   //regular traversal of tree trying to find a word
   if (node->word.compare(search->word) == 0)
   {  //we should never hit this case since we haven't found it already
	   return node;
   }
   else if (node->word.compare(search->word) > 0)
   {
	   return findGreatGrandParent(node->left, search, stackVisited);
   }
   else
   {
	   return findGreatGrandParent(node->right, search, stackVisited);
   }

}
