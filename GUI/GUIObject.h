#ifndef GUIOBJECT_H_INCLUDED
#define GUIOBJECT_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GUICore.h"

class GUIObject: public sf::Drawable
{
	public:

		enum OriginBehaviour
		{
			DefaultOrigin = 1,
			CentredOrigin
		};

		GUIObject();
		GUIObject(sf::Vector2f position);
		GUIObject(sf::Vector2f position, sf::Vector2f size);

		virtual void update() = 0;

		// setters

		void setPosition(sf::Vector2f position);
		void setSize(sf::Vector2f size);
		void setOriginBehaviour(OriginBehaviour origin);

		// getters

		sf::Vector2f getPosition() const;
		sf::Vector2f getRealPosition() const;
		sf::Vector2f getSize() const;
		OriginBehaviour getOriginBehaviour() const;

		static OriginBehaviour originBehaviourFromString(std::string);

	protected:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	private:

		sf::Vector2f m_position;
		sf::Vector2f m_size;
		OriginBehaviour m_originBehaviour;

};

#endif // GUIOBJECT_H_INCLUDED