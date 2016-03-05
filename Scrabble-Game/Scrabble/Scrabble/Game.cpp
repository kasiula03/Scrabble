#include "Game.h"
#include <iostream>

using namespace std;

Font Game::font;

Game::Game(int a)
{
	SetLetters();
	state = MENU;
	if (!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBox(NULL, "Fond not found", "ERROR", NULL);
		return;
	}
	RunGame();
	
}

void Game::SetLetters()
{
	Word::allLeters[0] = Letter('A', 1);
	Word::allLeters[1] = Letter('•', 5);
	Word::allLeters[2] = Letter('B', 3);
	Word::allLeters[3] = Letter('C', 6);
	Word::allLeters[4] = Letter('∆', 6);
	Word::allLeters[5] = Letter('D', 2);
	Word::allLeters[6] = Letter('E', 1);
	Word::allLeters[7] = Letter(' ', 5);
	Word::allLeters[8] = Letter('F', 5);
	Word::allLeters[9] = Letter('G', 3);
	Word::allLeters[10] = Letter('H', 3);
	Word::allLeters[11] = Letter('I', 1);
	Word::allLeters[12] = Letter('J', 3);
	Word::allLeters[13] = Letter('K', 2);
	Word::allLeters[14] = Letter('L', 2);
	Word::allLeters[15] = Letter('£', 3);
	Word::allLeters[16] = Letter('M', 2);
	Word::allLeters[17] = Letter('N', 1);
	Word::allLeters[18] = Letter('—', 7);
	Word::allLeters[19] = Letter('O', 1);
	Word::allLeters[20] = Letter('”', 5);
	Word::allLeters[21] = Letter('P', 2);
	Word::allLeters[22] = Letter('R', 1);
	Word::allLeters[23] = Letter('S', 1);
	Word::allLeters[24] = Letter('å', 5);
	Word::allLeters[25] = Letter('T', 2);
	Word::allLeters[26] = Letter('U', 3);
	Word::allLeters[27] = Letter('W', 1);
	Word::allLeters[28] = Letter('Y', 2);
	Word::allLeters[29] = Letter('Z', 1);
	Word::allLeters[30] = Letter('è', 9);
	Word::allLeters[31] = Letter('Ø', 5);
}

void Game::RunGame()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			Menu();
			break;
		case GameState::GAME:
			Play();
			break;
		}

	}
}

void Game::Menu()
{
	bool menu = true;
	Event event;
	
	RenderWindow window(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
	

	Text tekst;
	tekst.setFont(font);
	tekst.setString("ddd");
	tekst.setPosition(50, 50);
	while (menu)
	{

		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				menu = false;
				state = END;
			}
		}
		window.draw(tekst);
		window.display();
	}
	
}

void Game::Play()
{
	RenderWindow window(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
	bool play = true;
	Event event;

	while (play)
	{
		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				play = false;
				state = END;
			}
		}
		window.display();
	}
}