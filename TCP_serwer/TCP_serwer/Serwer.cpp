#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include "Serwer.h"

#include <iostream>
#include <mutex>
#include <thread>
#include <sstream>

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
	std::cout << "TRWA LADOWANIE SLOWNIKA" << std::endl;
	dictionary = new Dictionary();

	CreateSerwer();
	countLetter = 0;
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

			clientsThread[countClients] = new std::thread(&Serwer::Manager,&*this, countClients - 1);
		}
	}
}


void Serwer::Send()
{
	while (true)
	{
		if (sendQueue.buffers.size() > 0 && sendQueue.whos.size() > 0)
		{
			packet = HandleMessage(sendQueue.buffers.front());
			sendQueue.buffers.erase(sendQueue.buffers.begin());
			int index = sendQueue.whos.front();
			sendQueue.whos.erase(sendQueue.whos.begin());


			if (packet.getPacketType() == "LetterRequest" || packet.getPacketType() == "WordCheck")
			{
				char * playerName = (char*)playersName[index].c_str();

				int playerNameSize = playersName[index].length();

				send(acceptSocket[index], (char*)&playerNameSize, sizeof(int), NULL);
				send(acceptSocket[index], playerName, playerNameSize, NULL);

				int bufferLength = (packet.PacketToString().size());
				send(acceptSocket[index], (char *)&bufferLength, sizeof(int), NULL); // wysylanie info o wielkosci
				std::cout << packet.PacketToString().c_str() << std::endl;
				send(acceptSocket[index], packet.PacketToString().c_str(), bufferLength, NULL);
				Sleep(50);
			}
			
			for (int i = 0; i < countClients; i++)
			{
				if (i == index)
				{
					continue;
				}
				else if (clientConnect[i])
				{
					if (packet.getPacketType() == "Letter")
					{
						char * playerName = (char*)playersName[index].c_str();

						int playerNameSize = playersName[index].length();

						send(acceptSocket[i], (char*)&playerNameSize, sizeof(int), NULL);
						send(acceptSocket[i], playerName, playerNameSize, NULL);

						int bufferLength = (packet.PacketToString().size());
						send(acceptSocket[i], (char *)&bufferLength, sizeof(int), NULL); // wysylanie info o wielkosci
						//std::cout << packet.PacketToString().c_str() << std::endl;
						send(acceptSocket[i], packet.PacketToString().c_str(), bufferLength, NULL);
						Sleep(50);
					}
					if ((packet.getPacketType() == "Conversation"))
					{
						char * playerName = (char*)playersName[index].c_str();

						int playerNameSize = playersName[index].length();

						send(acceptSocket[i], (char*)&playerNameSize, sizeof(int), NULL);

						send(acceptSocket[i], playerName, playerNameSize, NULL);

						int bufferLength = (packet.PacketToString().size());
						send(acceptSocket[i], (char*)&bufferLength, sizeof(int), NULL);

						send(acceptSocket[i], packet.PacketToString().c_str(), bufferLength, NULL);
					}
					//delete[] playerName;
				}
			}
		}
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
Packet Serwer::HandleMessage(std::string buffer)
{
	srand(time(NULL));
	Packet packet("n","n");
	std::istringstream iss(buffer);
	//Letter temp;
	std::string slowo;
	iss >> slowo;
	packet = Packet::stringToPacket(buffer);
	
	if ((packet.getPacketType() == "Letter") || (packet.getPacketType() == "FirstLetter") || (packet.getPacketType() == "NewLetter"))
	{
		iss >> slowo;
		iss >> slowo;
		iss >> slowo;
		letterOccupied[atoi(slowo.c_str())] = true;
	}
	if (packet.getPacketType() == "LetterRequest")
	{
		int k = rand() % 98;
		while (letterOccupied[k])
		{
			if (countLetter >= 98)
			{
				packet.setData("nic");
			}
			k = rand() % 98;

		}
		letterOccupied[k] = true;
		countLetter++;
		packet.setData(std::to_string(k));
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
		if(dictionary->CheckWord(packet.getData()))
			packet.setData("Correct");
		else
			packet.setData("InCorrect");
	}
	return packet;
}
void Serwer::Manager(int index)
{
	int bufferLength;
	//Packet packet("n", "n");
	
	while (true)
	{
		recv(acceptSocket[index], (char*)&bufferLength, sizeof(int), NULL);
		
		sendQueue.buffersLength.push_back(bufferLength);
		char * buffer = new char[bufferLength];

		recv(acceptSocket[index], buffer, bufferLength, NULL);

		sendQueue.buffers.push_back(buffer);

		sendQueue.whos.push_back(index);
		
		delete[] buffer;

	}
}
