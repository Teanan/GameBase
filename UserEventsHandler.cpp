#include "UserEventsHandler.h"

UserEventsHandler::UserEventsHandler(sf::RenderWindow* renderWindow): m_renderWindow(renderWindow), m_gamePaused(false)
{
	m_keysMap[Up] = sf::Keyboard::Z;
	m_keysMap[Down] = sf::Keyboard::S;
	m_keysMap[Left] = sf::Keyboard::Q;
	m_keysMap[Right] = sf::Keyboard::D;
	m_keysMap[Attack] = sf::Keyboard::LControl;
}

void UserEventsHandler::processEvents(){
	m_events.clear();

    sf::Event sfEvent;
    while (m_renderWindow->pollEvent(sfEvent)){
        if (sfEvent.type == sf::Event::Closed){
            m_renderWindow->close();
			break;
		}

		if (sfEvent.type == sf::Event::LostFocus){
			m_events[LostFocus] = true;
			m_gamePaused = true;
		}

		if (sfEvent.type == sf::Event::GainedFocus){
			m_events[GainedFocus] = true;
			m_gamePaused = false;
		}

		if (sfEvent.type == sf::Event::MouseWheelMoved){
			m_events[MouseWheelMoved] = true;
			m_mouseX = sfEvent.mouseWheel.x;
			m_mouseY = sfEvent.mouseWheel.y;
			m_mouseWheelDelta = sfEvent.mouseWheel.delta;
		}

		if (sfEvent.type == sf::Event::MouseButtonPressed){
			m_events[MouseButtonPressed] = true;
			m_mouseX = sfEvent.mouseButton.x;
			m_mouseY = sfEvent.mouseButton.y;
			m_lastMouseButtonPressed = sfEvent.mouseButton.button;
			m_mouseButtons[sfEvent.mouseButton.button] = true;
		}

		if (sfEvent.type == sf::Event::MouseButtonReleased){
			m_events[MouseButtonReleased] = true;
			m_mouseX = sfEvent.mouseButton.x;
			m_mouseY = sfEvent.mouseButton.y;
			m_lastMouseButtonReleased = sfEvent.mouseButton.button;

			if (m_lastMouseButtonPressed == sfEvent.mouseButton.button && m_mouseButtons[sfEvent.mouseButton.button] == true){
				m_events[MouseButtonClicked] = true;
				m_lastMouseButtonClicked = sfEvent.mouseButton.button;
			}

			m_mouseButtons[sfEvent.mouseButton.button] = false;

		}

		if (sfEvent.type == sf::Event::MouseMoved){
			m_events[MouseMoved] = true;
			m_mouseX = sfEvent.mouseMove.x;
			m_mouseY = sfEvent.mouseMove.y;
		}

		if (sfEvent.type == sf::Event::MouseEntered){
			m_events[MouseEntered] = true;
		}

		if (sfEvent.type == sf::Event::MouseLeft){
			m_events[MouseLeft] = true;
		}

		if (sfEvent.type == sf::Event::TextEntered){
			m_events[TextEntered] = true;
			m_textEntered = sfEvent.text.unicode;
		}

		if (sfEvent.type == sf::Event::KeyPressed){
			m_events[SfKeyPressed] = true;
			m_keyCode = sfEvent.key.code;
			m_keyAlt = sfEvent.key.alt;
			m_keyControl = sfEvent.key.control;
			m_keyShift = sfEvent.key.shift;
			m_keySystem = sfEvent.key.system;
		}

		if (sfEvent.type == sf::Event::KeyReleased){
			m_events[SfKeyReleased] = true;
			m_keyCode = sfEvent.key.code;
			m_keyAlt = sfEvent.key.alt;
			m_keyControl = sfEvent.key.control;
			m_keyShift = sfEvent.key.shift;
			m_keySystem = sfEvent.key.system;
		}

		if (!m_eventsMirror.empty())
			m_eventsMirror(sfEvent);
    }
}

void UserEventsHandler::setEventsMirror(boost::function<void (sf::Event)> mirror){
	m_eventsMirror = mirror;
}

bool UserEventsHandler::isSfKeyDown(sf::Keyboard::Key key){
	if (m_gamePaused) return false;
	return sf::Keyboard::isKeyPressed(key);
}

bool UserEventsHandler::isKeyDown(Key key){
	if (m_gamePaused) return false;
	if (m_keysMap.count(key) == 0) return false;
	return sf::Keyboard::isKeyPressed(m_keysMap.at(key));
}

bool UserEventsHandler::isEventThrown(Event e){
	if (m_events.count(e) == 0) return false;
	return m_events[e];
}

sf::Vector2f UserEventsHandler::getMousePosition(){
	return sf::Vector2f(m_mouseX, m_mouseY);
}

UserEventsHandler::BoutonState UserEventsHandler::getMouseBoutonState(sf::Mouse::Button button){
	if (m_mouseButtons.count(button) == 0) return StateReleased;
	return (m_mouseButtons[button]) ? StatePressed : StateReleased;
}

char UserEventsHandler::getTextEntered(){
	return m_textEntered;
}

sf::Keyboard::Key UserEventsHandler::getKeyCode(){
	return m_keyCode;
}

bool UserEventsHandler::getKeyAlt(){
	return m_keyAlt;
}

bool UserEventsHandler::getKeyControl(){
	return m_keyControl;
}

bool UserEventsHandler::getKeyShift(){
	return m_keyShift;
}

bool UserEventsHandler::getKeySystem(){
	return m_keySystem;
}