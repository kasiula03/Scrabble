#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Login
{
	static std::string playerName;
	sf::Text txts[5];
public:
	Login();
	std::string runLoginWindow();
	bool tryToLogin(std::string usr, std::string password);
};