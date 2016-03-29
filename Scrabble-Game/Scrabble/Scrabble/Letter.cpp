#include "Letter.h"
#include <iostream>
void Letter::SetSign(char sign)
{
	this->sign = sign;
}
char Letter::GetSign()
{
	return this->sign;
}
void Letter::SetPoints(int points)
{
	this->points = points;
}
int Letter::GetPoints()
{
	return this->points;
}

Letter::Letter(char sign, int points)
{
	string patchOfFile = "data//Graphs//Letters//Letter_" + string(1,sign) + ".png";
	SetSign(sign);
	SetPoints(points);
	
	if (!texture.loadFromFile(patchOfFile))
	{
		cout << "Nie wczytano tekstury!" << endl;
	}
	sprite.setTexture(texture);
	placed = false;
}
Letter::Letter()
{
	
}

Letter::Letter(const Letter & letter)
{
	setPosition(letter.pos_x, letter.pos_y);
	this->points = letter.points;
	this->sign = letter.sign;
	this->texture = letter.texture;
	this->sprite.setTexture(this->texture);
	this->placed = letter.placed;
}
Letter& Letter::operator=(Letter const& lt)
{
	this->points = lt.points;
	this->sign = lt.sign;
	this->texture = lt.texture;
	this->sprite.setTexture(this->texture);
	this->placed = lt.placed;
	return *this;
}

bool Letter::dragAndDrop()
{
	int dist_x = Mouse::getPosition().x - (pos_x + 10);
	int dist_y = Mouse::getPosition().y - (pos_y + 25);
	//cout << Mouse::getPosition().x << " " << Mouse::getPosition().y << endl;
	//cout << allLeters[0].getPositionX() << " " << allLeters[0].getPositionY() << endl;
	if (dist_x < 40 && dist_x > 0 && dist_y < 40 && dist_y > 0)
		return true;
	else 
		return false;
	
	
}

int Letter::getPositionX()
{
	return pos_x;
}

int Letter::getPositionY()
{
	return pos_y;
}

void Letter::setPosition(int x, int y)
{
	this->pos_x = x;
	this->pos_y = y;
	this->sprite.setPosition(pos_x, pos_y);
}

void Letter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(sprite);
}