#ifndef IMAGEWIDGET_H_INCLUDED
#define IMAGEWIDGET_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <boost/shared_ptr.hpp>

#include "Widget.h"

typedef boost::shared_ptr<sf::Texture> TexturePtr;

class ImageWidget: public Widget
{
	public:

		ImageWidget();
		ImageWidget(sf::Vector2f position, sf::Vector2f size);
		ImageWidget(sf::Vector2f position, sf::Vector2f size, TexturePtr texture);

		void update();

		// setters

		void setTexture(TexturePtr texture);

		// getters

		TexturePtr getTexture();

	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void init();

		TexturePtr m_texture;
		sf::Sprite m_image;

};

#endif // IMAGEWIDGET_H_INCLUDED