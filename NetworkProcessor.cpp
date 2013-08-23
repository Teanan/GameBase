#include "NetworkProcessor.h"
#include "Application.h"

#include <iostream>

NetworkProcessor::NetworkProcessor()
{
	m_socket.setBlocking(false);
	m_state = Disconnected;
}

void NetworkProcessor::processNetworkEvents(){
	if (m_state == Disconnected) return;

	sf::Packet packet;
	sf::Uint32 state(m_socket.receive(packet));
	
	if (state == sf::Socket::Done && m_state == Connecting) m_state = Connected;
	if (state == sf::Socket::Done) incomingPacket(packet);
	if (state == sf::Socket::Error || state == sf::Socket::Disconnected) Application::instance()->getRenderWindow()->close();
}

void NetworkProcessor::incomingPacket(sf::Packet& packet){
	sf::Uint32 id;
	if (!(packet >> id)) return;

	if (m_state == Connected)
		if (m_serverHandles.count(id) > 0)
			(*(m_serverHandles[id]))(m_application, packet);
}

void NetworkProcessor::connectToServer(){
	m_state = Connecting;
	m_socket.disconnect();
	std::cout << "Server ip : " << m_serverConfig.first.toString() << std::endl;
	m_socket.setBlocking(true);
	m_socket.connect(m_serverConfig.first, m_serverConfig.second);
	m_socket.setBlocking(false);
}

void NetworkProcessor::setConfig(sf::IpAddress ipAddress, sf::Uint16 port){
	m_serverConfig.first = ipAddress;
	m_serverConfig.second = port;
}

void NetworkProcessor::registerHandle(sf::Uint32 id, fptr handle){
	m_serverHandles[id] = handle;
}

void NetworkProcessor::send(sf::Packet packet){
	m_socket.send(packet);
}

bool NetworkProcessor::isConnectedToServer(){
	return (m_state == Connected);
}