#include "Joueur.h"
#include <iostream>
#include <string>
#include "Pokemon.h"
#include "Inventaire.h"
using namespace std;

Joueur::Joueur()
{
	nom = "Test";
}

Joueur::Joueur(string nom)
{
	this->nom = nom;
}

Joueur::Joueur(string nom, Pokemon tabPokemon[2], Inventaire inventaire, sf::Texture& texture, sf::IntRect rect)
	: Perso(texture, rect)
{
	this->nom = nom;
	for (int i = 0; i < 2; i++)
	{
		this->tabPokemon[i] = tabPokemon[i];
	}
	this->inventaire = inventaire;
}

string Joueur::getNom()
{
	return nom;
}

void Joueur::setNom(string nom)
{
	this->nom = nom;
}

Pokemon Joueur::getPokemon(int i)
{
	return tabPokemon[i];
}

void Joueur::setPokemon(int i, Pokemon pokemon)
{
	tabPokemon[i] = pokemon;
}

Inventaire Joueur::getInventaire()
{
	return inventaire;
}

void Joueur::loop() {
	if (horloge.getElapsedTime().asSeconds() > .05f) {
		rect.left += 32;
		if (rect.left >= 96)
			rect.left = 0;
		sprite.setTextureRect(rect);
		horloge.restart();
	}
}

void Joueur::deplacement(sf::Vector2f deplacement)
{
	if (deplacement.x < 0 && deplacement.y == 0)
		rect.top = 70;
	else if (deplacement.x > 0 && deplacement.y == 0)
		rect.top = 105;
	else if (deplacement.x == 0 && deplacement.y < 0)
		rect.top = 0;
	else if (deplacement.x == 0 && deplacement.y > 0)
		rect.top = 35;

	if (deplacement.x != 0 || deplacement.y != 0)
		loop();
	else
		rect.left = 0;

	sprite.setTextureRect(rect);
	sprite.move(deplacement);
}