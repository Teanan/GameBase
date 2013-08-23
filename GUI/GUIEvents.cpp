#include "GUIEvents.h"

GUIEvents::GUIEvents(){

}

void GUIEvents::pushEvent(sf::Event sfEvent){
	m_sfEvents.push_back(sfEvent);
}

void GUIEvents::processEvents(){
	m_events.clear();

    for (std::vector<sf::Event>::iterator it = m_sfEvents.begin(); it < m_sfEvents.end(); it++){
		sf::Event sfEvent(*it);
		
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
    }

	m_sfEvents.clear();
}

bool GUIEvents::isSfKeyDown(sf::Keyboard::Key key){
	if (m_gamePaused) return false;
	return sf::Keyboard::isKeyPressed(key);
}

bool GUIEvents::isEventThrown(Event e){
	if (m_events.count(e) == 0) return false;
	return m_events[e];
}

sf::Vector2f GUIEvents::getMousePosition(){
	return sf::Vector2f(m_mouseX, m_mouseY);
}

GUIEvents::BoutonState GUIEvents::getMouseBoutonState(sf::Mouse::Button button){
	if (m_mouseButtons.count(button) == 0) return StateReleased;
	return (m_mouseButtons[button]) ? StatePressed : StateReleased;
}

char GUIEvents::getTextEntered(){
	return m_textEntered;
}

sf::Keyboard::Key GUIEvents::getKeyCode(){
	return m_keyCode;
}

bool GUIEvents::getKeyAlt(){
	return m_keyAlt;
}

bool GUIEvents::getKeyControl(){
	return m_keyControl;
}

bool GUIEvents::getKeyShift(){
	return m_keyShift;
}

bool GUIEvents::getKeySystem(){
	return m_keySystem;
}