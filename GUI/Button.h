#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

#include "TextWidget.h"

typedef boost::shared_ptr<sf::Texture> TexturePtr;

class Button: public TextWidget
{
	public:

		enum State
		{
			Normal = 1,
			Hovered,
			Clicked
		};
		
		// constructors

		Button();
		Button(sf::Vector2f position, sf::Vector2f size);
		Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color);
		Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font);
		Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, TexturePtr texture);
		Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font, TexturePtr texture);
		
		void update();

		bool clicked();

		// setters

		void setTexture(TexturePtr);
		void setState(State);

		// getters
		
		TexturePtr getTexture();
		State getState();

	protected:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		TexturePtr m_texture;

		State m_state;
		State m_lastState;
};
#endif // BUTTON_H_INCLUDED