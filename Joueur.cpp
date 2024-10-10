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

string Joueur::pokeball(Pokemon pokemon, sf::Texture& texture)
{
	float coeff = (1.f - (pokemon.getPv() * 1.0) / (pokemon.getPvMax() * 1.0)) + (1 - 1/(pokemon.getEtat()+1)) ;
	inventaire.utiliserPokeball();
	if (coeff >= 0.75) {
		for (int i = 0; i < sizeof(tabPokemon)/sizeof(tabPokemon[0]) - 1; i++) {
			if (tabPokemon[i].getNom() == "Pokéball vide") {
				Competence tabCompetence[4] = { pokemon.getCompetence(0), pokemon.getCompetence(1), pokemon.getCompetence(2), pokemon.getCompetence(3) };
				tabPokemon[i] = Pokemon(
					pokemon.getNom(), 
					pokemon.getType(), 
					pokemon.getPvMax(), 
					pokemon.getAttaqueMax(), 
					pokemon.getVitesseMax(), 
					tabCompetence,
					0, 
					texture, 
					pokemon.getRect()
				);
				tabPokemon[i].getSprite().setPosition(tabPokemon[0].getSprite().getPosition());
				tabPokemon[i].getSprite().setScale(tabPokemon[0].getSprite().getScale());
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

void Joueur::danse() {
	rect.top = 0;
	if (horloge.getElapsedTime().asSeconds() > .5f) {
		rect.left += 32;
		cout << rect.left << endl;
		if (rect.left >= 256)
			rect.left = 0;
		sprite.setTextureRect(rect);
		horloge.restart();
	}
}