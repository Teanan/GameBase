#ifndef PASSWORDTEXTBOX_H_INCLUDED
#define PASSWORDTEXTBOX_H_INCLUDED

#include <boost/shared_ptr.hpp>

#include "Textbox.h"

typedef boost::shared_ptr<sf::Texture> TexturePtr;

class PasswordTextbox: public Textbox
{
	public:

		PasswordTextbox();
		PasswordTextbox(sf::Vector2f position, sf::Vector2f size);
		PasswordTextbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color);
		PasswordTextbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font);
		PasswordTextbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, TexturePtr texture);
		PasswordTextbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font, TexturePtr texture);

	private:
		
		void offsetText();

};

#endif // PASSWORDTEXTBOX_H_INCLUDED