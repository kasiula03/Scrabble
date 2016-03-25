#pragma once



#include <WinSock2.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <iostream>



class Serwer
{
	SOCKET mainSocket;
	sockaddr_in service;
	SOCKET acceptSocket[4];

	int countClients;
	
	bool * clientConnect; 

public:
	
	Serwer();

	void CreateSerwer(); 
	void AcceptClient();
	void Receive();
	void Send(std::string,int); //send data as string

	void operator()(std::string); //thread function
};