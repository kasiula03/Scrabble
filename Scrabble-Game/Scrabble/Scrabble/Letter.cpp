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
}
Letter::Letter()
{
	
}

Letter::Letter(const Letter & letter)
{
	this->points = letter.points;
	this->sign = letter.sign;
	this->texture = letter.texture;
	this->sprite.setTexture(this->texture);
}
Letter& Letter::operator=(Letter const& lt)
{
	this->points = lt.points;
	this->sign = lt.sign;
	this->texture = lt.texture;
	this->sprite.setTexture(this->texture);
	return *this;
}

void Letter::dragAndDrop()
{

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