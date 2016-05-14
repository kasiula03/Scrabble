#include "Word.h"
#include <iostream>

using namespace std;


Word::Word()
{
	this->word = "";
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
}
void Word::deleteLetter(Letter * letter)
{
	for (int i = 0; i < letters.size(); i++)
	{
		if(letters[i]->id == letter->id)
		{
			letters.erase(letters.begin()+i);
		}
	}
	
}
void Word::deleteAllLetter()
{
	if(letters.size() > 0)
		letters.clear();
}
void Word::DisplayWord()
{
	cout << endl;
	for (int i = 0; i < letters.size(); i++)
	{
		cout << letters.at(i)->GetSign();
	}
	cout << endl;
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
