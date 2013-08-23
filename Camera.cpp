#include "Camera.h"
#include <iostream>

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::initialize()
{
	m_cameraX = m_cameraY = 0; 
}

void Camera::updateX(int x)
{
	m_cameraX = -(800 / 2) + x;
}

void Camera::updateY(int y)
{
	m_cameraY = -(600 / 2) + y;
}

void Camera::update()
{
    if(m_cameraX < 0)
        m_cameraX = 0;
    if(m_cameraY < 0)
        m_cameraY = 0;

	m_cameraPosition.setCenter(sf::Vector2f(400 + m_cameraX, 300 + m_cameraY));
}

void Camera::draw(sf::RenderWindow &Window)
{
    Window.setView(m_cameraPosition);
}

void Camera::setView(sf::View Camera)
{
    m_cameraPosition = Camera;
}

sf::View Camera::getView()
{
    return m_cameraPosition;
}
