#include "ImageWidget.h"

ImageWidget::ImageWidget()
	: m_texture(GUICore::getEmptyTexture())
{
	init();
}

ImageWidget::ImageWidget(sf::Vector2f position, sf::Vector2f size)
	: Widget(position, size), m_texture(GUICore::getEmptyTexture())
{
	init();
}

ImageWidget::ImageWidget(sf::Vector2f position, sf::Vector2f size, TexturePtr texture)
	: Widget(position, size), m_texture(texture)
{
	init();
}

void ImageWidget::setTexture(TexturePtr texture){
	m_texture = texture;

	m_image.setTexture(*m_texture);
}

TexturePtr ImageWidget::getTexture(){
	return m_texture;
}

void ImageWidget::init(){
	m_image.setTexture(*m_texture, true);
}

void ImageWidget::update(){
	m_image.setTexture(*m_texture, true);
	m_image.setPosition(getRealPosition());
}

void ImageWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(m_image, states);
}
