#include "Dictionary.h"
#include <fstream>
#include <iostream>


Dictionary::Dictionary()
{
	//LoadWords();
	std::cout << "SLOWNIK ZALADOWANY" << std::endl;
}
void Dictionary::LoadWords()
{
	std::ifstream file;
	file.open("data\\Slownik.txt", std::ios::in);
	char temp = 'a';
	int which = 0;
	int ile = 0;
	std::string word;

	if (file.good())
	{
		while (getline(file, word))
		{
			if (word[0] != temp)
			{
				temp = word[0];
				which++;
				system("cls");
				std::cout << "TRWA LADOWANIE SLOWNIKA" << std::endl;
				std::cout << ((float)ile / 2720949) * 100 << "%" << std::endl;
			}
			words[which].push_back(word);

			ile++;
		}
		system("cls");
		std::cout << "TRWA LADOWANIE SLOWNIKA" << std::endl;
		std::cout << "100%" << std::endl;
	}
	file.close();
}
bool Dictionary::CheckWord(std::string word)
{
	int x = 0;
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] == '\n')
		{
			x = i;
		}
	}
	word = word.substr(0, x);
	std::cout << "Slowo: " << word << std::endl;
	int which = 0;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 30; i++)
		{
			if ((words[i].at(0))[0] == word[0])
			{
				which = i;
				break;
			}
		}
		for (int i = 0; i < words[which].size(); i++)
		{
			if (words[which].at(i) == word)
				return true;
		}
	}
	std::cout << word.size() << std::endl;
	return false;
}