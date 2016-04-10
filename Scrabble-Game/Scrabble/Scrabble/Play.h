#pragma once

#include <SFML\Graphics.hpp>
#include <cstring>
#include "GlobalFunctions.h"
#include "Field.h"
#include "Client.h"
#include "Button.h"
#include "Word.h"
#include <vector>
using namespace sf;
using namespace std;

class Play
{
protected:
	Play();

	static Font font;

	RenderWindow * playWindow;

	Sprite Layout;
	Texture texture;
	Text Tplayers[4];

	Text tempTxt;

	vector<Text> conversation;
	int countTexts;
	Client * client;

	Field board[15][15];
	Letter allLeters[32];
	Letter letters[100];
	vector<Letter> existLetters;
	Word * newWord;

	Button * acceptWord;
	string str;

	bool ourTurn;
	bool canWrite;

	void Start(string playerName);
	void RandomLetters();
	bool CheckLetter(Letter letter, int & x, int & y);
	Field * GetBoardField(Letter * letter);
	Field * GetField(int pos_x, int pos_y);
	Letter * GetLetterOnBoard(Field *);
	void LettersUpdate();
	void WriteControl(Event &);
	int CheckWord();

	void PrepareBoard();
	void SetLetters();
	void Display();

};