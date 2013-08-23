#include "GUICore.h"
#include "GUILayer.h"

GUICore* GUICore::m_instance;

GUICore::GUICore(){
	m_defaultFont.loadFromFile("data/arial.ttf");
	m_events = new GUIEvents;
	m_mainLayer = new GUILayer;
}

TexturePtr GUICore::getEmptyTexture(){
	if (m_instance == 0) m_instance = new GUICore;
	if (m_instance->m_emptyTexture.get() == 0) m_instance->m_emptyTexture = TexturePtr(new sf::Texture);
	return m_instance->m_emptyTexture;
}

sf::Font& GUICore::getDefaultFont(){
	if (m_instance == 0) m_instance = new GUICore;
	return m_instance->m_defaultFont;
}

GUIEvents* GUICore::events(){
	if (m_instance == 0) m_instance = new GUICore;
	return m_instance->m_events;
}

GUILayer* GUICore::getMainLayer(){
	if (m_instance == 0) m_instance = new GUICore;
	return m_instance->m_mainLayer;
}