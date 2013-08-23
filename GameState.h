#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <SFML/Graphics.hpp>

class GameState
{
	public:

		GameState();
		~GameState();

		virtual void init();
		virtual void unload();
		virtual void update();
		virtual void render(sf::RenderTarget* target);

	private:


};

#endif // GAMESTATE_H_INCLUDED