#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include "Client.h"
#include <iostream>
//#include <WinSock2.h>


using namespace std;

Client::Client()
{
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		cout << "Initialization error!" << endl;
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET)
	{
		cout << "Error creating socket! \t" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	if (!ConnectToServer()) return;

	//Send();
}

bool Client::ConnectToServer()
{
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
	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	
	char recvbuf[32] = "";
	int size = date.length();
	 //Wysylamy napis do serwera
	//cout << "Bytes sent: " << bytesSent << endl;
	int i = 0;
	char * sendbuf = new char[size];
	strcpy(sendbuf, date.c_str());
	//cin >> sendbuf;
	bytesSent = send(mainSocket, sendbuf, size, 0);
		/*while (bytesRecv == SOCKET_ERROR)
		{
			bytesRecv = recv(mainSocket, recvbuf, 32, 0);

			if (bytesRecv == 0 || bytesRecv == WSAECONNRESET)
			{
				cout << "Connection closed" << endl;
				break;
			}
			if (bytesRecv < 0)
				return;

			cout << "Bytes received: " << bytesRecv << endl;
			cout << "Received text: " << recvbuf << endl;
		}*/
	
}