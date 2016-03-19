#pragma once
#include "Word.h"
#include <Windows.h>
#include "Client.h"
#include "Play.h"
#include <thread>
class Game : public Play
{
public:
	Game(int);
	void operator()() // thread function
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

	RenderWindow * window;

	Text texts[5];

	void SetLetters();

	//main game functions
	void Inatialize();

	void RunGame();
	void Menu();
	void Play();
	void Authorization();
	void Display();

	//helpfull functions

	Text setText(string, int, int);
};