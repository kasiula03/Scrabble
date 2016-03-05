#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>
class Client
{
public:
	Client();
	bool ConnectToServer(); // try to connect with server
	void Send(std::string); // send date to server
	bool CheckIfConnected(); // check if our client is connected with server
	//void Received();

private:
	SOCKET mainSocket;
	sockaddr_in service;
	bool connected;
};