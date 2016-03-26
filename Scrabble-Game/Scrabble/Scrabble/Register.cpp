#include "Register.h"
#include <iostream>

sf::Font Register::font;

Register::Register()
{
	if (!font.loadFromFile("data/WorkSans-Black.otf"))
	{
		std::cout << "Fond not found" << std::endl;
		return;
	}

}

void Register::runRegisterWindow()
{
	registerWindow = new sf::RenderWindow(sf::VideoMode(1366, 768), "Scrabble multiplayer", sf::Style::Fullscreen);
	bool opened = true;
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
		}

		registerWindow->clear(sf::Color(50, 50, 50, 255));
		
		registerWindow->display();
	}
}