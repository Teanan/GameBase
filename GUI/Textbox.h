#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <boost/shared_ptr.hpp>

#include "TextWidget.h"

typedef boost::shared_ptr<sf::Texture> TexturePtr;

class Textbox: public TextWidget
{
	public:

		// constructors

		Textbox();
		Textbox(sf::Vector2f position, sf::Vector2f size);
		Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color);
		Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font);
		Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, TexturePtr texture);
		Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font, TexturePtr texture);
		
		// setters

		void setTexture(TexturePtr);
		void setText(std::string text);

		// getters

		TexturePtr getTexture();
		std::string getText();

		bool validated();
		
		void update();

	protected:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void init();
		void textUpdated();
		virtual void offsetText();

		TexturePtr m_texture;
		std::string m_realText;
		sf::Uint32 m_offset;
		sf::Uint32 m_cutText;
		sf::Uint32 m_cursor;
		bool m_validated;

		sf::Clock m_cursorClock;

		sf::RectangleShape m_cursorShape;
};

#endif // TEXTBOX_H_INCLUDED