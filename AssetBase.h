#ifndef ASSET_BASE_H_INCLUDED
#define ASSET_BASE_H_INCLUDED

#include <SFML/System.hpp>

#include <map>

#include "Properties.h"

class AssetBase: public Properties
{

	public:

		AssetBase(sf::Uint32 index): m_index(index)
		{
		};

		virtual void clear() = 0;

		sf::Uint32 getIndex(){
			return m_index;
		}

		std::string getName(){
			return m_name;
		}

		void setName(std::string n){
			m_name = n;
		}

	protected:

		sf::Uint32	m_index;
		std::string	m_name;

};

template <class ItemType>
class AssetsManagerBase
{

	public:

        ItemType* item(unsigned int index){
			if (m_items.count(index) == 0) return 0;
			return m_items[index];
		}

        bool exist(unsigned int num){
			if (item(num) != 0)
				if (item(num)->getName().length() > 0)
					return true;
			return false;
		};

	protected:

		std::map<sf::Uint32, ItemType*> m_items;

};

#endif // ASSET_BASE_H_INCLUDED
