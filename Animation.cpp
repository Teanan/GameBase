#include "Animation.h"
#include "Application.h"
#include "../server/GameAssets/GraphicsManager.h"

Animation::Animation() : m_currentFrame(0), m_delayBetweenFrames(0), m_lastFrameUpdate(0), m_image(Application::graphicsManager()->getEmptyTexture())
{

}
Animation::Animation(TexturePtr texture) : m_currentFrame(0), m_delayBetweenFrames(0), m_lastFrameUpdate(0), m_image(texture)
{

}

Animation::~Animation(){

}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(m_sprite, states);
}

TexturePtr Animation::getImage() const{
	return m_image;
}
	
void Animation::setImage(TexturePtr image){
	m_image = image;
	init();
}

sf::Sprite Animation::getFrame() const{
	return m_sprite;
}
		
void Animation::setCurrentFrame(sf::Uint32 frame){
	m_currentFrame = frame;
}