#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <SFML/System.hpp>

int split(std::vector<std::string>& vecteur, std::string chaine, char separateur);
std::string randomKey(sf::Uint32 len);
std::string crypt(std::string text, std::string key);
std::string decrypt(std::string text, std::string key);

#endif // GENERAL_H_INCLUDED