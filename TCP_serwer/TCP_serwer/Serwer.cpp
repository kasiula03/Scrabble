#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include "Serwer.h"

#include <iostream>
#include <mutex>
#include <thread>
#include <fstream>

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

	CreateSerwer();
	countLetter = 0;
	round = 1;

	packetHandler = new PacketHandler(this);

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

void Serwer::Register(std::string login, std::string password)
{
	std::fstream plik;
	plik.open("Registered_Users.txt", std::ios::out | std::ios::app);
	if (plik.good())
	{
		plik << login << " " << password << std::endl;
	}
	plik.close();
	//std::cout << login << " " << password << std::endl;
}
bool Serwer::Login(std::string login, std::string password)
{
	std::fstream plik;
	plik.open("Registered_Users.txt", std::ios::in);

	std::string tempLogin;
	std::string tempPassword;
	if (plik.good())
	{
		while (!plik.eof())
		{
			plik >> tempLogin;
			if (tempLogin == login)
			{
				plik >> tempPassword;
				if (tempPassword == password)
				{
					plik.close();
					return true;
				}
			}
		}
	}
	plik.close();
	return false;
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
			clientsThread[countClients] = new std::thread(&Serwer::ManagerSingleClient, &*this, countClients);
			
			playersName[countClients] = "Guest" + std::to_string(rand() % 80)+ ": ";
			countClients += 1;

			for (int i = 0; i < countClients; i++)
			{
				std::cout << clientConnect[i] << " " << clientsThread[i]->get_id() << " " << playersName[i] << std::endl;
			}
			
		}
	}
}

void Serwer::SendMessageToClient(int index, Packet packet)
{
	char * playerName = (char*)playersName[index].c_str();

	int playerNameSize = playersName[index].length();

	send(acceptSocket[index], (char*)&playerNameSize, sizeof(int), NULL);
	send(acceptSocket[index], playerName, playerNameSize, NULL);

	int bufferLength = (packet.PacketToString().size());
	send(acceptSocket[index], (char *)&bufferLength, sizeof(int), NULL); // wysylanie info o wielkosci
																		 
	send(acceptSocket[index], packet.PacketToString().c_str(), bufferLength, NULL);
}
void Serwer::SendMessageToClient(int index, int who, Packet packet)
{
	char * playerName = (char*)playersName[index].c_str();

	int playerNameSize = playersName[index].length();

	send(acceptSocket[who], (char*)&playerNameSize, sizeof(int), NULL);

	send(acceptSocket[who], playerName, playerNameSize, NULL);

	int bufferLength = (packet.PacketToString().size());
	send(acceptSocket[who], (char*)&bufferLength, sizeof(int), NULL);

	send(acceptSocket[who], packet.PacketToString().c_str(), bufferLength, NULL);
}

void Serwer::Send()
{
	int prev_index = 0;
	while (true)
	{
		if (packetHandler->sendQueue.buffers.size() > 0 && packetHandler->sendQueue.whos.size() > 0)
		{
			packet = packetHandler->HandleReceiveMessage();
			if (packet.getPacketType() != "error")
			{
				int index = packetHandler->sendQueue.whos.front(); //which player send message
				packetHandler->sendQueue.whos.erase(packetHandler->sendQueue.whos.begin());

				if (packet.getPacketType() == "LetterRequest" || packet.getPacketType() == "WordCheck")
				{
					SendMessageToClient(index, packet);
				}
				if (packet.getPacketType() == "Login")
				{
					SendMessageToClient(index, packet);
				}
				if (packet.getPacketType() == "PlayerJoin")
				{
					Packet playerNamePacket(playersName[index], "YourName");
					SendMessageToClient(index, playerNamePacket);
					for (int k = 0; k < 98; k++)
					{
						if (ifLetterOnBoard[k])
						{
							SendMessageToClient(index, *(new Packet((Packet::LetterToString(&letterOnBoard[k])),"Letter")));
						}
					}
					for (int i = 0; i < 4; i++)
					{
						if (i != index && clientConnect[i])
						{
							SendMessageToClient(index, *(new Packet(playersName[i], "PlayerJoin")));
						}
					}
					
					Packet roundPacket(std::to_string(round), "GameRound");
					SendMessageToClient(index, roundPacket);

					int which = (round-1) % countClients;
					Packet whosTurnPacket(playersName[which], "PlayerRound");
					SendMessageToClient(index, whosTurnPacket);
					
					
				}
				for (int i = 0; i < countClients; i++)
				{
					if (packet.getPacketType() == "WordCheck")
					{
						Packet roundPacket(std::to_string(round), "GameRound");
						SendMessageToClient(i, roundPacket);
						int which = (round - 1) % countClients;
						Packet whosTurnPacket(playersName[which], "PlayerRound");
						SendMessageToClient(i, whosTurnPacket);
					}
					if (packet.getPacketType() == "PlayerLeave")
					{
						std::cout << "Player: " << playersName[index] << " left the game" << std::endl;
						std::cout << "Id: " << clientsThread[index]->get_id() << std::endl;

						closesocket(acceptSocket[index]);
						playersName[index] = "none";
						clientConnect[index] = false;
						countClients--;

						for (int i = index; i < countClients; i++)
						{
							playersName[i] = playersName[i + 1];
							clientConnect[i] = clientConnect[i + 1];
							acceptSocket[i] = acceptSocket[i + 1];
						}

					}


					if (i == index)
						continue;
					else if (clientConnect[i])
					{
						if (packet.getPacketType() == "Letter")
							SendMessageToClient(i, packet);

						if (packet.getPacketType() == "Conversation")
							SendMessageToClient(index, i, packet);

						if (packet.getPacketType() == "PlayerLeave")
						{
							packet.setData(playersName[index]);
							SendMessageToClient(index, i, packet);
						}
						if (packet.getPacketType() == "PlayerJoin")
							SendMessageToClient(i, *(new Packet(playersName[index], "PlayerJoin")));
						
					}
					
				}
				Sleep(10);
			}
		}
	}

}

void Serwer::ManagerSingleClient(int index)
{
	int bufferLength;
	
	while (clientConnect[index])
	{
		recv(acceptSocket[index], (char*)&bufferLength, sizeof(int), NULL);
		
		if (bufferLength < 3000)
		{
			
			packetHandler->sendQueue.buffersLength.push_back(bufferLength);
		
			char * buffer = new char[bufferLength];

			recv(acceptSocket[index], buffer, bufferLength, NULL);

			packetHandler->sendQueue.buffers.push_back(buffer);

			packetHandler->sendQueue.whos.push_back(index);

			delete[] buffer;

			Sleep(10);
		}
	}
	std::cout << "thread end" << std::endl;
}
