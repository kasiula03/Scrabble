#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class Button : public sf::Drawable, sf::Transformable
{
	std::string text;
	sf::Text buttonText;
	int pos_x;
	int pos_y;
	sf::Sprite sprite;
	sf::Texture texture;
	bool haveImage;

	static sf::Font font;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	Button();
	Button(std::string text, int pos_x, int pos_y, int char_size = 30);
	void setButtonImage(std::string patch, int width, int height);
	bool ifMousePressed(sf::RenderWindow * window);

};