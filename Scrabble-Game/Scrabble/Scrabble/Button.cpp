#include "Button.h"
#include <Windows.h>
#include <iostream>

sf::Font Button::font;

Button::Button()
{
	Button("NONE", 0, 0, 30);
}

Button::Button(std::string text, int pos_x, int pos_y, int char_size)
{
	this->haveImage = false;
	this->text = text;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->buttonText.setFont(font);
	this->buttonText.setColor(sf::Color(0, 0, 0, 255));
	this->buttonText.setString(this->text);
	this->buttonText.setCharacterSize(char_size);
	this->buttonText.setPosition(pos_x, pos_y);

	if (!font.loadFromFile("data/WorkSans-Black.otf"))
	{
		MessageBox(NULL, "Fond not found", "ERROR", NULL);
	}

}

bool Button::ifMousePressed(sf::RenderWindow * window)
{
	sf::Vector2f pos(buttonText.getGlobalBounds().left, buttonText.getGlobalBounds().top);
	sf::Vector2f size(buttonText.getGlobalBounds().width, buttonText.getGlobalBounds().height);
	sf::FloatRect newRect(static_cast < sf::Vector2f >(window->mapCoordsToPixel(pos)), 
		static_cast < sf::Vector2f >(window->mapCoordsToPixel(size)));

	if (newRect.contains(static_cast <sf::Vector2f>(sf::Mouse::getPosition(*window))))
	{
		buttonText.setColor(sf::Color::Cyan);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return true;
		}

	}
	else
	{
		buttonText.setColor(sf::Color::Black);
		return false;
	}

}

void Button::setButtonImage(std::string patch, int width, int height)
{
	if (!texture.loadFromFile(patch))
	{
		std::cout << "Nie wczytano tekstury!" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(width, height);
	this->haveImage = true;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if(haveImage) target.draw(sprite);
	target.draw(buttonText);
	
}