#include "WorldRenderer.h"
#include "Camera.h"

#include "../server/GameAssets/Map.h"

WorldRenderer::WorldRenderer(){

}

WorldRenderer::~WorldRenderer(){

}

DrawableMapPtr WorldRenderer::getMap(){
	return m_map;
}

Camera& WorldRenderer::getCamera(){
	return m_camera;
}

void WorldRenderer::init(){

}

void WorldRenderer::unload(){

}

void WorldRenderer::update(sf::Time frameTime){
	//sf::Uint32 posX = me.getPosition().getMapXY().x * 32;
	//sf::Uint32 posY = me.getPosition().getMapXY().y * 32;

	//if (posX + 400 < m_map->getMap()->getSize().x * 32)
	//	m_camera.updateX(posX);
	//if (posY + 300 < m_map->getMap()->getSize().y * 32)
	//	m_camera.updateY(posY);

	m_camera.update();
	//m_map->setView(m_camera.getView());
	
	//me.update(frameTime);
}

void WorldRenderer::render(sf::RenderTarget* target){
	target->setView(m_camera.getView());

	//target->draw(*m_map.get());
	//target->draw(me);

	target->setView(target->getDefaultView());
}