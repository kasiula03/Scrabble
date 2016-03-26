#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Letter : public sf::Drawable, sf::Transformable
{
	
public:
	Letter(char, int);
	Letter(const Letter & letter);
	Letter();
	void SetSign(char);
	char GetSign();
	void SetPoints(int);
	int GetPoints();

	Letter& operator= (Letter const& lt);

	void setPosition(int x, int y);
	void dragAndDrop();
	int getPositionX();
	int getPositionY();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	Sprite sprite;

private:
	char sign; // sign which represent our letter
	int points; // amount points our letter

	int pos_x;
	int pos_y;
	
	Texture texture;
};