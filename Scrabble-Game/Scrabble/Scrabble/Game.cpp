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

void Game::SetLetters()
{
	Word::allLeters[0] = Letter('A', 1);
	Word::allLeters[1] = Letter('¥', 5);
	Word::allLeters[2] = Letter('B', 3);
	Word::allLeters[3] = Letter('C', 6);
	Word::allLeters[4] = Letter('Æ', 6);
	Word::allLeters[5] = Letter('D', 2);
	Word::allLeters[6] = Letter('E', 1);
	Word::allLeters[7] = Letter('Ê', 5);
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
	Word::allLeters[18] = Letter('Ñ', 7);
	Word::allLeters[19] = Letter('O', 1);
	Word::allLeters[20] = Letter('Ó', 5);
	Word::allLeters[21] = Letter('P', 2);
	Word::allLeters[22] = Letter('R', 1);
	Word::allLeters[23] = Letter('S', 1);
	Word::allLeters[24] = Letter('Œ', 5);
	Word::allLeters[25] = Letter('T', 2);
	Word::allLeters[26] = Letter('U', 3);
	Word::allLeters[27] = Letter('W', 1);
	Word::allLeters[28] = Letter('Y', 2);
	Word::allLeters[29] = Letter('Z', 1);
	Word::allLeters[30] = Letter('', 9);
	Word::allLeters[31] = Letter('¯', 5);
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

			
			
			/*if (event.type == sf::Event::TextEntered)
			{
				// Handle ASCII characters only
				if (event.text.unicode < 128)
				{
					str += static_cast<char>(event.text.unicode);
					texts[1].setString(str);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && str.length() > 0)
			{
				str.erase(str.length() - 1, str.length());
				texts[1].setString(str.c_str());
			}*/ 

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
