#include "GlobalFunctions.h"
#include <Windows.h>

sf::Font GlobalFunctions::font;

void GlobalFunctions::setText(sf::Text & txt, std::string text, int pos_x, int pos_y, int char_size)
{
	txt.setFont(font);
	txt.setColor(sf::Color(0, 0, 0, 255));
	txt.setString(text);
	txt.setCharacterSize(char_size);
	txt.setPosition(pos_x, pos_y);
}
GlobalFunctions::GlobalFunctions()
{
	if (!font.loadFromFile("data/WorkSans-Black.otf"))
	{
		MessageBox(NULL, "Fond not found", "ERROR", NULL);
		return;
	}
	
}