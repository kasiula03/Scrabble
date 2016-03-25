#pragma once
#include <SFML\Graphics.hpp>
#include <string>
class GlobalFunctions
{
public:
	GlobalFunctions();

	static sf::Font font;
	static void setText(sf::Text & txt, std::string text, int pos_x, int pos_y, int char_size = 30);
};