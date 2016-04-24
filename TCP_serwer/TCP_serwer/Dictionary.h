#pragma once
#include <vector>
#include <string>
class Dictionary
{
public:
	Dictionary();
	bool CheckWord(std::string);
private:
	void LoadWords();
	std::vector<std::string> words[30];

};
