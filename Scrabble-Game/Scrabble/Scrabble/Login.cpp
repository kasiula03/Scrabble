#include "Login.h"
#include "GlobalFunctions.h"
#include <Windows.h>
#include <fstream>
#include <sstream>
using namespace sf;

Login::Login()
{
	GlobalFunctions::setText(txts[0], "Zaloguj sie", 100, 100);
	GlobalFunctions::setText(txts[1], "Login: ", 70, 150);
	GlobalFunctions::setText(txts[2], "Haslo: ", 70, 200);

	button = new Button("Zaloguj", 70, 250);
	//runLoginWindow();
}

std::string Login::runLoginWindow()
{
	loginWindow = new sf::RenderWindow(VideoMode(1366, 768), "Katarzyna Nalepka Scrabble", Style::Default);
	bool opened = true;
	canWrite = true;
	writeLogin = true;
	writePassword = false;
	login = "";
	password = "";
	bool loginB = false;
	bool answer = false;
	sf::Event event;

	while (opened)
	{
		while (loginWindow->pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				loginWindow->close();
				opened = false;
				return "Guest";
			}
			if (button->ifMousePressed(loginWindow))
			{
				tryToLogin(login, password);
				
			}
			
			if (client->taskQueue.buffers.size() > 0 && client->taskQueue.buffers.front().length() > 0)
			{
				string tekst = client->taskQueue.buffers.front();
				client->taskQueue.buffers.erase(client->taskQueue.buffers.begin());

				std::istringstream iss(tekst);
				string slowo;
				iss >> slowo;
				tekst = tekst.substr(slowo.length() + 1, tekst.length());
				Packet packet = Packet::stringToPacket(tekst);

				if (packet.getPacketType() == "Login")
				{
					if (packet.getData() == "Login")
					{
						loginWindow->close();
						opened = false;
						return login;
					}
					else
					{
						MessageBox(NULL, "Nie udalo sie zalogowac", "ERROR", NULL);
					}
					
				}
				answer = true;

			}
			WriteControl(event);
		}

		Display();
		Sleep(10);
	}
	return "None";
}
void Login::WriteControl(Event event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
	{
		if (writeLogin)
		{
			writeLogin = false;
			writePassword = true;
		}
		else if (writePassword)
		{
			writeLogin = true;
			writePassword = false;
		}
	}
	if (event.type == sf::Event::TextEntered)
	{
		// Handle ASCII characters only
		if (this->canWrite)
		{
			if (event.text.unicode < 128 && event.text.unicode != 13)
			{
				if (writeLogin)
				{
					login += static_cast<char>(event.text.unicode);
					GlobalFunctions::setText(loginTxt, login, 200, 150);
				}
				else
				{
					password += static_cast<char>(event.text.unicode);
					GlobalFunctions::setText(passwordTxt, password, 200, 200);
				}

			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::BackSpace) && login.length() > 0)
	{
		if (writeLogin)
		{
			login.erase(login.length() - 1, login.length());
			GlobalFunctions::setText(loginTxt, login, 200, 150);
		}
		else
		{
			password.erase(password.length() - 1, login.length());
			GlobalFunctions::setText(passwordTxt, password, 200, 200);
		}
	}
}
void Login::Display()
{
	loginWindow->clear(Color(50, 50, 50, 255));
	loginWindow->draw(txts[0]);
	loginWindow->draw(txts[1]);
	loginWindow->draw(txts[2]);
	loginWindow->draw(loginTxt);
	loginWindow->draw(passwordTxt);
	loginWindow->draw(*button);
	//window.draw(rec);
	loginWindow->display();
}
void Login::tryToLogin(std::string usr, std::string password)
{
	Packet packet(login + " " + password + "\n", "Login");
	client->Send(packet.PacketToString());
}