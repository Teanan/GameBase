#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <boost/shared_ptr.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>

#include "DataStream.h"

typedef boost::shared_ptr<sf::Texture> TexturePtr;

class Graphic
{
	public:

		Graphic();

		void setId(sf::Uint32 id);
		void setPath(std::string path);

		sf::Uint32 getId() const;
		std::string getPath() const;

		TexturePtr getTexture();

		void load(DataStream&);
		void save(DataStream&);

	private:

		std::string m_path;
		sf::Uint32 m_id;

		TexturePtr m_texture;
};

typedef boost::shared_ptr<Graphic> GraphicPtr;

#endif // GRAPHICSASSET_H_INCLUDED
