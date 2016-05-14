#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Font Game::font;
bool Game::online;
int Game::ID;

Game::Game(int a)
{
	client = new Client();
	Play::client = this->client;
	
	SetLetters();
	GlobalFunctions::GlobalFunctions();
	state = MENU;
	if (!font.loadFromFile("data/WorkSans-Black.otf"))
	{
		MessageBox(NULL, "Fond not found", "ERROR", NULL);
		return;
	}
	if (!menuTexture.loadFromFile("data//Graphs//menuBackground2.png"))
	{
		std::cout << "Nie wczytano tekstury!" << std::endl;
	}
	menuBackground.setTexture(menuTexture);

	this->playerName = "Guest";

	gameThread = new thread(*this); 
	gameThread->join();

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
		case GameState::AUTHORIZATION:
			Authorization();
			break;
		case GameState::REGISTER:
			Register();
			break;
		}

	}
}

void Game::Menu()
{
	bool menu = true;
	Event event;
	
	Inatialize();

	
	while (menu)
	{
		Vector2f mouse(Mouse::getPosition());
		while (window->pollEvent(event))
		{

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				menu = false;
				state = END;
			}

			if (Keyboard::isKeyPressed(Keyboard::B))
			{
				menu = false;
				window->close();
				state = GAME;
			}

			//set text color when mouse is coliding and change state to Authorization

			if (loginButton.ifMousePressed(window))
			{
				state = AUTHORIZATION;
				menu = false;
			}
			if (gameButton.ifMousePressed(window))
			{
				state = GAME;
				menu = false;
			}
			if (registerButton.ifMousePressed(window))
			{
				state = REGISTER;
				menu = false;
			}
			if (reconnectButton.ifMousePressed(window))
			{
				if (client->ConnectToServer())
				{
					cout << "Polaczylem" << endl;
					//clientThreadSend = new thread(*client,"Wysylanie");
					clientThreadRecv = new thread(&Client::Listen, &*client);

					online = true;
					GlobalFunctions::setText(texts[0], "Gra w trybie online", 10, 10);
					client->connected = true;
				}
				else
				{
					online = false;
					GlobalFunctions::setText(texts[0], "Gra w trybie offline", 10, 10);
					MessageBox(NULL, "Nie udalo polaczyc sie z serwerem", "ERROR", NULL);
				}
			}

		}
		
		Display();
	}
	
}

void Game::Play()
{
	window->close();


	Start(playerName);
		
	state = MENU;
	Sleep(200);
}

void Game::Authorization()
{
	window->close();

	this->playerName = runLoginWindow();

	state = MENU;
	Sleep(200);
}

void Game::Register()
{
	window->close();

	runRegisterWindow();

	state = MENU;
	Sleep(200);
}

void Game::Inatialize()
{
	window = new RenderWindow(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);

	scrabbleButton = Button("Scrabble", window->getSize().x / 2.5, 10, 56);
	loginButton = Button("Zaloguj sie", 1170, 300);
	reconnectButton = Button("Kliknij tutaj aby sprobwac \npolaczyc sie z serwerem", 10, 50);
	registerButton = Button("Zarejestruj", 1170, 350);
	gameButton = Button("Graj", window->getSize().x / 2.5 + 20, 250, 75);

	if (!online)
	{
		if (client->CheckIfConnected())
		{
			online = true;
			GlobalFunctions::setText(texts[0], "Gra w trybie online", 10, 10);
			//client->Send("Polaczylem");
			//clientThreadSend = new thread(*client, "Wysylanie");
			clientThreadRecv = new thread(&Client::Listen, &*client);

		}
		else
		{
			online = false;
			GlobalFunctions::setText(texts[0], "Gra w trybie offline", 10, 10);
			MessageBox(NULL, "Nie udalo polaczyc sie z serwerem, grasz w trybie offline", "ERROR", NULL);
		}
	}
}

void Game::Display()
{
	window->clear(Color(50, 50, 50, 255));
	window->draw(menuBackground);

	window->draw(scrabbleButton);
	window->draw(texts[0]);
	window->draw(registerButton);
	if (!online) window->draw(reconnectButton);
	window->draw(loginButton);
	window->draw(gameButton);

	window->display();
}
