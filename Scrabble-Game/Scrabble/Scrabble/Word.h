#pragma once
#include "Letter.h"

class Word
{
	friend class Game;

public:
	Word(string);
	int TotalPoints();

private:
	static Letter allLeters[32]; //probably unnecessary
	string word;
	Letter * letters;
};