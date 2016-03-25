#pragma once

#include <SFML\Graphics.hpp>
#include <cstring>
#include "GlobalFunctions.h"
using namespace sf;
using namespace std;

class Play
{
protected:
	Play();

	static Font font;

	RenderWindow * playWindow;

	Sprite Layout;
	Texture texture;
	Text Tplayers[4];

	void Start();

};