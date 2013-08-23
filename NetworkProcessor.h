#ifndef NETWORKEVENTS_H_INCLUDED
#define NETWORKEVENTS_H_INCLUDED

#include <SFML/Network.hpp>

class Application;

class NetworkProcessor
{
	public:

		enum NetworkState{
			Disconnected = 0,
			Connected,
			Connecting
		};

		typedef void (*fptr)(Application*, sf::Packet);

		NetworkProcessor();

		void processNetworkEvents();
		
		void registerHandle(sf::Uint32 id, fptr handle);

		void setConfig(sf::IpAddress ipAddress, sf::Uint16 port);

		void connectToServer();
		bool isConnectedToServer();
		
		void send(sf::Packet packet);

	private:

		void incomingPacket(sf::Packet& packet);

		sf::TcpSocket m_socket;
		sf::Uint32 m_state;
		Application* m_application;
		
		std::map<sf::Uint32, fptr> m_serverHandles;
		
		std::pair<sf::IpAddress, sf::Uint16> m_serverConfig;

};

#endif // NETWORKEVENTS_H_INCLUDED