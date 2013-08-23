#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <string>
#include <map>
#include <fstream>

#include <SFML/System.hpp>

#include "../libs/yaml-cpp/include/yaml-cpp/yaml.h"

class Config
{

	public:

		~Config();

		static Config* instance();
		static Config* initInstance(std::string configFile);

		std::string get(std::string key);
		sf::Int32 getInt32(std::string key, sf::Int32 defaultValue = 0);
		void set(std::string key, std::string value, bool save = true);
		
		void load();
		void load(std::string configFile);
		void save();
		void save(std::string configFile);

	private:

		Config(std::string configFile);

		std::string m_file;
		std::map<std::string, std::string> m_configs;

		static Config* m_instance;

};

#endif // CONFIG_H_INCLUDED