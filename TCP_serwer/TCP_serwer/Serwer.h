#pragma once



#include <WinSock2.h>
#include <cstdio>
#include <string>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "PacketHandler.h"


class Serwer
{
	SOCKET mainSocket;
	sockaddr_in service;
	static SOCKET acceptSocket[4];
	

	bool sendMessage;

	bool * clientConnect; 
	std::thread * clientsThread[4];

	
	Packet packet;
public:
	
	Serwer();

	static std::string playersName[4];
	static int countClients;
	bool letterOccupied[98];
	Letter letterExists[98];

	bool ifLetterOnBoard[98];
	Letter letterOnBoard[98];
	int countLetter;
	int round;

	void Register(std::string login, std::string password);
	bool Login(std::string login, std::string password);
	void CreateSerwer(); 
	void AcceptClient();
	void ManagerSingleClient(int index);
	void Send(); 
	void SendMessageToClient(int index, Packet packet);
	void SendMessageToClient(int index, int who, Packet packet);

	PacketHandler * packetHandler;
};