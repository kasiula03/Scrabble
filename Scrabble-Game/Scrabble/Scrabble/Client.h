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
	void Send(std::string); // send data to server
	void Listen(); // thread function
	void Receive();
	bool CheckIfConnected(); // check if our client is connected with server

	string getReceivedMessage();

	static bool connected;

	static string receivedMessage;
	static bool messageReceived;

private:
	SOCKET mainSocket;
	sockaddr_in service;
	
};