#pragma once
#include "Word.h"
#include <Windows.h>
class Game
{
public:
	Game(int);

private:
	enum GameState { MENU, GAME, GAME_OVER, END };
	GameState state;

	static Font font;

	void SetLetters();

	//main game functions
	void RunGame();
	void Menu();
	void Play();
};