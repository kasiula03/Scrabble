#include "PacketHandler.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "Serwer.h"


PacketHandler::PacketHandler(Serwer * server)
{
	this->server = server;
	dictionary = new Dictionary();
	
}
Packet PacketHandler::HandleReceiveMessage()
{
	srand(time(NULL));

	std::string buffer = sendQueue.buffers.front();
	sendQueue.buffers.erase(sendQueue.buffers.begin());

	Packet packet("n", "n");
	std::istringstream iss(buffer);
		
	std::string slowo;
	iss >> slowo;
	packet = Packet::stringToPacket(buffer);

	if (packet.getPacketType() == "Letter")
	{
		iss >> slowo;
		iss >> slowo;
		iss >> slowo;
		
		server->letterOccupied[atoi(slowo.c_str())] = true;
		server->ifLetterOnBoard[atoi(slowo.c_str())] = true;
		server->letterOnBoard[atoi(slowo.c_str())] = packet.StringToLetter(packet.getData());
	}
	if (packet.getPacketType() == "LetterRelease")
	{
		Letter ltr = Packet::StringToLetter(packet.getData());
		server->letterOccupied[ltr.id] = false;
		server->countLetter--;
	}
	if (packet.getPacketType() == "Register")
	{
		int i = 0;
		for (; i < packet.getData().length(); i++)
		{
			if (packet.getData()[i] == '\n')
				break;
		}
		packet.setData(packet.getData().substr(0, i));

		std::string login, password;
		iss >> login;
		iss >> password;
		server->Register(login, password);
	}
	if (packet.getPacketType() == "Login")
	{
		int i = 0;
		for (; i < packet.getData().length(); i++)
		{
			if (packet.getData()[i] == '\n')
				break;
		}
		packet.setData(packet.getData().substr(0, i));

		std::string login, password;
		iss >> login;
		iss >> password;
		if (server->Login(login, password))
			packet.setData("Login");
		else
			packet.setData("Wrong");
		
	}
	if (packet.getPacketType() == "PlayerName")
	{
		int i = 0;
		for (; i < packet.getData().length(); i++)
		{
			if (packet.getData()[i] == '\n')
				break;
		}
		packet.setData(packet.getData().substr(0, i));
		server->playersName[sendQueue.whos.front()] = (packet.getData() + ": ");
	}
		if (packet.getPacketType() == "LetterRequest")
		{
			
			if (server->countLetter < 98)
			{
				int k = rand() % 98;
				while (server->letterOccupied[k])
				{
					k = rand() % 98;
				}
				server->countLetter++;
				server->letterOccupied[k] = true;

				packet.setData(std::to_string(k));
			}
			else
			{
				packet.setData("nic");
			}
			
		}
		if (packet.getPacketType() == "Conversation")
		{
			int i = 0;
			for (; i < packet.getData().length(); i++)
			{
				if (packet.getData()[i] == '\n')
					break;
			}
			packet.setData(packet.getData().substr(0, i));

		}
		if (packet.getPacketType() == "WordCheck")
		{
			std::cout << "\n ZAJETYCH LITER: " << server->countLetter << std::endl;
			int x = 0;
			for (int i = 0; i < packet.getData().length(); i++)
			{
				if (packet.getData()[i] == '\n')
				{
					x = i;
				}
			}
			if (x < packet.getData().length())
			{
				if (dictionary->CheckWord(packet.getData()))
					packet.setData("Correct");
				else
					packet.setData("InCorrect");


				server->round++;

			}
		}
		
		return packet;
	
}