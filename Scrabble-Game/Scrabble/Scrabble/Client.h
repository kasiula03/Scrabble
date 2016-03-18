#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <iostream>

using namespace std;

class Client
{
public:
	Client();
	
	bool ConnectToServer(); // try to connect with server
	void Send(std::string); // send date to server
	void Receive();
	bool CheckIfConnected(); // check if our client is connected with server

	void operator()();
	
	bool connected;

private:
	SOCKET mainSocket;
	sockaddr_in service;
	
};