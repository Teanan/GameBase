#include "general.h"

int split(std::vector<std::string>& vecteur, std::string chaine, char separateur){
	vecteur.clear();

	std::string::size_type stTemp = chaine.find(separateur);
	
	while(stTemp != std::string::npos){
		vecteur.push_back(chaine.substr(0, stTemp));
		chaine = chaine.substr(stTemp + 1);
		stTemp = chaine.find(separateur);
	}
	
	vecteur.push_back(chaine);

	return vecteur.size();
};

std::string randomKey(sf::Uint32 len){
	const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string key;

	for (sf::Uint32 i(0); i < len; ++i){
		key += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return key;
};

std::string crypt(std::string text, std::string key){
	sf::Uint32 keyPose(0);
	std::string result;

	for (sf::Uint32 i(0); i < text.length(); i++){
		result += text.at(i);
		result[i] = ~result[i];
		result[i] ^= key[keyPose];
		if (keyPose == key.length()) keyPose = 0;
	}

	return result;
};

std::string decrypt(std::string text, std::string key){
	return crypt(text, key);
};