#include "Play.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
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

	GlobalFunctions::setText(Tplayers[0], "Brak", 1110, 150);
	GlobalFunctions::setText(Tplayers[1], "Brak", 1240, 150);
	GlobalFunctions::setText(Tplayers[2], "Brak", 1110, 215);
	GlobalFunctions::setText(Tplayers[3], "Brak", 1240, 215);

	
	setLetters();
	prepareBoard();
	//allLeters[0].setPosition(200, 200);
	//allLeters[1].setPosition(240, 200);
	//existLetters.push_back(Letter(allLeters[0]));
	//existLetters.push_back(Letter(allLeters[1]));
	randomLetters();
}

void Play::prepareBoard()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			board[i][j] = Field(240 + (i*40), 30 + (j * 40));
			board[i][j].occupied = false;
		}
	}
}

void Play::randomLetters()
{
	srand(time(NULL));

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int k = rand() % 32;
			allLeters[k].setPosition((1120 + i * 40), (300 + j * 40));
			existLetters.push_back(Letter(allLeters[k]));
		}
	}
}

bool Play::checkLetter(Letter letter, int & x, int & y)
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

void Play::setLetters()
{
	allLeters[0] = Letter('A', 1);
	allLeters[1] = Letter('¥', 5);
	allLeters[2] = Letter('B', 3);
	allLeters[3] = Letter('C', 6);
	allLeters[4] = Letter('Æ', 6);
	allLeters[5] = Letter('D', 2);
	allLeters[6] = Letter('E', 1);
	allLeters[7] = Letter('Ê', 5);
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
	allLeters[18] = Letter('Ñ', 7);
	allLeters[19] = Letter('O', 1);
	allLeters[20] = Letter('Ó', 5);
	allLeters[21] = Letter('P', 2);
	allLeters[22] = Letter('R', 1);
	allLeters[23] = Letter('S', 1);
	allLeters[24] = Letter('Œ', 5);
	allLeters[25] = Letter('T', 2);
	allLeters[26] = Letter('U', 3);
	allLeters[27] = Letter('W', 1);
	allLeters[28] = Letter('Y', 2);
	allLeters[29] = Letter('Z', 1);
	allLeters[30] = Letter('', 9);
	allLeters[31] = Letter('¯', 5);
}

void Play::Start(string playerName)
{
	playWindow = new RenderWindow(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
	GlobalFunctions::setText(Tplayers[0], playerName, 1110, 150, 25);
	bool play = true;
	
	Event event;
	allLeters[0].setPosition(240, 30);
	while (play)
	{
		Vector2i mousePos = Mouse::getPosition(*playWindow);
		while (playWindow->pollEvent(event)) 
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				playWindow->close();
				play = false;
			}

			for (int i = 0; i < existLetters.size(); i++)
			{
				if (!existLetters[i].placed)
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

						if (checkLetter(existLetters[i], xx, yy))
						{
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
			/*if (allLeters[0].dragAndDrop())
			{
				while (Mouse::isButtonPressed(Mouse::Left))
				{
					//playWindow->pollEvent(event);
					int x = Mouse::getPosition().x - 30;
					int y = Mouse::getPosition().y - 30;
					allLeters[0].setPosition(x, y);
					Display();

				}
			}*/
		}
		
		Display();
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
	for (int i = 0; i < existLetters.size(); i++)
		playWindow->draw(existLetters[i]);
	/*for (int i = 1; i < 15; i++)
	{
		for (int j = 1; j < 15; j++)
			playWindow->draw(board[i][j]);
	}*/
	
	
	playWindow->display();
}
