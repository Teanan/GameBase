#ifndef DATASTREAM_H_INCLUDED
#define DATASTREAM_H_INCLUDED

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class DataStream: public sf::Packet
{
	public:

		// generic types

		template <typename T>
		T read(){
			T value;
			*this >> value;
			return value;
		};

		template <typename T>
		bool read(T& value){
			return (*this >> value);
		};
		
		template <typename T>
		bool write(T& value){
			return (*this << value);
		};

		// vectors

		template <typename T>
		sf::Vector2<T> readVec(){
			sf::Vector2<T> value;
			*this >> value.x;
			*this >> value.y;
			return value;
		};

		template <typename T>
		bool read(sf::Vector2<T>& value){
			return (*this >> value.x >> value.y);
		};
		
		template <typename T>
		bool write(sf::Vector2<T>& value){
			return (*this << value.x << value.y);
		};

	protected:

		DataStream(){
			
		};
};

#endif // DATASTREAM_H_INCLUDED