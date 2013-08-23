#ifndef GUILAYER_H_INCLUDED
#define GUILAYER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <vector>

#include "GUIObject.h"

class Widget;

class GUILayer: public GUIObject
{
	public:

		GUILayer();
		GUILayer(sf::Vector2f position, sf::Vector2f size);

		void update();
		
		void addWidget(Widget* widget);
		void removeWidget(Widget* widget);

		void setFocusedWidget(Widget* widget);
		Widget* getFocusedWidget();

	private:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void init();

		std::vector<Widget*> m_widgets;
		Widget* m_focusedWidget;
};

#endif // GUILAYER_H_INCLUDED