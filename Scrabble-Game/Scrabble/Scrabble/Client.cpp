#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include "Client.h"
#include <iostream>
#include <sstream>
//#include <WinSock2.h>

bool Client::connected;
bool Client::messageReceived;
string Client::receivedMessage;
using namespace std;

Client::Client()
{

	if (!ConnectToServer()) return;
	messageReceived = false;
	//Send();
}


bool Client::ConnectToServer()
{
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (mainSocket == INVALID_SOCKET)
		if (result != NO_ERROR)
			cout << "Initialization error!" << endl;
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET)
	{
		cout << "Error creating socket! \t" << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);

	if (connect(mainSocket, (SOCKADDR *)& service, sizeof(service)) == SOCKET_ERROR)
	{
		connected = false;
		cout << "Failed to connect! " << endl;
		
		WSACleanup();
		return false;
	}
	connected = true;
	cout << "Connected to server" << endl;
	return true;
}

bool Client::CheckIfConnected()
{
	return connected;
}

void Client::Send(string date)
{
	if (this->CheckIfConnected())
	{
		int bufferLength = date.size();
		send(mainSocket, (char *)&bufferLength, sizeof(int), NULL); // wysylanie info o wielkosci
		send(mainSocket, date.c_str(), date.length(), NULL);
	}
	
}
void Client::Receive()
{
	
	int bytesRecv = SOCKET_ERROR;
	char recvbuf[512];
	while (bytesRecv == SOCKET_ERROR)
	{
		bytesRecv = recv(mainSocket, recvbuf, sizeof(recvbuf),0); //przy zmianie rozmiaru na np 10 wykona sie to 5 razy

		if (bytesRecv == 0 || bytesRecv == WSAECONNRESET)
		{
			cout << "Connection closed" << endl;
			break;
		}
		if (bytesRecv < 0)
			break;

		cout << "Bytes received: " << bytesRecv << endl;
		cout << "Received text: " << recvbuf << endl;
	}
	
	
}
string Client::getReceivedMessage()
{
	return receivedMessage;
}
void Client::operator()(std::string task)
{
	
	if (task == "Wysylanie")
	{
		
	}
	else if (task == "Odbieranie")
	{
		int bufferLength;
		char * playerName;
		int playerNameSize;
		//int whichPlayer = 0;
		while (true)
		{
			if (this->CheckIfConnected())
			{
				recv(mainSocket, (char*)&playerNameSize, sizeof(int), NULL);
				playerName = new char[playerNameSize + 1];
				playerName[playerNameSize] = '\0';
				recv(mainSocket, playerName, playerNameSize, NULL);

				recv(mainSocket, (char*)&bufferLength, sizeof(int), NULL);
				char * buffer = new char[bufferLength + 1];
				buffer[bufferLength] = '\0';
				recv(mainSocket, buffer, bufferLength, NULL);

				messageReceived = true;
				receivedMessage = (string)playerName + buffer;
				
				//ostringstream ss;
				//ss << whichPlayer;
				//string liczba = ss.str();

				//receivedMessage += liczba;
				cout << buffer << endl;
				delete[] buffer;
			}
		}
	}
}