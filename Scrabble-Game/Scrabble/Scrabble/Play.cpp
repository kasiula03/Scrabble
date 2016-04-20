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

	acceptWord = new Button("Zatwierdz slowo", 1040, 385);

	countTexts = 0;
	tour = 1;
	ourTurn = true;
	this->canWrite = false;
	SetLetters();
	PrepareBoard();
	
	for (int i = 0; i < 97; i++)
	{
		letterOccupied[i] = false;
	}

	RandomLetters();
	wordController = new WordController(&existLetters);
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
	board[0][0].setBonus("WyrazX3");
	board[7][0].setBonus("WyrazX3");
	board[14][0].setBonus("WyrazX3");
	board[0][7].setBonus("WyrazX3");
	board[0][14].setBonus("WyrazX3");
	board[7][14].setBonus("WyrazX3");
	board[14][14].setBonus("WyrazX3");
	board[14][7].setBonus("WyrazX3");
	
	board[1][1].setBonus("WyrazX2");
	board[2][2].setBonus("WyrazX2");
	board[3][3].setBonus("WyrazX2");
	board[4][4].setBonus("WyrazX2");
	board[7][7].setBonus("WyrazX2");
	board[10][10].setBonus("WyrazX2");
	board[11][11].setBonus("WyrazX2");
	board[12][12].setBonus("WyrazX2");
	board[13][13].setBonus("WyrazX2");

	board[13][1].setBonus("WyrazX2");
	board[12][2].setBonus("WyrazX2");
	board[11][3].setBonus("WyrazX2");
	board[10][4].setBonus("WyrazX2");
	board[4][10].setBonus("WyrazX2");
	board[3][11].setBonus("WyrazX2");
	board[2][12].setBonus("WyrazX2");
	board[1][13].setBonus("WyrazX2");

	board[3][0].setBonus("LiteraX2");
	board[11][0].setBonus("LiteraX2");
	board[6][2].setBonus("LiteraX2");
	board[8][2].setBonus("LiteraX2");
	board[0][3].setBonus("LiteraX2");
	board[7][3].setBonus("LiteraX2");

	board[14][3].setBonus("LiteraX2");
	board[2][6].setBonus("LiteraX2");
	board[12][6].setBonus("LiteraX2");
	board[3][7].setBonus("LiteraX2");
	board[11][7].setBonus("LiteraX2");
	board[2][8].setBonus("LiteraX2");
	board[12][8].setBonus("LiteraX2");

	board[0][11].setBonus("LiteraX2");
	board[7][11].setBonus("LiteraX2");
	board[14][11].setBonus("LiteraX2");
	board[6][12].setBonus("LiteraX2");
	board[8][12].setBonus("LiteraX2");
	board[3][14].setBonus("LiteraX2");
	board[11][14].setBonus("LiteraX2");

	board[5][1].setBonus("LiteraX3");
	board[9][1].setBonus("LiteraX3");
	board[1][5].setBonus("LiteraX3");
	board[13][5].setBonus("LiteraX3");
	board[1][9].setBonus("LiteraX3");
	board[13][9].setBonus("LiteraX3");
	board[5][13].setBonus("LiteraX3");
	board[9][13].setBonus("LiteraX3");
}

void Play::RandomLetters()
{
	srand(time(NULL));
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (i + j == 4)
				break;
			int k = rand() % 98;
			while (letterOccupied[k])
			{
				k = rand() % 98;
			}
			allLeters[k].setPosition((1070 + i * 40), (300 + j * 40));
			allLeters[k].id = count;
			count++;
			existLetters.push_back(&allLeters[k]);
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
Field * Play::GetBoardField(Letter * letter)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (letter->getPositionX() == board[i][j].getPositionX() && letter->getPositionY() == board[i][j].getPositionY())
			{
				return &board[i][j];
			}
		}

	}
	return nullptr;
}
Letter * Play::GetLetterOnBoard(Field * field)
{
	for (int i = 0; i < existLetters.size(); i++)
	{
		if (field->getPositionX() == existLetters[i]->getPositionX() && field->getPositionY() == existLetters[i]->getPositionY())
		{
			return existLetters[i];
		}
	}
	return nullptr;
}

Field * Play::GetField(int pos_x, int pos_y)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j].getPositionX() == pos_x && board[i][j].getPositionY() == pos_y)
			{
				return &board[i][j];
			}
		}

	}
	return nullptr;
}

void Play::SetLetters()
{
	allLeters[0] = Letter('A', 1);
	allLeters[1] = Letter('A', 1);
	allLeters[2] = Letter('A', 1);
	allLeters[3] = Letter('A', 1);
	allLeters[4] = Letter('A', 1);
	allLeters[5] = Letter('A', 1);
	allLeters[6] = Letter('A', 1);
	allLeters[7] = Letter('A', 1);
	allLeters[8] = Letter('A', 1);

	allLeters[9] = Letter('¥', 5);

	allLeters[10] = Letter('B', 3);
	allLeters[11] = Letter('B', 3);

	allLeters[12] = Letter('C', 2);
	allLeters[13] = Letter('C', 2);
	allLeters[14] = Letter('C', 2);

	allLeters[15] = Letter('Æ', 6);

	allLeters[16] = Letter('D', 2);
	allLeters[17] = Letter('D', 2);
	allLeters[18] = Letter('D', 2);

	allLeters[19] = Letter('E', 1);
	allLeters[20] = Letter('E', 1);
	allLeters[21] = Letter('E', 1);
	allLeters[22] = Letter('E', 1);
	allLeters[23] = Letter('E', 1);
	allLeters[24] = Letter('E', 1);
	allLeters[25] = Letter('E', 1);

	allLeters[26] = Letter('Ê', 5);

	allLeters[27] = Letter('F', 5);

	allLeters[28] = Letter('G', 3);
	allLeters[29] = Letter('G', 3);

	allLeters[30] = Letter('H', 3);
	allLeters[31] = Letter('H', 3);

	allLeters[32] = Letter('I', 1);
	allLeters[33] = Letter('I', 1);
	allLeters[34] = Letter('I', 1);
	allLeters[35] = Letter('I', 1);
	allLeters[36] = Letter('I', 1);
	allLeters[37] = Letter('I', 1);
	allLeters[38] = Letter('I', 1);
	allLeters[39] = Letter('I', 1);

	allLeters[40] = Letter('J', 3);
	allLeters[41] = Letter('J', 3);

	allLeters[42] = Letter('K', 2);
	allLeters[43] = Letter('K', 2);
	allLeters[44] = Letter('K', 2);

	allLeters[45] = Letter('L', 2);
	allLeters[46] = Letter('L', 2);
	allLeters[47] = Letter('L', 2);

	allLeters[48] = Letter('£', 3);
	allLeters[49] = Letter('L', 2);

	allLeters[50] = Letter('M', 2);
	allLeters[51] = Letter('M', 2);
	allLeters[52] = Letter('M', 2);

	allLeters[53] = Letter('N', 1);
	allLeters[54] = Letter('N', 1);
	allLeters[55] = Letter('N', 1);
	allLeters[56] = Letter('N', 1);
	allLeters[57] = Letter('N', 1);

	allLeters[58] = Letter('Ñ', 7);

	allLeters[59] = Letter('O', 1);
	allLeters[60] = Letter('O', 1);
	allLeters[61] = Letter('O', 1);
	allLeters[62] = Letter('O', 1);
	allLeters[63] = Letter('O', 1);
	allLeters[64] = Letter('O', 1);

	allLeters[65] = Letter('Ó', 5);

	allLeters[66] = Letter('P', 2);
	allLeters[67] = Letter('P', 2);
	allLeters[68] = Letter('P', 2);

	allLeters[69] = Letter('R', 1);
	allLeters[70] = Letter('R', 1);
	allLeters[71] = Letter('R', 1);
	allLeters[72] = Letter('R', 1);

	allLeters[73] = Letter('S', 1);
	allLeters[74] = Letter('S', 1);
	allLeters[75] = Letter('S', 1);
	allLeters[76] = Letter('S', 1);

	allLeters[77] = Letter('Œ', 5);

	allLeters[78] = Letter('T', 2);
	allLeters[79] = Letter('T', 2);
	allLeters[80] = Letter('T', 2);

	allLeters[81] = Letter('U', 3);
	allLeters[82] = Letter('U', 3);

	allLeters[83] = Letter('W', 1);
	allLeters[84] = Letter('W', 1);
	allLeters[85] = Letter('W', 1);
	allLeters[86] = Letter('W', 1);

	allLeters[87] = Letter('Y', 2);
	allLeters[88] = Letter('Y', 2);
	allLeters[89] = Letter('Y', 2);
	allLeters[90] = Letter('Y', 2);

	allLeters[91] = Letter('Z', 1);
	allLeters[92] = Letter('Z', 1);
	allLeters[93] = Letter('Z', 1);
	allLeters[94] = Letter('Z', 1);
	allLeters[95] = Letter('Z', 1);

	allLeters[96] = Letter('', 9);
	allLeters[97] = Letter('¯', 5);
}

void Play::LettersUpdate()
{
	for (int i = 0; i < existLetters.size(); i++)
	{
		if (ourTurn)
		{
			int prev_x = existLetters[i]->getPositionX();
			int prev_y = existLetters[i]->getPositionY();
			if (existLetters[i]->dragAndDrop(playWindow))
			{

				while (Mouse::isButtonPressed(Mouse::Left))
				{
					sf::Vector2i pozycjaMyszyWzgledemOkna = sf::Mouse::getPosition(*playWindow);
					sf::Vector2f pozycjaMyszyNaScenie = playWindow->mapPixelToCoords(pozycjaMyszyWzgledemOkna);
					int x = pozycjaMyszyNaScenie.x;
					int y = pozycjaMyszyNaScenie.y;
					existLetters[i]->setPosition(x, y);
					Display();
				}
				int xx, yy;

				if (CheckLetter(*existLetters[i], xx, yy))
				{
					for (int i = 0; i < 15; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							if (prev_x == board[i][j].getPositionX() && prev_y == board[i][j].getPositionY())
								board[i][j].occupied = false;
						}

					}
					
					existLetters[i]->setPosition(xx, yy);
					existLetters[i]->placed = true;
					if(!(newWord->LetterExist(existLetters[i])))
						newWord->addLetter(existLetters[i]);
				}
				else
				{
					existLetters[i]->setPosition(prev_x, prev_y);
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
	newWord = new Word();
	/*newWord->addLetter(existLetters[0]);
	newWord->addLetter(existLetters[2]);
	newWord->addLetter(existLetters[1]);
	newWord->addLetter(existLetters[3]);
	newWord->addLetter(existLetters[5]);
	newWord->deleteLetter(existLetters[1]);*/
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
			if (acceptWord->ifMousePressed(playWindow))
			{
				if (wordController->QuickCheck(newWord))
				{
					cout << "QuickTest: TRUE" << endl;
					if (tour == 1)
					{
						cout << "Punkty: " << wordController->CountPoints(board, newWord);
					}
					if (tour > 1)
					{
						wordController->SolidTest(board, newWord);
					}
				}
				else
					cout << "FALSE" << endl;
				//cout << "Punkty: " << CheckWord() << endl;
				newWord->deleteAllLetter();
				tour++;
			}
		}
		
		Display();
	}
}

int Play::CheckWord()
{
	Word * tempWord = new Word();
	cout << "Size: " << newWord->letters.size() << endl;
	if (newWord->letters.size() > 0)
	{

		sort(newWord->letters.begin(), newWord->letters.end(), Word::compareTwoLeters); // sortujemy litery ze wzgledu na pozycje lewo-prawo lub gora-dol
		
		bool horizontal = false;

		/*if (newWord->letters.size() > 1)
		{
			if (newWord->letters[0]->getPositionY() == newWord->letters[1]->getPositionY())
			{
				horizontal = true;
			}
			else
				horizontal = false;
		}*/
		int pos_x = newWord->letters[0]->getPositionX();
		int pos_y = newWord->letters[0]->getPositionY();
		Field * begin = GetField(pos_x, pos_y);
		//if (horizontal)
		//{
			//Wyszukanie slowa w poziome
			while (GetLetterOnBoard(begin) != nullptr) 
			{
				pos_x -= 40;
				//cout << GetLetterOnBoard(begin)->GetSign() << endl;
				begin = GetField(pos_x, pos_y); //puste pole za pierwsze litera slowa
			}
			int counter = 0;
			pos_x += 40;
			begin = GetField(pos_x, pos_y);
			cout << "Otrzymane slowo: ";
			while (GetLetterOnBoard(begin) != nullptr)
			{
				cout << GetLetterOnBoard(begin)->GetSign();
				counter++;
				pos_x += 40;
				begin = GetField(pos_x, pos_y);
			}
			cout << "\nIlosc liter: " << counter << endl;
		//}
		//else
		//{
			begin = GetField(newWord->letters[0]->getPositionX(), newWord->letters[0]->getPositionY());
			//wyszukanie slowa w pionie
			while (GetLetterOnBoard(begin) != nullptr)
			{
				pos_y -= 40;
				//cout << GetLetterOnBoard(begin)->GetSign() << endl;
				begin = GetField(newWord->letters[0]->getPositionX(), pos_y); //puste pole za pierwsze litera slowa
			}
			counter = 0;
			pos_y += 40;
			begin = GetField(newWord->letters[0]->getPositionX(), pos_y);
			cout << "Otrzymane slowo: ";
			while (GetLetterOnBoard(begin) != nullptr)
			{
				cout << GetLetterOnBoard(begin)->GetSign();
				counter++;
				pos_y += 40;
				begin = GetField(newWord->letters[0]->getPositionX(), pos_y);
			}
			cout << "\nIlosc liter: " << counter << endl;
		//}

		int points = 0;
		int premiaSlowa = 1;
		Field * temp;
		for (int i = 0; i < newWord->letters.size(); i++)
		{
			temp = GetBoardField(newWord->letters[i]);

			if (temp->bonus == "LiteraX2")
			{
				points += newWord->letters[i]->GetPoints() * 2;
			}
			else if (temp->bonus == "LiteraX3")
			{
				points += newWord->letters[i]->GetPoints() * 3;
			}
			else if (temp->bonus == "WyrazX2")
			{
				points += newWord->letters[i]->GetPoints();
				premiaSlowa *= 2;
			}
			else if (temp->bonus == "WyrazX3")
			{
				points += newWord->letters[i]->GetPoints();
				premiaSlowa *= 3;
			}
			else
			{
				points += newWord->letters[i]->GetPoints();
			}
		}
		points *= premiaSlowa;

		

		delete tempWord;
		return points;
	}

	return 0;
	
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
		playWindow->draw(*(existLetters[i]));

	playWindow->draw(*acceptWord);
	/*for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			playWindow->draw(board[i][j]);
	}*/
	
	playWindow->display();
}
