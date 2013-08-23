#include "Button.h"

Button::Button()
	: m_texture(GUICore::getEmptyTexture()), m_state(Normal), m_lastState(Normal)
{
	setTextAlignment(TextWidget::CentrallyAligned);
}

Button::Button(sf::Vector2f position, sf::Vector2f size)
	: TextWidget(position, size), m_texture(GUICore::getEmptyTexture()),
	m_state(Normal), m_lastState(Normal)
{
	setTextAlignment(TextWidget::CentrallyAligned);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color)
	:  TextWidget(position, size, text, textSize, color), m_texture(GUICore::getEmptyTexture()),
	m_state(Normal), m_lastState(Normal)
{
	setTextAlignment(TextWidget::CentrallyAligned);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font)
	:  TextWidget(position, size, text, textSize, color, font), m_texture(GUICore::getEmptyTexture()),
	m_state(Normal), m_lastState(Normal)
{
	setTextAlignment(TextWidget::CentrallyAligned);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, TexturePtr texture)
	:  TextWidget(position, size, text, textSize, color), m_texture(texture),
	m_state(Normal), m_lastState(Normal)
{
	setTextAlignment(TextWidget::CentrallyAligned);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font, TexturePtr texture)
	:  TextWidget(position, size, text, textSize, color, font), m_texture(texture),
	m_state(Normal), m_lastState(Normal)
{
	setTextAlignment(TextWidget::CentrallyAligned);
}

void Button::setTexture(TexturePtr texture){
	m_texture = texture;
}

void Button::update(){
	updateDrawableTextPosition();

	m_lastState = m_state;
	
	sf::FloatRect rect(getRealPosition().x, getRealPosition().y, getSize().x, getSize().y);

	if (!rect.contains(GUICore::events()->getMousePosition().x, GUICore::events()->getMousePosition().y)){
		m_state = Normal;
		return;
	}

	if (rect.contains(GUICore::events()->getMousePosition().x, GUICore::events()->getMousePosition().y) && GUICore::events()->getMouseBoutonState(sf::Mouse::Left) == GUIEvents::StateReleased){
		m_state = Hovered;
		return;
	}

	if (GUICore::events()->getMouseBoutonState(sf::Mouse::Left) == GUIEvents::StatePressed && m_state == Hovered){
		m_state = Clicked;
		giveFocus();
	}
}

bool Button::clicked(){
	return (m_lastState == Clicked && m_state == Hovered);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	sf::Sprite sprite(*m_texture, sf::IntRect(1 + (m_state - 1) * 16, 0, 8, 8));
	sprite.setPosition(getRealPosition());
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(9 + (m_state - 1) * 16, 0, 8, 8));
	sprite.setPosition(getRealPosition().x + getSize().x - 8, getRealPosition().y);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(1 + (m_state - 1) * 16, 16, 8, 8));
	sprite.setPosition(getRealPosition().x, getRealPosition().y + getSize().y - 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(9 + (m_state - 1) * 16, 16, 8, 8));
	sprite.setPosition(getRealPosition().x + getSize().x - 8, getRealPosition().y + getSize().y - 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(1 + (m_state - 1) * 16, 24, 8, 8));
	sprite.setScale((getSize().x - 16.f) / 8.f, 1);
	sprite.setPosition(getRealPosition().x + 8, getRealPosition().y);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(9 + (m_state - 1) * 16, 24, 8, 8));
	sprite.setScale((getSize().x - 16.f) / 8.f, 1);
	sprite.setPosition(getRealPosition().x + 8, getRealPosition().y + getSize().y - 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(1 + (m_state - 1) * 16, 8, 8, 8));
	sprite.setScale(1, (getSize().y - 16.f) / 8.f);
	sprite.setPosition(getRealPosition().x, getRealPosition().y + 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(9 + (m_state - 1) * 16, 8, 8, 8));
	sprite.setScale(1, (getSize().y - 16.f) / 8.f);
	sprite.setPosition(getRealPosition().x + getSize().x - 8, getRealPosition().y + 8);
	target.draw(sprite, states);

	sprite.setTextureRect(sf::IntRect(0, m_state - 1, 1, 1));
	sprite.setScale(getSize().x - 16.f, getSize().y - 16.f);
	sprite.setPosition(getRealPosition() + sf::Vector2f(8, 8));
	target.draw(sprite, states);

	target.draw(m_drawableText, states);
}