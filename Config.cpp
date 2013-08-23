#include "Config.h"

Config* Config::m_instance;

Config::Config(std::string configFile): m_file(configFile)
{
	load();
}

Config::~Config(){

}

std::string Config::get(std::string key){
	if (m_configs.count(key) == 0) return "";
	return m_configs.at(key);
}

sf::Int32 Config::getInt32(std::string key, sf::Int32 defaultValue){
	if (m_configs.count(key) == 0) return defaultValue;
	return atoi(m_configs.at(key).c_str());
}

void Config::set(std::string key, std::string value, bool saveFile){
	m_configs[key] = value;
	if (saveFile) save();
}

void Config::load(){
	load(m_file);
}

void Config::save(){
	save(m_file);
}

void Config::load(std::string file){
	std::ifstream stream(file.c_str());
	YAML::Parser parser(stream);
	
	YAML::Node yamlDB;
	while(parser.GetNextDocument(yamlDB)){
		for(size_t t=0; t < yamlDB["config"].size(); t++){
			const YAML::Node &yamlConfig(yamlDB["config"][t]);

			std::string group;

			yamlConfig["group"] >> group;

			for(size_t c=0; c < yamlConfig["values"].size(); c++){
				const YAML::Node &yamlValues(yamlConfig["values"][c]);
            
				std::string name, value;
				yamlValues["name"] >> name;
				yamlValues["value"] >> value;

				set(group + "." + name, value, false);
			}
		}
	}
}

void Config::save(std::string file){

}

Config* Config::instance(){
	return m_instance;
}

Config* Config::initInstance(std::string configFile){
	m_instance = new Config(configFile);
	return m_instance;
}