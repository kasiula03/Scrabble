#pragma once

#include "Word.h"
#include "Field.h"
class WordController
{
	
public:
	WordController();
	bool QuickCheck(Field board[15][15], vector <Letter*>* existLetters, Word * word);
	int SolidTest(Field board[15][15], vector <Letter*>* existLetters, Word * word);

	Field * GetField(Field board[15][15], vector <Letter*>* existLettersL,int pos_x, int pos_y);
	Field * GetBoardField(Field board[15][15], vector <Letter*>* existLetters, Letter * letter);
	Letter * GetLetterOnBoard(Field board[15][15], vector <Letter*>* existLetters, Field *);
	int CountPoints(Field board [15][15], vector <Letter*>* existLetters, Word * word);

	Word * CheckHorizontal(Field board[15][15], vector <Letter*>* existLetters, Letter * letter);
	Word * CheckVertical(Field board[15][15], vector <Letter*>* existLetters,Letter * letter);

	bool CheckIfLetterExist(Word * word, Letter * letter);
private:
	bool horizontal;
	bool vertical;
	//vector <Letter*>* existLetters;

};