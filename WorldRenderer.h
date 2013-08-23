#ifndef WORLDRENDERER_H_INCLUDED
#define WORLDRENDERER_H_INCLUDED

#include <boost/shared_ptr.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Camera.h"

class DrawableMap;
typedef boost::shared_ptr<DrawableMap> DrawableMapPtr;

class WorldRenderer
{
	public:

		WorldRenderer();
		~WorldRenderer();
		
		void init();
		void unload();
		void update(sf::Time frameTime);
		void render(sf::RenderTarget* target);

		DrawableMapPtr getMap();

		Camera& getCamera();

	private:

		DrawableMapPtr m_map;
		Camera m_camera;
};

typedef boost::shared_ptr<WorldRenderer> WorldRendererPtr;

#endif // WORLDRENDERER_H_INCLUDED