#ifndef GUICORE_H_INCLUDED
#define GUICORE_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <boost/shared_ptr.hpp>

#include "GUIEvents.h"

class GUILayer;

typedef boost::shared_ptr<sf::Texture> TexturePtr;

class GUICore
{
	public:

		static TexturePtr getEmptyTexture();
		static sf::Font& getDefaultFont();
		static GUIEvents* events();
		static GUILayer* getMainLayer();

	private:

		GUICore();

		TexturePtr m_emptyTexture;
		sf::Font m_defaultFont;
		GUIEvents* m_events;
		GUILayer* m_mainLayer;

		static GUICore* m_instance;
};

#endif // GUICORE_H_INCLUDED