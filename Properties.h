#ifndef PROPERTIES_H_INCLUDED
#define PROPERTIES_H_INCLUDED

#include <string>
#include <sstream>
#include <map>

#include <SFML/Network.hpp>

#include "Split.h"

class Properties
{
	public:

		Properties(){};
		~Properties(){};

		// Get & Set properties

		template <class T>
		void setProperty(std::string key, T value){
			std::ostringstream stream;
			stream << value;
			m_properties[key] = stream.str();
		};

		template <class T>
		T getProperty(std::string key){
			if (m_properties.count(key) == 0) return T();

			std::stringstream stream;
			T value;

			stream.str(m_properties[key]);
			stream >> value;

			return value;
		};

		template <class T>
		T getProperty(std::string prefix, std::string key){
			return getProperty<T>(prefix + "." + key);
		};

		template <class T>
		T getProperty(std::string prefix, sf::Uint32 prefixId, std::string key){
			std::ostringstream stream;
			stream << prefixId;
			return getProperty<T>(prefix + "." + stream.str() + "." + key);
		};

		sf::Uint32 getPropertiesCount() const{
			return m_properties.size();
		};

		// Read/Write to packet
		
		template <class T>
		bool readPropertyValue(std::string key, sf::Packet& packet){
			T value;
			if (packet >> value){
				setProperty<T>(key, value);
				return true;
			}
			return false;
		};
		
		template <class T>
		void writePropertyValue(std::string key, sf::Packet& packet){
			packet << getProperty<T>(key);
		};

		void writeProperties(sf::Packet& packet){
			packet << getPropertiesCount();

			for (Properties::const_properties_iterator it = propertiesBegin(); it != propertiesEnd(); it++){
				packet << it->first;
				packet << it->second;
			}
		};

		void readProperties(sf::Packet& packet){
			sf::Uint32 count;
			packet >> count;

			for (sf::Uint32 i(0); i < count; i++){
				std::string key, value;
				packet >> key >> value;
				setProperty(key, value);
			}
		};

		// iterators

		typedef std::map<std::string, std::string>::const_iterator const_properties_iterator;
		const_properties_iterator propertiesBegin() const{ return m_properties.begin(); };
		const_properties_iterator propertiesEnd() const{ return m_properties.end(); };

		/////////////////////////////////
		// Properties writing helpers ---
		/////////////////////////////////

		// Writing to sf::Packet

		template <class T>
		static void write(sf::Packet& packet, std::string key, T value){
			write(packet, "", key, value);
		};

		template <class T>
		static void write(sf::Packet& packet, std::string prefix, std::string key, T value){
			std::ostringstream stream;
			stream << value;

			packet << (prefix == "") ? key : prefix + "." + key;
			packet << stream.str();
		};

		template <class T>
		static void write(sf::Packet& packet, std::string prefix, sf::Uint32 prefixId, std::string key, T value){
			std::ostringstream stream;
			stream << prefixId;

			write(packet, prefix + "." + stream.str(), key, value);
		};

		// Writing to Properties object

		template <class T>
		static void write(Properties& properties, std::string key, T value){
			write(properties, "", key, value);
		};

		template <class T>
		static void write(Properties& properties, std::string prefix, std::string key, T value){
			properties.setProperty((prefix == "") ? key : prefix + "." + key, value);
		};

		template <class T>
		static void write(Properties& properties, std::string prefix, sf::Uint32 prefixId, std::string key, T value){
			std::ostringstream stream;
			stream << prefixId;

			write(properties, prefix + "." + stream.str(), key, value);
		};

		// Importing a Properties object to an other

		static void write(Properties& properties, std::string key, Properties& value){
			write(properties, "", key, value);
		};
		
		static void write(Properties& properties, std::string prefix, std::string key, Properties& value){
			for (Properties::const_properties_iterator it = value.propertiesBegin(); it != value.propertiesEnd(); it++){
				properties.write(properties, prefix + "." + key, it->first, it->second); 
			}
		};

		static void write(Properties& properties, std::string prefix, sf::Uint32 prefixId, std::string key, Properties& value){
			std::ostringstream stream;
			stream << prefixId;

			write(properties, prefix + "." + stream.str(), key, value);
		};

		// Make key string with prefix and/or prefixId

		static std::string makeKey(std::string prefix, std::string key){
			return prefix + "." + key;
		};

		static std::string makeKey(std::string prefix, sf::Uint32 prefixId, std::string key){
			std::ostringstream stream;
			stream << prefixId;

			return prefix + "." + stream.str() + "." + key;
		};

		static std::string makeKey(std::string prefix, sf::Uint32 prefixId){
			std::ostringstream stream;
			stream << prefixId;

			return prefix + "." + stream.str();
		};

		static std::string makeKey(sf::Uint32 prefixId, std::string key){
			std::ostringstream stream;
			stream << prefixId;

			return stream.str() + "." + key;
		};

		/////////////////////////////////
		// --- Properties writing helpers
		/////////////////////////////////

	private:

		std::map<std::string, std::string> m_properties;
};

// Specifics template resolutions

template <>
inline std::string Properties::getProperty(std::string key){
	if (m_properties.count(key) == 0) return std::string();

	return m_properties[key];
};

template <>
inline void Properties::write(sf::Packet& packet, std::string prefix, std::string key, std::string value){
	packet << (prefix == "") ? key : prefix + "." + key;
	packet << value;
};

#endif // PROPERTIES_H_INCLUDED