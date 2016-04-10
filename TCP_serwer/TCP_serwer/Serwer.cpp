#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include "Serwer.h"

#include <iostream>
#include <mutex>
#include <thread>

int Serwer::countClients;
SOCKET Serwer::acceptSocket[4];
std::string Serwer::playersName[4];
Serwer::Serwer()
{
	clientConnect = new bool[4];
	countClients = 0;
	for (int i = 0; i < 4; i++)
	{
		clientConnect[i] = false;
		playersName[i] = "Player" + std::to_string(i) + ": ";
	}
	CreateSerwer();

	//Receive();

}

void Serwer::CreateSerwer()
{
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		std::cout << "Initialization error!" << std::endl;
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET)
	{
		std::cout << "Error creating socket! \t" << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);

	if (bind(mainSocket, (SOCKADDR *)& service, sizeof(service)) == SOCKET_ERROR)
	{
		std::cout << "Bind failed! " << std::endl;
		closesocket(mainSocket);
		return;
	}
	if (listen(mainSocket, 1) == SOCKET_ERROR)
		std::cout << "Error listening on socket! " << std::endl;


	//AcceptClient();

}

void Serwer::AcceptClient()
{
	while (true)
	{
		if (countClients < 4)
		{
			acceptSocket[countClients] = SOCKET_ERROR;
			std::cout << "Waiting for a client to connect... " << std::endl;
			while (acceptSocket[countClients] == SOCKET_ERROR)
			{
				acceptSocket[countClients] = accept(mainSocket, NULL, NULL);
			}

			std::cout << "Client connected " << std::endl;


			clientConnect[countClients] = true;

			countClients += 1;

			clientsThread[countClients] = new std::thread(&Serwer::ManageConversation,&*this, countClients - 1);
		}
	}
}


void Serwer::Send(std::string pakiet, int which)
{
	int iResult = 2, iSendResult;

	int size = pakiet.length();

	char * sendbuf = new char[size]; // to wysylamy
	strcpy(sendbuf, pakiet.c_str());

	iSendResult = send(acceptSocket[which], sendbuf, 50, 0);

	Sleep(200); //Zeby kolejne wysylania nie odbywaly sie za szybko, bo wtedy sa bledy

	if (iSendResult == SOCKET_ERROR)
	{
		std::cout << "Connection closing" << std::endl;
		clientConnect[which] = false;
		closesocket(acceptSocket[which]);
		return;
	}


}

void Serwer::Receive()
{
	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char sendbuf[32] = "Server says hello!";
	char recvbuf[32] = "";

	bytesRecv = recv(acceptSocket[0], recvbuf, 32, 0);
	std::cout << "Bytes received: " << bytesRecv << std::endl;
	std::cout << "Received text: " << recvbuf << std::endl;

	bytesSent = send(acceptSocket[0], sendbuf, strlen(sendbuf), 0);
	std::cout << "Bytes send: " << bytesSent << std::endl;
}
void Serwer::ManageConversation(int index)
{
	int bufferLength;
	while (true)
	{

		recv(acceptSocket[index], (char*)&bufferLength, sizeof(int), NULL);

		char * buffer = new char[bufferLength];

		recv(acceptSocket[index], buffer, bufferLength, NULL);

		for (int i = 0; i < countClients; i++)
		{
			if (i == index)
				continue;

			if (clientConnect[i])
			{
				char * playerName = (char*)playersName[index].c_str();

				int playerNameSize = playersName[index].length();

				send(acceptSocket[i], (char*)&playerNameSize, sizeof(int), NULL);

				send(acceptSocket[i], playerName, playerNameSize, NULL);

				send(acceptSocket[i], (char*)&bufferLength, sizeof(int), NULL);

				send(acceptSocket[i], buffer, bufferLength, NULL);

				//delete[] playerName;
			}
		}

		delete[] buffer;

	}
}
