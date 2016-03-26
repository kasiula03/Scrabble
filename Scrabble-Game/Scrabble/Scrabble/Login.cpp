#include "Login.h"

#include "GlobalFunctions.h"
using namespace sf;

Login::Login()
{
	GlobalFunctions::setText(txts[0], "Zaloguj sie", 100, 100);
	GlobalFunctions::setText(txts[1], "Login: ", 70, 150);
	GlobalFunctions::setText(txts[2], "Haslo: ", 70, 200);
	//runLoginWindow();
}

std::string Login::runLoginWindow()
{
	RenderWindow windoww(VideoMode(1366, 768), "Scrabble multiplayer", Style::Default);
	bool opened = true;
	while (opened)
	{

		RectangleShape rec;

		rec.setSize(Vector2f(200, 200));
		rec.setPosition(90, 100);
		rec.setFillColor(Color(0, 0, 0, 0));
		rec.setOutlineThickness(2);
		rec.setOutlineColor(Color::White);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			windoww.close();
			opened = false;
			return "Guest2";
		}

		windoww.clear(Color(50, 50, 50, 255));
		windoww.draw(txts[0]);
		windoww.draw(txts[1]);
		windoww.draw(txts[2]);
		//window.draw(rec);
		windoww.display();
	}
	return "None";
}

bool Login::tryToLogin(std::string usr, std::string password)
{
	return true;
}