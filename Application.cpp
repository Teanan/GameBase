#include "Application.h"
#include "NetworkProcessor.h"
#include "UserEventsHandler.h"

#include "SplashScreen.h"
#include "MainMenu.h"
#include "InGame.h"

#include "GraphicsManager.h"

#include "GUI/GUICore.h"

#include "Config.h"

#include "handles.h"

#include <boost/bind.hpp>

Application::Application(){
	Config::initInstance("config.yaml");

	m_graphicsManagers = new GraphicsManager;
	m_networkProcessor = new NetworkProcessor;

	m_defaultFont.loadFromFile("data/arial.ttf");

	bool fullscreen = (Config::instance()->getInt32("graphic.fullscreen") == 1);
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game", fullscreen ? sf::Style::Fullscreen : sf::Style::Close | sf::Style::Titlebar);

	m_userEventsHandler = new UserEventsHandler(m_window);
	m_userEventsHandler->setEventsMirror(boost::bind(&GUIEvents::pushEvent, GUICore::events(), _1));

	//m_networkProcessor->setServerConfig(sf::IpAddress(Config::instance()->get("server.ip")), Config::instance()->getInt32("server.port"));
	//m_networkProcessor->registerHandle(SDemo, &handleDemo);
}

void Application::run(){ 
	m_window->setFramerateLimit(60);

	sf::Uint16 currentState(0);

	m_gameStates[SplashScreenState] = new SplashScreen;
	m_gameStates[MainMenuState] = new MainMenu;
	m_gameStates[InGameState] = new InGame;

	setCurrentGameState(SplashScreenState);

    while (m_window->isOpen()){
		if (m_gameState != currentState){
			if (m_gameStates.count(currentState) != 0) m_gameStates[currentState]->unload();
			if (m_gameStates.count(m_gameState) != 0) m_gameStates[m_gameState]->init();
			currentState = m_gameState;
		}

        loop(m_gameState);
    }
}

void Application::loop(sf::Uint16 gameState){
	assert(m_gameStates.count(gameState) != 0 && "Invalid gameState");

	m_window->clear();

	m_userEventsHandler->processEvents();
	GUICore::events()->processEvents();

	m_networkProcessor->processNetworkEvents();

	m_gameStates[gameState]->update();
	m_gameStates[gameState]->render(m_window);

	m_window->display();
}

void Application::setCurrentGameState(sf::Uint16 gameState){
	m_gameState = gameState;
}

sf::Uint16 Application::getCurrentGameState(){
	return m_gameState;
}

sf::Font& Application::getDefaultFont(){
	return m_defaultFont;
}

GameState* Application::getGameState(sf::Uint16 gameState){
	assert(m_gameStates.count(gameState) != 0 && "Invalid gameState");
	return m_gameStates[gameState];
}

sf::RenderWindow* Application::getRenderWindow(){
	return m_window;
}

GraphicsManager* Application::graphicsManager(){
	return instance()->m_graphicsManagers;
}

UserEventsHandler* Application::eventsHandler(){
	return instance()->m_userEventsHandler;
}

NetworkProcessor* Application::networkProcessor(){
	return instance()->m_networkProcessor;
}