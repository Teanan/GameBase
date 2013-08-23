#ifndef INGAME_H_INCLUDED
#define INGAME_H_INCLUDED

#include <boost/shared_ptr.hpp>

#include "GameState.h"

class WorldRenderer;
typedef boost::shared_ptr<WorldRenderer> WorldRendererPtr;

class InGame: public GameState
{
	public:

		InGame();

		void init();
		void unload();
		void update();
		void render(sf::RenderTarget* target);

		WorldRendererPtr getRenderer();

		void checkInputs();

	private:

		WorldRendererPtr m_worldRenderer;
		
		sf::Clock m_clock;
		sf::Clock m_frameClock;
		sf::Time m_frameTime;
		sf::Uint32 fps;
};

#endif // INGAME_H_INCLUDED