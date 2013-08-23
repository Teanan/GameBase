#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <map>

#include "Singleton.h"
#include "GameState.h"

class GraphicsManager;
class UserEventsHandler;
class NetworkProcessor;

enum GameStateEnum{
	SplashScreenState = 1,
	LoadingScreenState,
	MainMenuState,
	InGameState
};

class Application: public Singleton<Application>
{

	public:

		void run();
		void loop(sf::Uint16 gameState);

		void setCurrentGameState(sf::Uint16 gameState);
		sf::Uint16 getCurrentGameState();

		GameState* getGameState(sf::Uint16 gameState);
		sf::Font& getDefaultFont();
		sf::RenderWindow* getRenderWindow();

		static GraphicsManager* graphicsManager();
		static UserEventsHandler* eventsHandler();
		static NetworkProcessor* networkProcessor();

	private:

		Application();

		GraphicsManager* m_graphicsManagers;
		UserEventsHandler* m_userEventsHandler;
		NetworkProcessor* m_networkProcessor;

		sf::RenderWindow* m_window;

		sf::Uint16 m_gameState;
		std::map<sf::Uint16, GameState*> m_gameStates;

		sf::Font m_defaultFont;

	friend class Singleton<Application>;

};

#endif // MAIN_H_INCLUDED