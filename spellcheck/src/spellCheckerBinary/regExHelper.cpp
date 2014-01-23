
//regExHelper.cpp


#include "regExHelper.h"
#include "stdio.h"
#include "stdlib.h"
#include "iostream"


std::string regExHelper::standardVowels = "aeiou";


//this was whole file annoying since regex isn't implemented in gcc. I choose a bad language to do this
//but I've taken the red pill, and I'm in too deep



//will return a vector of all the different combinations of vowels, for example
//if we have heat, it will return in a vector heat, heit, heet, heot, heut, haat, haet, hait, haot, haut, ...
//all the way to huut
std::vector<std::string> regExHelper::vowels(std::string s)
{
    std::vector<std::string> swappedVowels;

    //need to know where in the string the vowels are, this call returns a vector of ints of where the positions
    //of where the vowels are
    std::vector<int> locationVowels = findLocationVowels(s);

    swappedVowels.push_back(s);

    //recursive function to combine all the vowels
    combineVowels(&swappedVowels, locationVowels.size()-1, locationVowels, s);

    return swappedVowels;
}

//returns a vector of ints of where the positions of where the vowels are
std::vector<int> regExHelper::findLocationVowels(std::string s)
{
	std::vector<int> locations;

   for (int i = 0; i < s.length(); i++)
   {
	   if (s[i] == 'a' ||
		   s[i] == 'e' ||
		   s[i] == 'i' ||
		   s[i] == 'o' ||
		   s[i] == 'u')
	   {
	       locations.push_back(i);
	   }
   }

   return locations;
}

//recursive function that gives every combination of all the vowels in the word
//one vowel 5 cases, two vowels 25 cases, three vowels 125 cases.
void regExHelper::combineVowels(std::vector<std::string> *vec, int start, std::vector<int> locationVowels, std::string s)
{
	for (int i = start;i>= 0;i--)
	{
		std::string aString = s;
		std::string eString = s;
		std::string iString = s;
		std::string oString = s;
		std::string uString = s;

		aString.replace(locationVowels[i], 1, "a");
        eString.replace(locationVowels[i], 1, "e");
        iString.replace(locationVowels[i], 1, "i");
        oString.replace(locationVowels[i], 1, "o");
        uString.replace(locationVowels[i], 1, "u");

        if (s[locationVowels[i]] != 'a')
      	   vec->push_back(aString);

        if (s[locationVowels[i]] != 'e')
      	   vec->push_back(eString);
        if (s[locationVowels[i]] != 'i')
      	   vec->push_back(iString);
        if (s[locationVowels[i]] != 'o')
      	   vec->push_back(oString);
        if (s[locationVowels[i]] != 'u')
      	   vec->push_back(uString);

		if (i > 0)
		{
			if (s[locationVowels[i]] == 'e' || s[locationVowels[i]] == 'i' || s[locationVowels[i]] == 'o' || s[locationVowels[i]] == 'u')
			   combineVowels(vec, i-1, locationVowels, aString);

			if (s[locationVowels[i]] == 'a' || s[locationVowels[i]] == 'i' || s[locationVowels[i]] == 'o' || s[locationVowels[i]] == 'u')
			   combineVowels(vec, i-1, locationVowels, eString);

			if (s[locationVowels[i]] == 'a' || s[locationVowels[i]] == 'e' || s[locationVowels[i]] == 'o' || s[locationVowels[i]] == 'u')
			   combineVowels(vec, i-1, locationVowels, iString);

			if (s[locationVowels[i]] == 'a' || s[locationVowels[i]] == 'e' || s[locationVowels[i]] == 'i' || s[locationVowels[i]] == 'u')
			   combineVowels(vec, i-1, locationVowels, oString);

			if (s[locationVowels[i]] == 'a' || s[locationVowels[i]] == 'e' || s[locationVowels[i]] == 'i' || s[locationVowels[i]] == 'o')
			   combineVowels(vec, i-1, locationVowels, uString);
		}
	}
}

//this function does multiple things
//first it shrinks down all multiple of characters that are 3 and greater to just 2
//then it finds all the locations of where there are 2 or more characters together and then does a combination of all of them
//so for example if we have hhatt, it will return a vector
//hat, hatt, hhat, and hhatt
std::vector<std::string> regExHelper::multipleChars(std::string s)
{
  std::vector<std::string> versionOfWords;

  if (threeOrMoreChars(s)) //according to google, there aren't word in the English language 3 characters in a or more
	  s = shrinkDown(s); //so we are going to get rid of 3 or more characters

  if (twoOrMoreChars(s))
  {
      std::vector<int> locationLetters = findLocationDouble(s);

      versionOfWords.push_back(s); //original case

      combine(&versionOfWords, locationLetters.size() - 1, locationLetters, s);
      //this is the place where it randomly stops if our string length is greater than 8
      //it won't go out of this if statement.
  }
  else
  {  //case where there isn't two or more characters together just return the original string word
     versionOfWords.push_back(s);  //adds element to end of vector
  }

  return versionOfWords;

}

//recursive function that combines all the possibilities of two characters being together
//so for example if we have hhatt, it will pass by reference a vector
//hat, hatt, hhat, and hhatt
void regExHelper::combine(std::vector<std::string> *vec, int start, std::vector<int>locationLetters, std::string s)
{
	for (int i = start;i>= 0;i--)
	{
		std::string tempString = s;
		vec->push_back(tempString.erase(locationLetters[i],1));

		if (i > 0)
		{
			combine(vec, i-1, locationLetters, tempString);
		}
	}
}

//find two or more of the same characters in an row
bool regExHelper::twoOrMoreChars(std::string s)
{
   if (s.length() == 1)
	   return false;

   int prev = 0;
   for (int i = 1; i < s.length(); i++)
   {
	   if (s[prev] == s[i])
		   return true;
	   prev = i;
   }

   return false;
}

//find 3 or more of the same characters in a row
bool regExHelper::threeOrMoreChars(std::string s)
{
   if (s.length() <= 2)
	   return false;

   int prevPrev = 0;
   int prev = 1;

   for (int i = 2; i < s.length(); i++)
   {
	   if (s[prevPrev] == s[prev] && s[prev] == s[i])
		   return true;

	   prevPrev = prev;
	   prev = i;
   }

   return false;
}

//if somewhere in the string there are 3 characters or more, then it will shrink it down to only two letters
std::string regExHelper::shrinkDown(std::string s)
{
   std::string newString;
   int prevPrev = 0, prev = 1;

   newString.append(s, 0, 2); //adds first two characters to the string.

   //have two pointers only right when we know there are not 3 characters in a row.
   for (int i = 2; i < s.length(); i++)
   {
	   if (s[prevPrev] == s[prev] && s[prev] == s[i])
	   {
		   continue;
	   }

	   newString.append(s, i, 1);
	   prevPrev = prev;
	   prev = i;
   }

   return newString;
}

//finds the location in string of where there are double characters, and returns it in a vector
std::vector<int> regExHelper::findLocationDouble(std::string s)
{
   std::vector<int> locations;

   int prev = 0;
   for (int i = 1; i < s.length(); i++)
   {
	   if (s[prev] == s[i])
		   locations.push_back(prev);

	   prev = i;
   }

   return locations;
}
