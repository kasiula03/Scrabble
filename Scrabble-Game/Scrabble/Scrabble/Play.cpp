#include "Play.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
Font Play::font;

Play::Play()
{
	
	if (!font.loadFromFile("data/WorkSans-Black.otf"))
	{
		cout << "Fond not found" << endl;
		return;
	}
	if (!texture.loadFromFile("data//Graphs//GameLayout.png"))
	{
		std::cout << "Nie wczytano tekstury!" << std::endl;
	}
	Layout.setTexture(texture);
	
	GlobalFunctions::setText(Tplayers[0], "Brak", 1060, 150);
	GlobalFunctions::setText(Tplayers[1], "Brak", 1190, 150);
	GlobalFunctions::setText(Tplayers[2], "Brak", 1060, 215);
	GlobalFunctions::setText(Tplayers[3], "Brak", 1190, 215);

	countTexts = 0;
	ourTurn = true;
	this->canWrite = false;
	SetLetters();
	PrepareBoard();
	//allLeters[0].setPosition(200, 200);
	//allLeters[1].setPosition(240, 200);
	//existLetters.push_back(Letter(allLeters[0]));
	//existLetters.push_back(Letter(allLeters[1]));
	
	RandomLetters();
}

void Play::PrepareBoard()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			board[i][j] = Field(188 + (i*40), 30 + (j * 40));
			board[i][j].occupied = false;
		}
	}
}

void Play::RandomLetters()
{
	srand(time(NULL));

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int k = rand() % 32;
			allLeters[k].setPosition((1070 + i * 40), (300 + j * 40));
			existLetters.push_back(Letter(allLeters[k]));
		}
	}
}

bool Play::CheckLetter(Letter letter, int & x, int & y)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (!board[i][j].occupied)
			{
				int dist_x = abs(letter.getPositionX() - board[i][j].getPositionX() + 10);
				int dist_y = abs(letter.getPositionY() - board[i][j].getPositionY() + 25);

				if (dist_x < 30 && dist_x > 0 && dist_y < 30 && dist_y > 0)
				{
					x = board[i][j].getPositionX();
					y = board[i][j].getPositionY();
					board[i][j].occupied = true;
					return true;
				}
				
			}
			
		}
	}
	return false;
}

void Play::SetLetters()
{
	allLeters[0] = Letter('A', 1);
	allLeters[1] = Letter('•', 5);
	allLeters[2] = Letter('B', 3);
	allLeters[3] = Letter('C', 6);
	allLeters[4] = Letter('∆', 6);
	allLeters[5] = Letter('D', 2);
	allLeters[6] = Letter('E', 1);
	allLeters[7] = Letter(' ', 5);
	allLeters[8] = Letter('F', 5);
	allLeters[9] = Letter('G', 3);
	allLeters[10] = Letter('H', 3);
	allLeters[11] = Letter('I', 1);
	allLeters[12] = Letter('J', 3);
	allLeters[13] = Letter('K', 2);
	allLeters[14] = Letter('L', 2);
	allLeters[15] = Letter('£', 3);
	allLeters[16] = Letter('M', 2);
	allLeters[17] = Letter('N', 1);
	allLeters[18] = Letter('—', 7);
	allLeters[19] = Letter('O', 1);
	allLeters[20] = Letter('”', 5);
	allLeters[21] = Letter('P', 2);
	allLeters[22] = Letter('R', 1);
	allLeters[23] = Letter('S', 1);
	allLeters[24] = Letter('å', 5);
	allLeters[25] = Letter('T', 2);
	allLeters[26] = Letter('U', 3);
	allLeters[27] = Letter('W', 1);
	allLeters[28] = Letter('Y', 2);
	allLeters[29] = Letter('Z', 1);
	allLeters[30] = Letter('è', 9);
	allLeters[31] = Letter('Ø', 5);
}

void Play::LettersUpdate()
{
	for (int i = 0; i < existLetters.size(); i++)
	{
		if (ourTurn)
		{
			int prev_x = existLetters[i].getPositionX();
			int prev_y = existLetters[i].getPositionY();
			if (existLetters[i].dragAndDrop())
			{

				while (Mouse::isButtonPressed(Mouse::Left))
				{
					//playWindow->pollEvent(event);
					int x = Mouse::getPosition().x - 30;
					int y = Mouse::getPosition().y - 30;
					existLetters[i].setPosition(x, y);
					Display();
				}
				int xx, yy;

				if (CheckLetter(existLetters[i], xx, yy))
				{
					for (int i = 0; i < 15; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							if (prev_x == board[i][j].getPositionX() && prev_y == board[i][j].getPositionY())
								board[i][j].occupied = false;
						}

					}
					
					existLetters[i].setPosition(xx, yy);
					existLetters[i].placed = true;
				}
				else
				{
					existLetters[i].setPosition(prev_x, prev_y);
				}
			}
		}
	}
}

void Play::Start(string playerName)
{
	playWindow = new RenderWindow(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
	GlobalFunctions::setText(Tplayers[0], playerName, 1060, 150, 25);
	bool play = true;
	//string str = "";
	
	//GlobalFunctions::setText(txt, str, 1100, 500, 15);
	Event event;
	allLeters[0].setPosition(240, 30);
	
	this->canWrite = false;

	while (play)
	{
		Vector2i mousePos = Mouse::getPosition(*playWindow);
		if (client->messageReceived)
		{
			Text temp;
			string tekst = client->getReceivedMessage();
			

			GlobalFunctions::setText(temp, tekst, 1000, 450 + (15 * countTexts), 15);
			conversation.push_back(temp);
			countTexts++;
			client->messageReceived = false;
			if (conversation.size() > 11)
			{

				for (int i = 0; i < conversation.size() - 1; i++)
				{
					conversation[i] = conversation[i + 1];
					conversation[i].setPosition(conversation[i].getPosition().x, conversation[i].getPosition().y - 15);
				}
				conversation.pop_back();
				this->countTexts--;

			}
		}
		while (playWindow->pollEvent(event)) 
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				playWindow->close();
				play = false;
			}

			LettersUpdate();
			WriteControl(event);
		}
		
		Display();
	}
}
void Play::WriteControl(Event & event)
{
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
	{
		if (canWrite)
			canWrite = false;
		else
		{
			canWrite = true;
			
		}
	}

	if (event.type == sf::Event::TextEntered)
	{
		// Handle ASCII characters only
		if (this->canWrite)
		{
			if (event.text.unicode < 128 && event.text.unicode != 13)
			{
				str += static_cast<char>(event.text.unicode);

				GlobalFunctions::setText(tempTxt, str, 1000, 620, 15);

			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::BackSpace) && str.length() > 0)
	{
		str.erase(str.length() - 1, str.length());
		GlobalFunctions::setText(tempTxt, str, 1000, 620, 15);
	}
	if (str.length() > 0 && (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
	{
		Text temp;
		conversation.push_back(temp);
		std::thread sendThread(&Client::Send, &*client, str);
		sendThread.join();
		//client->Send(str);
		GlobalFunctions::setText(conversation[this->countTexts],"Ja: " + str, 1000, 450 + (15 * countTexts), 15);
		GlobalFunctions::setText(tempTxt, "", 1000, 620, 15);
		str = "";
		this->countTexts++;

		if (conversation.size() > 11)
		{
			
			for (int i = 0; i < conversation.size() - 1; i++)
			{
				conversation[i] = conversation[i + 1];
				conversation[i].setPosition(conversation[i].getPosition().x, conversation[i].getPosition().y - 15);
			}
			conversation.pop_back();
			this->countTexts--;
			
		}
	}
}
void Play::Display()
{
	playWindow->clear(Color(50, 50, 50, 255));
	
	playWindow->draw(Layout);
	playWindow->draw(Tplayers[0]);
	playWindow->draw(Tplayers[1]);
	playWindow->draw(Tplayers[2]);
	playWindow->draw(Tplayers[3]);
	playWindow->draw(tempTxt);
	for (int i = 0; i < conversation.size(); i++)
		playWindow->draw(conversation[i]);
	for (int i = 0; i < existLetters.size(); i++)
		playWindow->draw(existLetters[i]);

	/*for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			playWindow->draw(board[i][j]);
	}*/
	
	playWindow->display();
}
