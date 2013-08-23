#include "TextWidget.h"

TextWidget::TextWidget()
	: m_textSize(12), m_font(GUICore::getDefaultFont()), m_alignment(CentrallyAligned)
{
	textUpdated();
}

TextWidget::TextWidget(sf::Vector2f position, sf::Vector2f size)
	: Widget(position, size), m_textSize(12), m_font(GUICore::getDefaultFont()), m_alignment(CentrallyAligned)
{
	textUpdated();
}

TextWidget::TextWidget(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color)
	:  Widget(position, size), m_text(text), m_textSize(textSize), m_textColor(color), m_font(GUICore::getDefaultFont()), m_alignment(CentrallyAligned)
{
	textUpdated();
}

TextWidget::TextWidget(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font)
	:  Widget(position, size), m_text(text), m_textSize(textSize), m_textColor(color), m_font(font), m_alignment(CentrallyAligned)
{
	textUpdated();
}

void TextWidget::setText(std::string text){
	m_text = text;
	textUpdated();
}

void TextWidget::setTextSize(sf::Uint32 size){
	m_textSize = size;
	textUpdated();
}

void TextWidget::setTextColor(sf::Color color){
	m_textColor = color;
	textUpdated();
}

void TextWidget::setFont(sf::Font& font){
	m_font = font;
	textUpdated();
}

void TextWidget::setTextAlignment(TextWidget::TextAlignment alignment){
	m_alignment = alignment;
	textUpdated();
}

void TextWidget::setPosition(sf::Vector2f position){
	Widget::setPosition(position);
	textUpdated();
	updateDrawableTextPosition();
}

void TextWidget::setSize(sf::Vector2f size){
	Widget::setSize(size);
	textUpdated();
	updateDrawableTextPosition();
}

void TextWidget::setOriginBehaviour(Widget::OriginBehaviour origin){
	Widget::setOriginBehaviour(origin);
	textUpdated();
	updateDrawableTextPosition();
}

std::string TextWidget::getText(){
	return m_text;
}

sf::Uint32 TextWidget::getTextSize(){
	return m_textSize;
}

sf::Color TextWidget::getTextColor(){
	return m_textColor;
}

sf::Font& TextWidget::getFont(){
	return m_font;
}

TextWidget::TextAlignment TextWidget::getTextAlignment(){
	return m_alignment;
}

TextWidget::TextAlignment TextWidget::textAlignmentFromString(std::string s){
	if (s == "CentrallyAligned") return CentrallyAligned;
	if (s == "LeftAligned") return LeftAligned;
	if (s == "RightAligned") return RightAligned;

	return LeftAligned;
}

void TextWidget::textUpdated(){
	m_drawableText.setString(m_text);
	m_drawableText.setCharacterSize(m_textSize);
	m_drawableText.setColor(m_textColor);
	m_drawableText.setFont(m_font);
	updateDrawableTextPosition();
}

void TextWidget::updateDrawableTextPosition(){
	switch (getTextAlignment()){
		case CentrallyAligned:
			m_drawableText.setOrigin(m_drawableText.getLocalBounds().width / 2.f, m_drawableText.getLocalBounds().height / 2.f);
			m_drawableText.setPosition(getRealPosition() + getSize() / 2.f);
			break;
		case LeftAligned:
			m_drawableText.setOrigin(0, m_drawableText.getLocalBounds().height / 2.f);
			m_drawableText.setPosition(getRealPosition().x + 8, getRealPosition().y + getSize().y / 2.f);
			break;
		case RightAligned:
			m_drawableText.setOrigin(m_drawableText.getLocalBounds().width, m_drawableText.getLocalBounds().height / 2.f);
			m_drawableText.setPosition(getRealPosition().x + getSize().x - 8, getRealPosition().y + getSize().y / 2.f);
			break;
	}
}