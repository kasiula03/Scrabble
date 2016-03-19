#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Play
{
protected:
	Play();

	RenderWindow * playWindow;

	void Start();
};