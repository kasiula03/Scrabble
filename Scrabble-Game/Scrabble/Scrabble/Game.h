#pragma once
#include "Word.h"
#include <Windows.h>
#include "Client.h"
class Game
{
public:
	Game(int);

private:
	enum GameState { MENU, GAME, GAME_OVER, END };
	GameState state;

	Client client;

	static Font font;

	void SetLetters();

	//main game functions
	void RunGame();
	void Menu();
	void Play();
};