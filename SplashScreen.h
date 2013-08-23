#ifndef SPLASHSCREEN_H_INCLUDED
#define SPLASHSCREEN_H_INCLUDED

#include "GameState.h"

class SplashScreen: public GameState
{
	public:

		SplashScreen(){
			m_test = sf::Text("splash screen", Application::instance()->getDefaultFont(), 30);
			m_test.setColor(sf::Color::White);
		};

		void init(){
			m_timer.restart();
		};

		void update(){
			if (m_timer.getElapsedTime() >= sf::seconds(1))
				Application::instance()->setCurrentGameState(MainMenuState);
		};

		void render(sf::RenderTarget* renderTarger){
			renderTarger->draw(m_test);
		};

	private:

		sf::Text m_test;
		sf::Clock m_timer;
};

#endif // SPLASHSCREEN_H_INCLUDED