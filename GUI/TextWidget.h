#ifndef TEXTWIDGET_H_INCLUDED
#define TEXTWIDGET_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <boost/shared_ptr.hpp>

#include "Widget.h"

typedef boost::shared_ptr<sf::Texture> TexturePtr;

class TextWidget: public Widget
{
	public:

		enum TextAlignment
		{
			CentrallyAligned = 1,
			LeftAligned,
			RightAligned
		};

		// constructors

		TextWidget();
		TextWidget(sf::Vector2f position, sf::Vector2f size);
		TextWidget(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color);
		TextWidget(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Uint32 textSize, sf::Color color, sf::Font& font);
		
		virtual void update() = 0;

		// setters

		void setText(std::string);
		void setTextSize(sf::Uint32);
		void setTextColor(sf::Color);
		void setFont(sf::Font&);
		void setTextAlignment(TextAlignment);

		// overide Widget's setters
		
		void setPosition(sf::Vector2f position);
		void setSize(sf::Vector2f size);
		void setOriginBehaviour(Widget::OriginBehaviour origin);

		// getters

		std::string getText();
		sf::Uint32 getTextSize();
		sf::Color getTextColor();
		sf::Font& getFont();
		TextAlignment getTextAlignment();

		static TextAlignment textAlignmentFromString(std::string);

	protected:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		virtual void textUpdated();

		void updateDrawableTextPosition();

		std::string m_text;
		sf::Uint32 m_textSize;
		sf::Color m_textColor;
		sf::Font& m_font;
		TextAlignment m_alignment;

		sf::Text m_drawableText;

};

#endif // TEXTWIDGET_H_INCLUDED