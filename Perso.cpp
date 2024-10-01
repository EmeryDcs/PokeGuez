#include "Perso.h"

Perso::Perso()
{
	horloge.restart();
}

Perso::Perso(sf::Texture& texture, sf::IntRect rect)
{
	this->texture = texture;
	this->rect = rect;
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.setPosition(0, 0);
	horloge.restart();
}

sf::Sprite& Perso::getSprite()
{
	return sprite;
}