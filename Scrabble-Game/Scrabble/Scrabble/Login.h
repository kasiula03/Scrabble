#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Client.h"
class Login
{
	static std::string playerName;
	sf::Text txts[5];

	sf::RenderWindow * loginWindow;

	std::string login;
	std::string password;

	sf::Text loginTxt;
	sf::Text passwordTxt;

	bool canWrite;
	bool writeLogin;
	bool writePassword;

	Button * button;
public:
	Client * client;

	Login();
	std::string runLoginWindow();
	void WriteControl(sf::Event event);
	void Display();

	void tryToLogin(std::string usr, std::string password);
};