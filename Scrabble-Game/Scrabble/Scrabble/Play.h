#pragma once

#include <SFML\Graphics.hpp>
#include <cstring>
#include "GlobalFunctions.h"
#include "Field.h"
#include "Client.h"
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
	vector<Letter> existLetters;

	string str;

	bool ourTurn;
	bool canWrite;

	void Start(string playerName);
	void RandomLetters();
	bool CheckLetter(Letter letter, int & x, int & y);
	void LettersUpdate();
	void WriteControl(Event &);

	void PrepareBoard();
	void SetLetters();
	void Display();

};