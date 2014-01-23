
//regExHelper.h
//this class does two things
//return all the combination of vowels in a word and
//returns all the combinations of multiple characters


#ifndef REGEXHELPER_H_
#define REGEXHELPER_H_

#include "string"
#include "vector"

class regExHelper
{

public:
	static std::vector<std::string> vowels(std::string s);
	static std::vector<std::string> multipleChars(std::string s);

private:
	static bool twoOrMoreChars(std::string s);
	static bool threeOrMoreChars(std::string s);
	static std::string shrinkDown(std::string s);
	static std::vector<int> findLocationDouble(std::string s);
	static std::vector<int> findLocationVowels(std::string s);
	static void combine(std::vector<std::string> *vec, int start, std::vector<int> locationLetters, std::string s);
	static void combineVowels(std::vector<std::string> *vec, int start, std::vector<int> locationVowels, std::string s);

	static std::string standardVowels;

};




#endif
