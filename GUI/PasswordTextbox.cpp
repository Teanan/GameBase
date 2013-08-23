#include "PasswordTextbox.h"

PasswordTextbox::PasswordTextbox(){

}

PasswordTextbox::PasswordTextbox(sf::Vector2f position, sf::Vector2f size)
	: Textbox(position, size)
{

}

PasswordTextbox::PasswordTextbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color)
	: Textbox(position, size, text, textSize, color)
{

}

PasswordTextbox::PasswordTextbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font)
	: Textbox(position, size, text, textSize, color, font)
{

}
	
PasswordTextbox::PasswordTextbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, TexturePtr texture)
	: Textbox(position, size, text, textSize, color, texture)
{

}

PasswordTextbox::PasswordTextbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font, TexturePtr texture)
	: Textbox(position, size, text, textSize, color, font, texture)
{

}

void PasswordTextbox::offsetText(){
	Textbox::offsetText();

	m_text.replace(m_text.begin(), m_text.end(), m_text.size(), '*');
	textUpdated();
}