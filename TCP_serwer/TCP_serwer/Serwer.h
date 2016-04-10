#pragma once



#include <WinSock2.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <iostream>
#include <thread>


class Serwer
{
	SOCKET mainSocket;
	sockaddr_in service;
	static SOCKET acceptSocket[4];
	static std::string playersName[4];

	bool sendMessage;

	static int countClients;
	
	bool * clientConnect; 
	std::thread * clientsThread[4];
public:
	
	Serwer();

	void CreateSerwer(); 
	void AcceptClient();
	void ManageConversation(int index);
	void Receive();
	void Send(std::string,int); //send data as string

};