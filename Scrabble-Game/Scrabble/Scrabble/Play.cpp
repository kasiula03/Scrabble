#include "Play.h"
#include <iostream>

Font Play::font;

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

void Play::InitializePlay()
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
	Tplayers[0] = setText("Brak", 1110, 150);
	//Tplayers[0].setScale(1.5, 1);
	Tplayers[0].setColor(Color(0, 0, 0, 255));

	Tplayers[1] = setText("Brak", 1240, 150);
	//Tplayers[1].setScale(1.5, 1);
	Tplayers[1].setColor(Color(0, 0, 0, 255));

	Tplayers[2] = setText("Brak", 1110, 215);
	//Tplayers[2].setScale(1.5, 1);
	Tplayers[2].setColor(Color(0, 0, 0, 255));

	Tplayers[3] = setText("Brak", 1240, 215);
	//[3].setScale(1.5, 1);
	Tplayers[3].setColor(Color(0, 0, 0, 255));

}
Text Play::setText(string inscription, int pos_x, int pos_y)
{
	Text temp;
	temp.setFont(font);
	temp.setString(inscription);
	temp.setPosition(pos_x, pos_y);
	return temp;
}