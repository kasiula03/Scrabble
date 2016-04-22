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
	bool dragAndDrop(sf::RenderWindow * window);
	int getPositionX();
	int getPositionY();

	bool operator <(const Letter& letter) const;
	bool operator ==(const Letter & letter);

	static int letterCounter;
	int id;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	Sprite sprite;
	bool placed;

	int pos_x;
	int pos_y;

private:
	char sign; // sign which represent our letter
	int points; // amount points our letter

	
	

	Texture texture;
};