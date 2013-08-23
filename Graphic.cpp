#include "Graphic.h"

Graphic::Graphic(){

}

void Graphic::setId(sf::Uint32 id){
	m_id = id;	
}

void Graphic::setPath(std::string path){
	m_path = path;	
}

sf::Uint32 Graphic::getId() const{
	return m_id;
}

std::string Graphic::getPath() const{
	return m_path;
}

TexturePtr Graphic::getTexture(){
	if (m_texture.get() == 0){
		m_texture = TexturePtr(new sf::Texture);
		m_texture->loadFromFile("graphics/" + m_path);
		m_texture->setSmooth(false);
	}

	return m_texture;
}
		
void Graphic::load(DataStream& stream){
	stream >> m_id;
	stream >> m_path;
}

void Graphic::save(DataStream& stream){
	stream << m_id;
	stream << m_path;
}