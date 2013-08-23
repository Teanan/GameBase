#ifndef WIDGETSLAYER_H_INCLUDED
#define WIDGETSLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <vector>

#include "GUILayer.h"

class WidgetsLayer: public GUILayer
{
	public:

		WidgetsLayer();
		WidgetsLayer(sf::Vector2f position, sf::Vector2f size);

		void update();
		
	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void init();

		sf::View m_view;
};

#endif // WIDGETSLAYER_H_INCLUDED