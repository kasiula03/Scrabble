#pragma once

#include <SFML\Graphics.hpp>
#include <cstring>
#include "GlobalFunctions.h"
#include "Field.h"
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

	Field board[15][15];
	Letter allLeters[32];

	void Start(string playerName);
	void randomLetters();

	void prepareBoard();
	void setLetters();
	void Display();

};