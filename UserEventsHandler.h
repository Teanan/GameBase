#ifndef INPUTSEVENTS_H_INCLUDED
#define INPUTSEVENTS_H_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

#include <boost/function.hpp>

class UserEventsHandler
{
	public:

		enum Key{
			Up = 1,
			Down,
			Left,
			Right,
			Attack
		};

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

		UserEventsHandler(sf::RenderWindow* renderWindow);

		void processEvents();

		void setEventsMirror(boost::function<void (sf::Event)> mirror);
		
		bool isSfKeyDown(sf::Keyboard::Key key);
		bool isKeyDown(Key key);
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
		
		bool m_gamePaused;
		std::map<Key, sf::Keyboard::Key> m_keysMap;
		std::map<Event, bool> m_events;
		sf::RenderWindow* m_renderWindow;

		boost::function<void (sf::Event)> m_eventsMirror;

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

#endif // INPUTSEVENTS_H_INCLUDED