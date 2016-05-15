#pragma once

#include <SFML\Graphics.hpp>
#include <cstring>
#include "GlobalFunctions.h"
#include "Field.h"
#include "Client.h"
#include "Button.h"
#include "Word.h"
#include "WordController.h"

#include <vector>
using namespace sf;
using namespace std;

class Play
{
protected:
	Play();

	static Font font;

	RenderWindow * playWindow;

	Sprite Layout;
	Texture texture;
	Text Tplayers[4];
	bool playerConnected[4];

	Text tempTxt;
	Text textPoints;
	Text WhosRoundTxt;

	vector<Text> conversation;
	int countTexts;
	Client * client;

	Field board[15][15];
	Letter allLeters[98]; //all avaliable letters
	bool letterOccupied[98];
	int countLetter;
	
	vector<Letter *> existLetters;
	Word * newWord;
	WordController * wordController;

	int round;
	int points;

	Button * acceptWord;
	string str;

	bool youTurn;
	bool canWrite;
	bool roundOver;
	bool correctWords;
	bool waitingForAnswer;
	bool answer;

	void Initialize(string playerName);
	void Start(string playerName);
	
	bool CheckIfOver();

	void HandleReceivePacket();

	void AcceptWord();
	void WriteControl(Event &);
	void HandleAnswer();

	Field * GetBoardField(Letter * letter);

	void HandlePacketPlayRound(Packet & packet);
	void HandlePacketPlayerJoin(Packet & packet);
	void HandlePacketLetter(Packet & packet);
	void HandlePacketWordCheck(Packet & packet);
	void HandlePacketLetterRequest(Packet & packet);
	void HandlePacketConversation(Packet & packet, std::string playerName);
	void HandlePacketPlayerLeave(Packet & packet);

	void LettersUpdate();
	bool CheckLetter(Letter letter, int & x, int & y);
	bool CheckIfLetterIs(int x, int y);
	void ReleasePreviousField(int prev_x, int prev_y);
	void SetLetterPosition(Letter * letter, int prev_x, int prev_y);
	void SetLetterOnTable(Letter * letter, int prev_x, int prev_y);
	void RestartLetters();
	void addLetterToStand();
	void RandomLetters();
	void SetLetters();

	void PrepareBoard();
	

	void Display();

};