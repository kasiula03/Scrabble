#pragma once
#include "Letter.h"

class Word
{
	friend class Game;

public:
	Word(string);
	int TotalPoints();
	static Letter allLeters[32]; //probably unnecessary
private:
	
	string word;
	Letter * letters;
};