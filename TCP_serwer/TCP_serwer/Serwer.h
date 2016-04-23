#pragma once



#include <WinSock2.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "Packet.h"
#include "TasksQueue.h"

class Serwer
{
	SOCKET mainSocket;
	sockaddr_in service;
	static SOCKET acceptSocket[4];
	static std::string playersName[4];

	bool sendMessage;

	static int countClients;

	int letterOccupied[98];
	int countLetter;
	
	bool * clientConnect; 
	std::thread * clientsThread[4];

	TasksQueue sendQueue;
	Packet packet;
public:
	
	Serwer();

	void CreateSerwer(); 
	void AcceptClient();
	void Manager(int index);
	void Receive();
	void Send(); 

	Packet HandleMessage(std::string);
};