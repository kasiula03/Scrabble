#pragma once

#include <SFML\Graphics.hpp>
#include "Button.h"
#include "Client.h"
class Register
{
protected:
	Register();

	static sf::Font font;

	sf::RenderWindow * registerWindow;
	Client * client;

	sf::Sprite Layout;
	sf::Texture texture;
	sf::Text txt[4];
	Button * button;
	bool canWrite;
	bool writeLogin;
	bool writePassword;
	std::string login;
	std::string password;

	sf::Text loginTxt;
	sf::Text passwordTxt;

	void runRegisterWindow();
	void WriteControl(sf::Event event);
	void Display();

};