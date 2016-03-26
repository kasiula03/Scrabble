#pragma once

#include <SFML\Graphics.hpp>

class Register
{
protected:
	Register();

	static sf::Font font;

	sf::RenderWindow * registerWindow;

	sf::Sprite Layout;
	sf::Texture texture;

	void runRegisterWindow();

};