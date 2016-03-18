#pragma once
#include "Word.h"
#include <Windows.h>
#include "Client.h"
#include <thread>
class Game
{
public:
	Game(int);
	void operator()()
	{
		RunGame();
	}
	thread * gameThread; // Watek gry
	thread * clientThread; // Watek klienta

private:
	enum GameState { MENU, GAME, GAME_OVER, END, AUTHORIZATION };
	GameState state;

	Client * client;

	static Font font;
	bool online;

	void SetLetters();

	//main game functions
	void RunGame();
	void Menu();
	void Play();
	void Authorization();

	

	//helpfull functions

	Text setText(string, int, int);
};