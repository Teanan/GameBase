#include "Textbox.h"

#include <iostream>
#include <cmath>

Textbox::Textbox()
	: m_texture(GUICore::getEmptyTexture()),
	m_offset(0), m_cutText(0), m_cursor(0), m_validated(false)
{
	init();
}

Textbox::Textbox(sf::Vector2f position, sf::Vector2f size)
	: TextWidget(position, size), m_texture(GUICore::getEmptyTexture()),
	m_offset(0), m_cutText(0), m_cursor(0), m_validated(false)
{
	init();
}

Textbox::Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color)
	: TextWidget(position, size, text, textSize, color), m_texture(GUICore::getEmptyTexture()),
	m_offset(0), m_cutText(0), m_cursor(0), m_validated(false)
{
	init();
}

Textbox::Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font)
	: TextWidget(position, size, text, textSize, color, font), m_texture(GUICore::getEmptyTexture()),
	m_offset(0), m_cutText(0), m_cursor(0), m_validated(false)
{
	init();
}
	
Textbox::Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, TexturePtr texture)
	: TextWidget(position, size, text, textSize, color), m_texture(texture),
	m_offset(0), m_cutText(0), m_cursor(0), m_validated(false)
{
	init();
}

Textbox::Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font, TexturePtr texture)
	: TextWidget(position, size, text, textSize, color, font), m_texture(texture),
	m_offset(0), m_cutText(0), m_cursor(0), m_validated(false)
{
	init();
}

void Textbox::setTexture(TexturePtr texture){
	m_texture = texture;
}

void Textbox::setText(std::string text){
	m_realText = text;
	offsetText();

	while(m_cursor != m_realText.size()){
		if (m_cursor == m_cutText && m_cutText < m_realText.size()) m_offset++;
		m_cursor++;
		updateDrawableTextPosition();
		offsetText();
	}
	offsetText();
}

TexturePtr Textbox::getTexture(){
	return m_texture;
}

std::string Textbox::getText(){
	return m_realText;
}

bool Textbox::validated(){
	return m_validated;
}

void Textbox::init(){
	setTextAlignment(TextWidget::LeftAligned);
	m_realText = m_text;
	m_cursor = m_realText.size();
	m_cursorClock.restart();
	m_cutText = 1;

	m_cursorShape = sf::RectangleShape(sf::Vector2f(1, m_textSize));
	m_cursorShape.setFillColor(m_textColor);
	
	updateDrawableTextPosition();
	offsetText();
	textUpdated();
}

void Textbox::textUpdated(){
	TextWidget::textUpdated();

	m_cursorShape.setSize(sf::Vector2f(1, m_textSize));
	m_cursorShape.setOrigin(0, m_textSize / 2.f);

	if (m_drawableText.getString().getSize() == 0 && getTextAlignment() == TextWidget::LeftAligned)
		m_cursorShape.setPosition(getRealPosition().x + 8, getRealPosition().y + getSize().y / 2.f);
	else if (m_drawableText.getString().getSize() == 0 && getTextAlignment() == TextWidget::RightAligned)
		m_cursorShape.setPosition(getRealPosition().x  + getSize().x - 8, getRealPosition().y + getSize().y / 2.f);
	else m_cursorShape.setPosition(m_drawableText.findCharacterPos(m_cursor - m_offset).x, getRealPosition().y + getSize().y / 2.f);
}

void Textbox::offsetText(){
	updateDrawableTextPosition();
	m_cutText = 1;
	if (m_drawableText.getString() != "" && getSize().x != 0){
		for (sf::Uint32 i(m_drawableText.getString().getSize() + 1); i >= 0; i--){
			sf::Vector2f chr(m_drawableText.findCharacterPos(i));

			if (chr.x < (getRealPosition().x + getSize().x - 16)){
				m_cutText = m_offset + i;
				break;
			}
		}
	}

	if ((m_cutText - m_offset) > m_realText.size()) m_offset = 0;

	m_text = m_realText.substr(m_offset, m_cutText);
	textUpdated();
}

void Textbox::update(){
	if (m_cursor > m_realText.size()) m_cursor = m_realText.size() - 1;
	if (m_realText.size() == 0) m_cursor = 0;

	m_validated = false;

	if (GUICore::events()->isEventThrown(GUIEvents::TextEntered) && hasFocus()){
		unsigned int c = (unsigned int)GUICore::events()->getTextEntered();
		if (c == 8){ // backspace
			if (m_realText.size() > 0 && m_cursor > 0){
				m_realText.erase(m_realText.begin() + m_cursor - 1);
				m_cursor--;
				if (m_offset > 0 && m_offset == m_cursor) m_offset--;
				offsetText();
			}
		}else if (c == 13){ // carrige return
			m_validated = true;
			removeFocus();
		}else if ((c >= 32 && c <= 126) || (c >= 128 && c <= 168) || (c >= 224 && c <= 253)){ // ascii codes and extended ascii
			m_realText.insert(m_realText.begin() + m_cursor, GUICore::events()->getTextEntered());
			updateDrawableTextPosition();
			offsetText();
			if (m_cursor >= m_cutText && m_cutText < m_realText.size() && m_cutText > 0) m_offset++;
			m_cursor++;
			offsetText();
		}
	}

	if (GUICore::events()->isEventThrown(GUIEvents::SfKeyPressed) && hasFocus()){
		if (GUICore::events()->getKeyCode() == sf::Keyboard::Left || GUICore::events()->getKeyCode() == sf::Keyboard::Right){
			if (GUICore::events()->getKeyCode() == sf::Keyboard::Left && m_cursor > 0){
				m_cursor--;
				if (m_offset > 0 && m_cursor == m_offset) m_offset--;
			}
			if (GUICore::events()->getKeyCode() == sf::Keyboard::Right && m_cursor < m_realText.size()){
				if (m_cursor == m_cutText && m_cutText < m_realText.size()) m_offset++;
				m_cursor++;
			}
			offsetText();
		}
		if (GUICore::events()->getKeyCode() == sf::Keyboard::Delete && m_cursor < m_realText.size()){
			m_realText.erase(m_realText.begin() + m_cursor);
			offsetText();
		}
		if (GUICore::events()->getKeyCode() == sf::Keyboard::Home){
			m_cursor = 0;
			m_offset = 0;
			offsetText();
		}
		if (GUICore::events()->getKeyCode() == sf::Keyboard::End){
			while(m_cursor != m_realText.size()){
				if (m_cursor == m_cutText && m_cutText < m_realText.size()) m_offset++;
				m_cursor++;
				updateDrawableTextPosition();
				offsetText();
			}
			offsetText();
		}
	}

	if (m_cursorClock.getElapsedTime() >= sf::seconds(0.5) && hasFocus()){
		m_cursorShape.setFillColor(m_cursorShape.getFillColor() != sf::Color::Transparent ? sf::Color::Transparent : m_textColor);
		m_cursorClock.restart();
	}
	if (!hasFocus()) m_cursorShape.setFillColor(sf::Color::Transparent);

	updateDrawableTextPosition();

	if (GUICore::events()->isEventThrown(GUIEvents::MouseButtonClicked)){
		sf::FloatRect rect(getRealPosition().x, getRealPosition().y, getSize().x, getSize().y);
		if (rect.contains(GUICore::events()->getMousePosition().x, GUICore::events()->getMousePosition().y)){
			giveFocus();

			sf::Uint32 length(getSize().x * 2);
			for (sf::Uint32 i(0); i <= m_text.size(); i++){
				sf::Vector2f chr(m_drawableText.findCharacterPos(i));
				sf::Vector2f mouse(GUICore::events()->getMousePosition());

				sf::Uint32 l = sqrt(pow(chr.x - mouse.x, 2) + pow(chr.y - mouse.y, 2));
				if (l < length){
					length = l;
					m_cursor = i + m_offset;
				}
			}
			offsetText();
		}
	}
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	sf::Sprite sprite(*m_texture, sf::IntRect(1, 0, 8, 8));
	sprite.setPosition(getRealPosition());
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(9, 0, 8, 8));
	sprite.setPosition(getRealPosition().x + getSize().x - 8, getRealPosition().y);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(1, 16, 8, 8));
	sprite.setPosition(getRealPosition().x, getRealPosition().y + getSize().y - 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(9, 16, 8, 8));
	sprite.setPosition(getRealPosition().x + getSize().x - 8, getRealPosition().y + getSize().y - 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(1, 24, 8, 8));
	sprite.setScale((getSize().x - 16.f) / 8.f, 1);
	sprite.setPosition(getRealPosition().x + 8, getRealPosition().y);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(9, 24, 8, 8));
	sprite.setScale((getSize().x - 16.f) / 8.f, 1);
	sprite.setPosition(getRealPosition().x + 8, getRealPosition().y + getSize().y - 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(1, 8, 8, 8));
	sprite.setScale(1, (getSize().y - 16.f) / 8.f);
	sprite.setPosition(getRealPosition().x, getRealPosition().y + 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(9, 8, 8, 8));
	sprite.setScale(1, (getSize().y - 16.f) / 8.f);
	sprite.setPosition(getRealPosition().x + getSize().x - 8, getRealPosition().y + 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(0, 0, 1, 1));
	sprite.setScale(getSize().x - 16.f, getSize().y - 16.f);
	sprite.setPosition(getRealPosition() + sf::Vector2f(8, 8));
	target.draw(sprite, states);

	target.draw(m_drawableText, states);

	target.draw(m_cursorShape, states);
}