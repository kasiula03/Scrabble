#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Letter
{
	
public:
	Letter(char, int);
	Letter();
	void SetSign(char);
	char GetSign();
	void SetPoints(int);
	int GetPoints();

private:
	char sign; // sign which represent our letter
	int points; // amount points our letter
	Sprite sprite;
	Texture texture;
};