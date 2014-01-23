

#include <iostream>
#include "fstream"
#include "time.h"
#include "stdlib.h"

using namespace std;

int main()
{
    srand(time(NULL));

	ifstream myfile;
    myfile.open("3esl.txt"); //from Official 12Dicts Package http://wordlist.sourceforge.net/12dicts-readme-r5.html

    string word, search;

    int i = 0;
    int caseTest;
    int when = rand() % 500 + 1000;  //there are twenty thousand words so just pick a few


    while (getline(myfile, word))
    {
       if (i == when)
       {
    	   i = 0;
    	   caseTest = rand() % 3;

    	   //testing capital letter case
		   if (word.length() <= 7  && caseTest == 1)
		   {

			   for (int j = 0; j < word.length(); j++)
			   {
				   int upper = rand() % 2;
				   char ch;

				   if (upper)
				   {
					   ch = word.at(j);
					   ch = toupper(ch);

					   word[j] = ch;
				   }
			   }
			   cout << word << endl;
			   i++;
			   continue;

		   }

		   //testing multiple letter case
		   if (word.length() <=5 && caseTest ==2)
		   {

			  int rNum1 = rand() % word.length();
			  char ch1 = word.at(rNum1);
			  int rNum2 = rand() % word.length();
			  char ch2 = word.at(rNum2);

			  word.insert(rNum1, rNum1, ch1);
			  word.insert(rNum1+rNum2, rNum2, ch2);

			  cout << word << endl;
			  i++;
			  continue;

		   }

		   //testing incorrect vowel case
		   if (word.length() <=7 && caseTest == 0)
		   {
			  char vowels[] = {'a', 'e', 'i', 'o', 'u'};
			  int random = 0;
			  int position = -1;

              while (position < 0)
              {
            	 random = rand() % 5;  //pick random vowel to find in the word
			     position = word.find(vowels[random]);
              }


			  int randomVowel = rand() % 5;
			  while (randomVowel == random) //we don't want to replace it with the same vowel
				  randomVowel = rand() % 5;

			  word[position] = vowels[randomVowel];
			  cout << word << endl;
			  i++;
			  continue;
		   }
       }

       i++;
    }
    myfile.close();

    //cout << "0" << endl;
	return 0;
}
