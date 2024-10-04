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

Joueur::Joueur(string nom, Pokemon starter, Inventaire inventaire, sf::Texture& texture, sf::IntRect rect)
	: Perso(texture, rect)
{
	this->nom = nom;
	tabPokemon[0] = starter;
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

Pokemon& Joueur::getPokemon(int i)
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

void Joueur::soin(int i)
{
	tabPokemon[i].soin();
	inventaire.utiliserPotion();
}

string Joueur::pokeball(Pokemon pokemon, sf::Texture texture)
{
	int random = rand() % 2;
	inventaire.utiliserPokeball();
	if (random == 1) {
		for (int i = 0; i < sizeof(tabPokemon)/sizeof(tabPokemon[0]) - 1; i++) {
			if (tabPokemon[i].getNom() == "Pokéball vide") {
				tabPokemon[i] = pokemon;
				tabPokemon[i].getSprite().setTexture(texture);
				return "Capture reussie";
			}
		}
		return "Capture réussie, mais vous êtes déjà complet en Pokémon.";
	}
	else {
		return "Capture echouee";
	}
}

void Joueur::loopPokemon() {
	for (int i = 0; i < 6; i++) {
		if (tabPokemon[i].getNom() != "") {
			tabPokemon[i].loop();
		}
	}
}