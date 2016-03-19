#pragma once

#include <SFML\Graphics.hpp>
#include <cstring>
using namespace sf;
using namespace std;

class Play
{
protected:
	static Font font;

	RenderWindow * playWindow;

	Sprite Layout;
	Texture texture;
	Text Tplayers[4];

	void InitializePlay();
	void Start();

	Text setText(string, int, int);
};