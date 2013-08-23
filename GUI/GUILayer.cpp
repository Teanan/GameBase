#include "GUILayer.h"
#include "Widget.h"

GUILayer::GUILayer(): m_focusedWidget(0)
{

}

GUILayer::GUILayer(sf::Vector2f position, sf::Vector2f size): GUIObject(position, size), m_focusedWidget(0)
{

}

void GUILayer::addWidget(Widget* widget){
	if (widget->getLayer() != this) widget->setLayer(this);

	for (std::vector<Widget*>::iterator it = m_widgets.begin(); it < m_widgets.end(); it++){
		if (*it == widget) return;
	}

	m_widgets.push_back(widget);
}

void GUILayer::removeWidget(Widget* widget){
	for (std::vector<Widget*>::iterator it = m_widgets.begin(); it < m_widgets.end(); it++){
		if (*it == widget){
			if (widget->getLayer() == this) widget->setLayer(0);
			m_widgets.erase(it);
			return;
		}
	}
}

void GUILayer::setFocusedWidget(Widget* widget){
	if (getFocusedWidget() == widget) return;

	m_focusedWidget = widget;
}

Widget* GUILayer::getFocusedWidget(){
	return m_focusedWidget;
}

void GUILayer::update(){

}

void GUILayer::draw(sf::RenderTarget& target, sf::RenderStates states) const{

}
