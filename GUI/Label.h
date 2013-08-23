#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "TextWidget.h"

class Label: public TextWidget
{
	public:

		Label();
		Label(sf::Vector2f pos, sf::Vector2f size);
		Label(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color);
		Label(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font);

		void update();

	private:

		void init();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // LABEL_H_INCLUDED