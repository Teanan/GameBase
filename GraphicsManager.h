#ifndef GRAPHICSMANAGER_H_INCLUDED
#define GRAPHICSMANAGER_H_INCLUDED

#include <map>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <boost/shared_ptr.hpp>

class Graphic;
typedef boost::shared_ptr<Graphic> GraphicPtr;

typedef boost::shared_ptr<sf::Texture> TexturePtr;

class GraphicsManager: public sf::NonCopyable
{
	
	public:

		GraphicsManager();

		GraphicPtr get(sf::Uint32 id);
		TexturePtr getEmptyTexture();

		void loadGraphicsDB(std::string fileName);

	private:

		std::map<sf::Uint32, GraphicPtr> m_assets;
		
		TexturePtr m_emptyTexture;

};

#endif // GRAPHICASSETSMANAGER_H_INCLUDED
