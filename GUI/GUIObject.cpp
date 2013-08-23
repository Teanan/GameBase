#include "GUIObject.h"

GUIObject::GUIObject(): m_originBehaviour(DefaultOrigin){

}

GUIObject::GUIObject(sf::Vector2f position): m_position(position), m_originBehaviour(DefaultOrigin)
{

}

GUIObject::GUIObject(sf::Vector2f position, sf::Vector2f size): m_position(position), m_size(size), m_originBehaviour(DefaultOrigin)
{

}

void GUIObject::setPosition(sf::Vector2f position){
	m_position = position;
}

void GUIObject::setSize(sf::Vector2f size){
	m_size = size;
}

void GUIObject::setOriginBehaviour(GUIObject::OriginBehaviour origin){
	m_originBehaviour = origin;
}

sf::Vector2f GUIObject::getPosition() const{
	return m_position;
}

sf::Vector2f GUIObject::getRealPosition() const{
	if (m_originBehaviour == DefaultOrigin) return m_position;
	if (m_originBehaviour == CentredOrigin) return sf::Vector2f(m_position.x - m_size.x / 2.f, m_position.y - m_size.y / 2.f);

	return sf::Vector2f(0, 0);
}

sf::Vector2f GUIObject::getSize() const{
	return m_size;
}

GUIObject::OriginBehaviour GUIObject::getOriginBehaviour() const{
	return m_originBehaviour;
}

GUIObject::OriginBehaviour GUIObject::originBehaviourFromString(std::string s){
	if (s == "DefaultOrigin") return DefaultOrigin;
	if (s == "CentredOrigin") return CentredOrigin;
	
	return DefaultOrigin;
}