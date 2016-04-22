#pragma once

#include <SFML\Graphics.hpp>
#include <cstring>
#include "GlobalFunctions.h"
#include "Field.h"
#include "Client.h"
#include "Button.h"
#include "Word.h"
#include "WordController.h"
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
	Text textPoints;

	vector<Text> conversation;
	int countTexts;
	Client * client;

	Field board[15][15];
	Letter allLeters[98]; //all avaliable letters
	bool letterOccupied[98];
	int countLetter;
	
	vector<Letter *> existLetters;
	Word * newWord;
	WordController * wordController;

	int tour;
	int points;

	Button * acceptWord;
	string str;

	bool ourTurn;
	bool canWrite;
	bool roundOver;

	void Start(string playerName);
	void RandomLetters();
	bool CheckLetter(Letter letter, int & x, int & y);
	void addLetterToStand();
	bool CheckIfOver();
	void RestartLetters();

	void LettersUpdate();
	void WriteControl(Event &);

	Field * GetBoardField(Letter * letter);

	void PrepareBoard();
	void SetLetters();
	void Display();

};