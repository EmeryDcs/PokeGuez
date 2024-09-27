#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

class Perso
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rect;
	sf::Clock horlogeAnim;

public:
	Perso();
	Perso(sf::Texture texture, sf::Sprite sprite, sf::IntRect rect);
};

