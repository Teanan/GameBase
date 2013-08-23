#include "Label.h"

Label::Label(){
	init();
}

Label::Label(sf::Vector2f position, sf::Vector2f size)
	: TextWidget(position, size)
{
	init();
}

Label::Label(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color)
	: TextWidget(position, size, text, textSize, color)
{
	init();
}

Label::Label(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font)
	: TextWidget(position, size, text, textSize, color, font)
{
	init();
}

void Label::init(){
	setTextAlignment(TextWidget::LeftAligned);
	updateDrawableTextPosition();
}

void Label::update(){

}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(m_drawableText, states);
}