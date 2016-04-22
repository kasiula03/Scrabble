#pragma once
#include "Letter.h"
#include <vector>
#include <iostream>
class Word
{
	friend class Game;

public:
	Word();
	~Word();
	int TotalPoints();
	static Letter allLeters[32]; //probably unnecessary

	void addLetter(Letter *);
	void deleteLetter(Letter *);
	void deleteAllLetter();
	bool LetterExist(Letter *);
	vector<Letter *> letters;

	void DisplayWord();

	static bool compareTwoLeters(const Letter*, const Letter*);
private:
	
	string word;
	
	
};