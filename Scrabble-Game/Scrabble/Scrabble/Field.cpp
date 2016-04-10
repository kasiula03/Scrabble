#include "Field.h"

Field::Field()
{
	Field(0, 0);
}

Field::Field(int pos_x, int pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	collider.setPosition(pos_x, pos_y);
	collider.setSize(Vector2f(width, height));

	collider.setFillColor(sf::Color(255, 232, 54, 120));
	setBonus("None");
	//collider.setOrigin(32, 32);
	
}
string Field::getBonus()
{
	return bonus;
}
void Field::setBonus(string bonus)
{
	this->bonus = bonus;
}
int Field::getPositionX()
{
	return this->pos_x;
}

int Field::getPositionY()
{
	return this->pos_y;
}

bool Field::ifLetterTouching(Letter * letter)
{
	int distanceX = (pos_x + 20) - (letter->getPositionX() + 20);
	int distanceY = (pos_y + 20) - (letter->getPositionY() + 20);
	if (distanceX < 20 && distanceY < 20)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	
	target.draw(collider);
}