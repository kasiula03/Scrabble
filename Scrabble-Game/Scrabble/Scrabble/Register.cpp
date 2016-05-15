#include "Register.h"
#include "GlobalFunctions.h"
#include <iostream>
#include <Windows.h>

sf::Font Register::font;

using namespace sf;

Register::Register()
{
	if (!font.loadFromFile("data/WorkSans-Black.otf"))
	{
		std::cout << "Fond not found" << std::endl;
		return;
	}
	GlobalFunctions::setText(txt[0], "Rejestracja", 100, 100);
	GlobalFunctions::setText(txt[1], "Login: ", 70, 150);
	GlobalFunctions::setText(txt[2], "Haslo: ", 70, 200);

	button = new Button("Zarejestruj", 70, 250);

}

void Register::runRegisterWindow()
{
	registerWindow = new sf::RenderWindow(VideoMode(1366, 768), "Katarzyna Nalepka Scrabble", Style::Default);
	bool opened = true;
	canWrite = true;
	writeLogin = true;
	writePassword = false;
	login = "";
	password = "";
	
	sf::Event event;

	while (opened)
	{
		while (registerWindow->pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				registerWindow->close();
				opened = false;
			}

			if (button->ifMousePressed(registerWindow))
			{
				Packet packet(login + " " + password + "\n", "Register");
				client->Send(packet.PacketToString());
				registerWindow->close();
				opened = false;
			}

			WriteControl(event);

		}
		
		Display();

		Sleep(10);
	}
}
void Register::Display()
{
	registerWindow->clear(sf::Color(50, 50, 50, 255));

	registerWindow->draw(*button);
	for (int i = 0; i < 4; i++)
		registerWindow->draw(txt[i]);
	registerWindow->draw(loginTxt);
	registerWindow->draw(passwordTxt);
	registerWindow->display();
}
void Register::WriteControl(Event event)
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