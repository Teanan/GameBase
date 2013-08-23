#include "InGame.h"
#include "WorldRenderer.h"
#include "Application.h"

#include <iostream>

InGame::InGame(){
	m_worldRenderer = WorldRendererPtr(new WorldRenderer);
	m_worldRenderer->getCamera().setView(Application::instance()->getRenderWindow()->getDefaultView());
}

WorldRendererPtr InGame::getRenderer(){
	return m_worldRenderer;
}

void InGame::init(){
	m_worldRenderer->init();
}

void InGame::unload(){
	m_worldRenderer->unload();
}

void InGame::update(){
	m_worldRenderer->update(m_frameTime);
}

void InGame::render(sf::RenderTarget* target){
	checkInputs();
	
	// render world
	m_worldRenderer->render(target);

	// render gui


	fps++;
	if (m_clock.getElapsedTime() >= sf::seconds(1)){
		std::cout << fps << " " << m_frameTime.asMilliseconds() << "ms" << std::endl;
		fps = 0;
		m_clock.restart();
	}
	m_frameTime = m_frameClock.getElapsedTime();
	m_frameClock.restart();
}