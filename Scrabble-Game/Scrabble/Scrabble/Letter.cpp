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
	//string patchOfFile = "data//Graphs//Letters//Letter_" + string(1,sign) + ".png";
	SetSign(sign);
	SetPoints(points);
	
	//if (!texture.loadFromFile(patchOfFile))
	//{
		//cout << "Nie wczytano tekstury!" << endl;
	//}
	sprite.setTexture(texture);
}
Letter::Letter()
{
	
}