#include "Widget.h"
#include "GUILayer.h"

Widget::Widget(): m_layer(0){
	setLayer(GUICore::getMainLayer());
}

Widget::Widget(sf::Vector2f position): GUIObject(position), m_layer(0)
{
	setLayer(GUICore::getMainLayer());
}

Widget::Widget(sf::Vector2f position, sf::Vector2f size): GUIObject(position, size), m_layer(0)
{
	setLayer(GUICore::getMainLayer());
}

Widget::~Widget(){
	removeFocus();
	setLayer(0);
}

void Widget::setLayer(GUILayer* layer){
	if (m_layer != 0) m_layer->removeWidget(this);

	m_layer = layer;

	if (m_layer != 0) m_layer->addWidget(this);
}

GUILayer* Widget::getLayer(){
	return m_layer;
}

void Widget::giveFocus(){
	if (hasFocus() || m_layer == 0) return;

	m_layer->setFocusedWidget(this);
}

void Widget::removeFocus(){
	if (!hasFocus() || m_layer == 0) return;

	m_layer->setFocusedWidget(0);
}

bool Widget::hasFocus(){
	if (m_layer == 0) return true;

	return (m_layer->getFocusedWidget() == this);
}