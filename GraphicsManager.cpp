#include "GraphicsManager.h"
#include "Graphic.h"

#include "FileDataStream.h"

GraphicsManager::GraphicsManager(){
	loadGraphicsDB("graphics.db");
}

GraphicPtr GraphicsManager::get(sf::Uint32 id){
	return m_assets[id];
}

TexturePtr GraphicsManager::getEmptyTexture(){
	return m_emptyTexture;
}

void GraphicsManager::loadGraphicsDB(std::string fileName){
	FileDataStream stream(fileName, FileDataStream::Read);

	sf::Uint32 count(stream.read<sf::Uint32>());

	for (sf::Uint32 i(0); i < count; i++){
		GraphicPtr asset(new Graphic);
		asset->load(stream);
		m_assets[asset->getId()] = asset;
	}
}