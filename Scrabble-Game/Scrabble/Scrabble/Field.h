#pragma once
#include "Letter.h"

class Field : public sf::Drawable, sf::Transformable
{
	friend class Play;
	friend class WordController;
	
	//upper-left corner
	int pos_x; 
	int pos_y;

	//all fields have the same size
	int width = 40;
	int height = 40;

	string bonus;
	sf::RectangleShape collider;

	Field();
	Field(int pos_x, int pos_y);
	bool ifLetterTouching(Letter * letter); //check if letter touching our field

public:
	int getPositionX();
	int getPositionY();
	bool occupied;

	string getBonus();
	void setBonus(string);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; //trzeba potem skasowac
};