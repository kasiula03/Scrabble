#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Font Game::font;


Game::Game(int a)
{
	client = new Client();
	SetLetters();
	state = MENU;
	if (!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBox(NULL, "Fond not found", "ERROR", NULL);
		return;
	}

	
	gameThread = new thread(*this); 

	clientThread = new thread(*client); 
	//thread watek1(*client); // Watek klienta
	if (clientThread->joinable())
		clientThread->join();

	
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
		}

	}
}

void Game::Menu()
{
	bool menu = true;
	Event event;
	string str;
	RenderWindow window(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
	

	Text texts[5];
	Text txtIfOffline = setText("Kliknij tutaj aby sprobwac \npolaczyc sie z serwerem",10,45);

	texts[1] = setText("Scrabble", window.getSize().x / 2.5, 10);
	texts[1].setScale(1.5, 1.5);
	texts[2] = setText("Zaloguj sie", 20, 200);
	

	if (client->CheckIfConnected())
	{
		online = true;
		texts[0] = setText("Gra w trybie online",10,10);
		client->Send("Polaczylem");
		//std::thread watek1(*client);
		
	}
	else
	{
		online = false;
		texts[0] = setText("Gra w trybie offline", 10, 10);
		MessageBox(NULL, "Nie udalo polaczyc sie z serwerem, grasz w trybie offline", "ERROR", NULL);
	}
	while (menu)
	{
		Vector2f mouse(Mouse::getPosition());
		while (window.pollEvent(event))
		{

			Vector2f pos(texts[2].getGlobalBounds().left, texts[2].getGlobalBounds().top);
			Vector2f size(texts[2].getGlobalBounds().width, texts[2].getGlobalBounds().height);
			FloatRect newRect(static_cast < Vector2f >(window.mapCoordsToPixel(pos)), static_cast < Vector2f >(window.mapCoordsToPixel(size)));

			Vector2f pos2(txtIfOffline.getGlobalBounds().left, txtIfOffline.getGlobalBounds().top);
			Vector2f size2(txtIfOffline.getGlobalBounds().width, txtIfOffline.getGlobalBounds().height);
			FloatRect newRect2(static_cast < Vector2f >(window.mapCoordsToPixel(pos2)), static_cast < Vector2f >(window.mapCoordsToPixel(size2)));


			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				menu = false;
				state = END;
			}
			if (newRect.contains(static_cast <Vector2f>(Mouse::getPosition(window))))
			{
				texts[2].setColor(Color::Cyan);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					state = AUTHORIZATION;
					menu = false;
				}

			}
			else texts[2].setColor(Color::White);
			if (newRect2.contains(static_cast <Vector2f>(Mouse::getPosition(window))))
			{
				txtIfOffline.setColor(Color::Cyan);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					client = new Client();
					if (client->CheckIfConnected())
					{
						online = true;
						texts[0] = setText("Gra w trybie online", 10, 10);
						
					}
					else
					{
						online = false;
						texts[0] = setText("Gra w trybie offline", 10, 10);
						MessageBox(NULL, "Nie udalo polaczyc sie z serwerem", "ERROR", NULL);
					}
				}
			}
			else txtIfOffline.setColor(Color::White);
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
		
		//window.clear(Color(200, 200, 200));
		
		window.clear(Color(50,50,50,255));
		window.draw(texts[0]);
		window.draw(texts[1]);
		window.draw(texts[2]);
		if (!online) window.draw(txtIfOffline);
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
	
		window.clear(Color(50, 50, 50, 255));
		window.display();
	}
}

void Game::Authorization()
{
	RenderWindow window(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
	bool opened = true;
	while (opened)
	{
		Text txts[5];
		txts[0] = setText("Zaloguj sie", 100, 100);
		
		txts[1] = setText("Login: ", 70, 150);
		txts[2] = setText("Haslo: ", 70, 200);
		RectangleShape rec;
	
		rec.setSize(Vector2f(200, 200));
		rec.setPosition(90, 100);
		rec.setFillColor(Color(0,0,0,0));
		rec.setOutlineThickness(2);
		rec.setOutlineColor(Color::White);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			opened = false;
			state = MENU;
		}

		window.clear(Color(50, 50, 50, 255));
		window.draw(txts[0]);
		window.draw(txts[1]);
		window.draw(txts[2]);
		//window.draw(rec);
		window.display();
	}
}

Text Game::setText(string inscription, int pos_x, int pos_y)
{
	Text temp;
	temp.setFont(font);
	temp.setString(inscription);
	temp.setPosition(pos_x, pos_y);
	return temp;
}