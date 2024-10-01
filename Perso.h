#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

class Perso
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rect;
	sf::Clock horloge;

public:
	Perso();
	Perso(sf::Texture& texture, sf::IntRect rect);

	sf::Sprite& getSprite();
};

