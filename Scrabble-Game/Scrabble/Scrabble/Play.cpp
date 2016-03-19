#include "Play.h"


Play::Play()
{
	

}
void Play::Start()
{
	playWindow = new RenderWindow(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
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
		playWindow->display();
	}
}