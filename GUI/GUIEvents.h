#ifndef GUIEVENTS_H_INCLUDED
#define GUIEVENTS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <map>

class GUIEvents{
	
	public:

		GUIEvents();

		enum Event{
			LostFocus = 1,
			GainedFocus,
			MouseWheelMoved,
			MouseButtonPressed,
			MouseButtonReleased,
			MouseButtonClicked,
			MouseMoved,
			MouseEntered,
			MouseLeft,
			TextEntered,
			SfKeyPressed,
			SfKeyReleased,
		};

		enum BoutonState{
			StatePressed = 1,
			StateReleased
		};

		void processEvents();

		void pushEvent(sf::Event sfEvent);

		bool isSfKeyDown(sf::Keyboard::Key key);
		bool isEventThrown(Event e);

		sf::Vector2f getMousePosition();
		BoutonState getMouseBoutonState(sf::Mouse::Button);

		char getTextEntered();

		sf::Keyboard::Key getKeyCode();
		bool getKeyAlt();
		bool getKeyControl();
		bool getKeyShift();
		bool getKeySystem();

	private:

		std::vector<sf::Event> m_sfEvents;
		
		bool m_gamePaused;
		std::map<Event, bool> m_events;
		sf::RenderWindow* m_renderWindow;

		int m_mouseX;
		int m_mouseY;
		int m_mouseWheelDelta;
		std::map<sf::Mouse::Button, bool> m_mouseButtons;
		sf::Mouse::Button m_lastMouseButtonPressed;
		sf::Mouse::Button m_lastMouseButtonReleased;
		sf::Mouse::Button m_lastMouseButtonClicked;

		char m_textEntered;

        sf::Keyboard::Key m_keyCode;
        bool m_keyAlt;
        bool m_keyControl;
        bool m_keyShift;
        bool m_keySystem;
};

#endif // GUIEVENTS_H_INCLUDED