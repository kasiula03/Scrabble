#include "Letter.h"
#include <iostream>
int Letter::letterCounter = 0;
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
	this->id = letter.id;
}
Letter& Letter::operator=(Letter const& lt)
{
	this->points = lt.points;
	this->sign = lt.sign;
	this->texture = lt.texture;
	this->sprite.setTexture(this->texture);
	this->placed = lt.placed;
	//this->pos_x = lt.pos_x;
	//this->pos_y = lt.pos_y;
	this->id = lt.id;
	return *this;
}
bool Letter::operator <(const Letter& letter) const
{
	int x = this->pos_x;
	int x2 = letter.pos_x;
	return x < x2;
}
bool Letter::dragAndDrop(sf::RenderWindow * window)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
			sf::Vector2f pos(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
			sf::Vector2f size(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
			sf::FloatRect newRect(static_cast < sf::Vector2f >(window->mapCoordsToPixel(pos)),
				static_cast < sf::Vector2f >(window->mapCoordsToPixel(size)));

			//cout << Mouse::getPosition().x << " " << Mouse::getPosition().y << endl;
			//cout << allLeters[0].getPositionX() << " " << allLeters[0].getPositionY() << endl;
			if (newRect.contains(static_cast <sf::Vector2f>(sf::Mouse::getPosition(*window))))
				return true;
			else
				return false;
		
	}
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