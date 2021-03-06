#pragma once
#include "Word.h"
#include <Windows.h>
#include "Client.h"
#include "Play.h"
#include "Login.h"
#include "Button.h"
#include "Register.h"
#include <thread>
class Game : public Play, public Login, public Register
{
public:
	Game(int);
	void operator()() // thread function
	{
		RunGame();
	}
	string playerName;
	static int ID;

private:
	enum GameState { MENU, GAME, GAME_OVER, END, AUTHORIZATION, REGISTER };
	GameState state;

	Client * client;

	thread * gameThread; // Watek gry
	thread * clientThreadRecv;

	static Font font;
	static bool online;

	RenderWindow * window;

	Sprite menuBackground;
	Texture menuTexture;
	
	Button scrabbleButton;
	Button loginButton;
	Button registerButton;
	Button reconnectButton;
	Button gameButton;
	
	Text texts[4];

	//main game functions
	void Inatialize();

	void RunGame();
	void Menu();
	void Play();
	void Authorization();
	void Register();

	void Display();

};