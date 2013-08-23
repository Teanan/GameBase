#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

#include <boost/shared_ptr.hpp>

typedef std::vector<sf::IntRect> Frame;
typedef boost::shared_ptr<sf::Texture> TexturePtr;

class Animation: public sf::Drawable
{
	public:
		Animation();
		Animation(TexturePtr texture);
		~Animation();

		TexturePtr getImage() const;
		void setImage(TexturePtr image);

		sf::Sprite getFrame() const;
		void setCurrentFrame(sf::Uint32 frame);

	protected:
		virtual void init()=0;
		virtual void update()=0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
	protected:
		sf::Clock clock;

		sf::Uint32 m_frameSize;			// Taille d'une frame
		sf::Uint32 m_currentFrame;		// Frame actuelle
		sf::Uint32 m_delayBetweenFrames;// Delai entre deux frames
		sf::Uint32 m_lastFrameUpdate;	// Derniere mise a jour
		TexturePtr m_image;				// Image de l'animation
		sf::Sprite m_sprite;			// Frame affichee
};

#endif