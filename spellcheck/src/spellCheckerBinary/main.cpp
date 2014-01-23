

#include "iostream"
#include "BinaryNode.h"
#include "stdio.h"
#include "ctype.h"
#include "BinarySearchTree.h"
#include "regExHelper.h"
#include "fstream"
#include "vector"

using namespace std;



int main(void)
{
	ifstream myfile;
    myfile.open("3esl.txt"); //from Official 12Dicts Package http://wordlist.sourceforge.net/12dicts-readme-r5.html

    string word, search;


    BinarySearchTree *bTree = new BinarySearchTree();
    while (getline(myfile, word))  //get every word from the dictionary
    {
      	bTree->insert(word); //insert all the words into the binary tree
    }
    myfile.close();


    while (true)
    {
    	cout << "> ";
    	cin >> search;

    	if (search.at(0) == '0')  //Entering 0 will exit you out of the program
    		break;

    	cout << bTree->suggest(search) << endl;  //suggest spell checks what is entered
    }


   return 0;
}


