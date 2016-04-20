#pragma once

#include "Word.h"
#include "Field.h"
class WordController
{
	
public:
	WordController(vector<Letter*>*);
	bool QuickCheck(Word *);
	bool SolidTest(Field board[15][15], Word * word);

	Field * GetField(Field board[15][15],int pos_x, int pos_y);
	Field * GetBoardField(Field board[15][15], Letter * letter);
	Letter * GetLetterOnBoard(Field board[15][15], Field *);
	int CountPoints(Field board [15][15], Word * word);

	Word * CheckHorizontal(Field board[15][15], Letter * letter);
	Word * CheckVertical(Field board[15][15], Letter * letter);
private:
	bool horizontal;
	bool vertical;
	vector <Letter*>* existLetters;
};