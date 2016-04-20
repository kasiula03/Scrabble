#include "Word.h"
#include <iostream>

using namespace std;

Letter Word::allLeters[32];

Word::Word()
{
	
	//letters = new Letter[word.length()];
	this->word = "";
	//cout << "Total points: " << TotalPoints();
	
}
Word::~Word()
{
	letters.clear();
}
bool Word::compareTwoLeters(const Letter* lt1, const Letter* lt2)
{
	if (lt1->pos_y == lt2->pos_y)
		return (lt1->pos_x < lt2->pos_x);
	else
		return (lt1->pos_y < lt2->pos_y);
}
void Word::addLetter(Letter * letter)
{
	letters.push_back(letter);
	
	//this->word += letter.GetSign();
	//cout << letter.GetSign();
}
void Word::deleteLetter(Letter * letter)
{
	for (int i = 0; i < letters.size(); i++)
	{
		if(letters[i]->id == letter->id)
		{
			letters.erase(letters.begin()+i);
			//cout << "To ta sama";
		}
	}
	
}
void Word::deleteAllLetter()
{
	if(letters.size() > 0)
		letters.clear();
}
bool Word::LetterExist(Letter * letter)
{
	for (int i = 0; i < letters.size(); i++)
	{
		if (letters[i]->id == letter->id)
		{
			return true;
		}
	}
	return false;
}
int Word::TotalPoints()
{
	int total = 0;
	for (int i = 0; i < word.length(); i++)
	{
		int j = 0;
		while (allLeters[j].GetSign() != word[i])
		{
			j++;
		}
		total += allLeters[j].GetPoints();

	}
	return total;
}