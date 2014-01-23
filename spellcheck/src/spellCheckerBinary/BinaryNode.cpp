// BinaryNode.cpp


#include "BinaryNode.h"
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"

BinaryNode::BinaryNode()
{
    left = right = NULL;
    word = "";
}

BinaryNode::BinaryNode(std::string s)
{
	lowerTheWord(s); //sets word in our Node to all lower case

	left = right = NULL;
	sortWord();
}

bool BinaryNode::sortWord()
{
   char *tempString = new char[word.length()];
   char minChar;
   char temp;
   int lowestIndex = 0;

   std::strcpy(tempString, word.c_str());

   //just use selection sort worst case n^2 but the average length of a word
   //in the English word according to google is 5 so it shouldn't be that bad
   for (int i = 0; i < word.length() - 1; i++)
   {
	   lowestIndex = i;
	   minChar = tempString[lowestIndex];
	   for (int j = i+1; j < word.length(); j++)
	   {
		  if (tempString[j] < minChar)
		  {
			  minChar = tempString[j];
			  lowestIndex = j;
		  }
	   }

	   if (lowestIndex != i)
	   {
		   //swapping characters
		   temp = tempString[i];
		   tempString[i] = tempString[lowestIndex];
		   tempString[lowestIndex] = temp;
	   }
   }

   sortedWord = tempString;

   return true;
}

void BinaryNode::lowerTheWord(std::string s)
{
   char *tempString = new char[s.length() + 1];

   std::strcpy(tempString, s.c_str()); //didn't use strncpy for some reason couldn't find it in my includes

   for (int i = 0; i < s.length(); i++)
   {
	   tempString[i] = tolower(tempString[i]);
   }

   word = tempString;
}
