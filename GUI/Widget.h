#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GUIObject.h"

class GUILayer;

class Widget: public GUIObject
{
	public:

		Widget();
		Widget(sf::Vector2f position);
		Widget(sf::Vector2f position, sf::Vector2f size);

		~Widget();

		virtual void update() = 0;

		// setters

		void setLayer(GUILayer* layer);
		void giveFocus();
		void removeFocus();

		// getters

		GUILayer* getLayer();
		bool hasFocus();

	protected:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		GUILayer* m_layer;

	private:


};

#endif // WIDGET_H_INCLUDED