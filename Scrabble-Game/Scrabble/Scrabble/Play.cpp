#include "Play.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <sstream>

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
	countLetter = 0;
	ourTurn = true;
	roundOver = false;
	this->canWrite = false;
	SetLetters();
	PrepareBoard();
	
	for (int i = 0; i < 98; i++)
	{
		letterOccupied[i] = false;
	}

	wordController = new WordController();
	
	
	//Packet pac(Packet::LetterToString(existLetters[0]),"Letter");
	//cout << pac.PacketToString();
	//pac = pac.stringToPacket(pac.PacketToString());
	//cout << pac.StringToLetter(pac.getData());
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
	
	for (int i = 0; i < 7; i++)
	{
		client->Send ((Packet::stringToPacket("LetterRequest\n")).PacketToString());
		
		//Sleep(50);
			
			/*
			if (i + j == 4)
				break;
			int k = rand() % 98;
			while (letterOccupied[k])
			{
				k = rand() % 98;
			}
			letterOccupied[k] = true;
			allLeters[k].setPosition((1070 + i * 40), (300 + j * 40));
			//allLeters[k].id = countLetter;
			countLetter++;
			existLetters.push_back(&allLeters[k]);
			*/
		
	}
	//cout << &existLetters << endl;
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
	allLeters[1] = Letter('A', 1);
	allLeters[2] = Letter('A', 1);
	allLeters[3] = Letter('A', 1);
	allLeters[4] = Letter('A', 1);
	allLeters[5] = Letter('A', 1);
	allLeters[6] = Letter('A', 1);
	allLeters[7] = Letter('A', 1);
	allLeters[8] = Letter('A', 1);

	allLeters[9] = Letter('•', 5);

	allLeters[10] = Letter('B', 3);
	allLeters[11] = Letter('B', 3);

	allLeters[12] = Letter('C', 2);
	allLeters[13] = Letter('C', 2);
	allLeters[14] = Letter('C', 2);

	allLeters[15] = Letter('∆', 6);

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

	allLeters[26] = Letter(' ', 5);

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

	allLeters[58] = Letter('—', 7);

	allLeters[59] = Letter('O', 1);
	allLeters[60] = Letter('O', 1);
	allLeters[61] = Letter('O', 1);
	allLeters[62] = Letter('O', 1);
	allLeters[63] = Letter('O', 1);
	allLeters[64] = Letter('O', 1);

	allLeters[65] = Letter('”', 5);

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

	allLeters[77] = Letter('å', 5);

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

	allLeters[96] = Letter('è', 9);
	allLeters[97] = Letter('Ø', 5);
	for (int i = 0; i < 98; i++)
	{
		allLeters[i].id = i;
	}
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
					//existLetters[i]->placed = true;
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
void Play::RestartLetters()
{
	int a = newWord->letters.size();
	int x = 0;
	int y = 0;
	for (int i = 0; i < a; i++)
	{
		GetBoardField(newWord->letters[i])->occupied = false;
	}
	for (int i = 0; i < existLetters.size(); i++)
	{
		if (existLetters[i]->getPositionX() >= 1070 && existLetters[i]->getPositionY() >= 300)
		{
			if (x < 4)
			{
				existLetters[i]->setPosition((1070 + x * 40), (300));
			}
			else
			{
				existLetters[i]->setPosition((1070 + y * 40), (300 + 40));
				y++;
			}
			x++;
		}
	}
	for (int i = 0; i < a; i++)
	{
		if (x < 4)
		{
			newWord->letters[i]->setPosition((1070 + x * 40), (300));
		}
		else
		{
			newWord->letters[i]->setPosition((1070 + y * 40), (340));
			y++;
		}

	}
}
void Play::addLetterToStand()
{
	for (int i = 0; i < newWord->letters.size(); i++)
	{
		client->Send((Packet::stringToPacket("LetterRequest\n")).PacketToString());
		//Sleep(50);
	}
}
void Play::HandleReceivePacket()
{
	Text temp;
	if (client->taskQueue.buffers.size() > 0)
	{
		string tekst = client->taskQueue.buffers.front();
		client->taskQueue.buffers.erase(client->taskQueue.buffers.begin());
		cout << tekst << endl;
		std::istringstream iss(tekst);
		string slowo;
		iss >> slowo;
		tekst = tekst.substr(slowo.length() + 1, tekst.length());
		Packet packet = Packet::stringToPacket(tekst);
		//client->messageReceived = false;
		if (packet.getPacketType() == "Letter")
		{
			Letter newL = Packet::StringToLetter(packet.getData());
			allLeters[newL.id].setPosition(newL.getPositionX(), newL.getPositionY());
			allLeters[newL.id].placed = true;
			existLetters.push_back(&allLeters[newL.id]);
			if (GetBoardField(&allLeters[newL.id]) != nullptr)
				GetBoardField(&allLeters[newL.id])->occupied = true;
			letterOccupied[newL.id] = true;
			//cout << newL.getPositionX() << " " << newL.id << endl;
		}
		else if (packet.getPacketType() == "LetterRequest")
		{
			int a = atoi(packet.getData().c_str());
			int x = 0;
			int y = 0;
			for (int i = 0; i < existLetters.size(); i++)
			{
				if (existLetters[i]->getPositionX() >= 1070 && existLetters[i]->getPositionY() >= 300)
				{
					if (x < 4)
					{
						existLetters[i]->setPosition((1070 + x * 40), (300));
					}
					else
					{
						existLetters[i]->setPosition((1070 + y * 40), (300 + 40));
						y++;
					}
					x++;
				}
			}



			allLeters[a].setPosition((1070), (300));
			allLeters[a].placed = false;


			countLetter++;
			existLetters.push_back(&allLeters[a]);

			RestartLetters();
		}
		else if (packet.getPacketType() == "Conversation")
		{
			GlobalFunctions::setText(temp, slowo + " " + packet.getData(), 1000, 450 + (15 * countTexts), 15);
			conversation.push_back(temp);
			countTexts++;

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
}
void Play::Start(string playerName)
{
	playWindow = new RenderWindow(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
	GlobalFunctions::setText(Tplayers[0], playerName, 1060, 150, 25);
	bool play = true;
	
	Event event;
	//allLeters[0].setPosition(240, 30);
	
	this->canWrite = false;
	newWord = new Word();
	
	GlobalFunctions::setText(textPoints, "0", 10, 0);

	RandomLetters();
	while (play)
	{
		Vector2i mousePos = Mouse::getPosition(*playWindow);
		HandleReceivePacket();
		
		while (playWindow->pollEvent(event)) 
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				playWindow->close();
				play = false;
			}

			LettersUpdate();
			WriteControl(event);
			
			if (roundOver)
				cout << "\n\n KONIEC" << endl;
			if (acceptWord->ifMousePressed(playWindow))
			{
				for (int i = 0; i < existLetters.size(); i++)
				{
					cout << existLetters[i]->id << " ";
				}
				cout << endl;
				AcceptWord();
				for (int i = 0; i < newWord->letters.size();i++)
				{
					Packet packet(Packet::LetterToString(newWord->letters[i]), "Letter");
					client->Send(packet.PacketToString());
					Sleep(20);
				}
				newWord->deleteAllLetter();
				
			}
		}
		
		Display();
		Sleep(10);
	}
}
void Play::AcceptWord()
{
	if (newWord->letters.size() > 0)
	{
		try
		{
			if (wordController->QuickCheck(board, &existLetters, newWord))
			{
				cout << "QuickTest: TRUE" << endl;
				if (tour == 1)
				{
					if (newWord->letters.size() <= 1)
					{
						cout << "\nZA KROTKIE" << endl;
					}
					else
					{
						cout << "Punkty: " << wordController->CountPoints(board, &existLetters, newWord) << endl;
						this->points += wordController->CountPoints(board, &existLetters, newWord);
					}

				}
				if (tour > 1)
				{
					this->points += wordController->SolidTest(board, &existLetters, newWord);

					//cout << "Punkty: " << wordController->CountPoints(board, newWord);
				}
				for (int i = 0; i < newWord->letters.size(); i++)
				{
					newWord->letters[i]->placed = true;
				}
				addLetterToStand();
				tour++;
				GlobalFunctions::setText(textPoints, to_string(this->points), 10, 0);

			}
			else
				cout << "FALSE" << endl;
		}
		catch (string &w)
		{
			//Obsluga bledu
			cout << endl << w << endl;
			RestartLetters();
		}
		

	}
	if (existLetters.size() >= 98)
	{
		if (CheckIfOver())
			roundOver = true;
	}
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
bool Play::CheckIfOver()
{
	for (int i = 0; i < existLetters.size(); i++)
	{
		if (existLetters[i]->getPositionX() >= 1070 && existLetters[i]->getPositionY() >= 300)
		{
			return false;
		}
	}
	return true;
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
		Packet packet(str+"\n", "Conversation");
		std::thread sendThread(&Client::Send, &*client, packet.PacketToString());
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

	playWindow->draw(textPoints);
	/*for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			playWindow->draw(board[i][j]);
	}*/
	
	playWindow->display();
}
