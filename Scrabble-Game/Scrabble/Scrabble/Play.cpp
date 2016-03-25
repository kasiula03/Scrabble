#include "Play.h"
#include <iostream>

Font Play::font;

Play::Play()
{
	if (!font.loadFromFile("data/WorkSans-Black.otf"))
	{
		cout << "Fond not found" << endl;
		return;
	}
	if (!texture.loadFromFile("data//Graphs//GameLayout.png"))
	{
		std::cout << "Nie wczytano tekstury!" << std::endl;
	}
	Layout.setTexture(texture);

	GlobalFunctions::setText(Tplayers[0], "Brak", 1110, 150);
	GlobalFunctions::setText(Tplayers[1], "Brak", 1240, 150);
	GlobalFunctions::setText(Tplayers[2], "Brak", 1110, 215);
	GlobalFunctions::setText(Tplayers[3], "Brak", 1240, 215);
}

void Play::Start()
{
	playWindow = new RenderWindow(VideoMode(1366, 768), "Scrabble multiplayer", Style::Fullscreen);
	bool play = true;
	Event event;

	while (play)
	{
		while (playWindow->pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				playWindow->close();
				play = false;
			}
		}

		playWindow->clear(Color(50, 50, 50, 255));
		playWindow->draw(Layout);
		playWindow->draw(Tplayers[0]);
		playWindow->draw(Tplayers[1]);
		playWindow->draw(Tplayers[2]);
		playWindow->draw(Tplayers[3]);
		playWindow->display();
	}
}
