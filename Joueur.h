#pragma once
#include <iostream>
#include <string>
#include "Pokemon.h"
#include "Inventaire.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Perso.h"

using namespace std;

class Joueur :
	public Perso
{
	string nom;
	Pokemon tabPokemon[6];
	Inventaire inventaire;

public:
	Joueur();
	Joueur(string nom);
	Joueur(string nom, Pokemon starter, Inventaire inventaire, sf::Texture& texture, sf::IntRect rect);

	string getNom();
	void setNom(string nom);
	Pokemon& getPokemon(int i);
	void setPokemon(int i, Pokemon pokemon);
	Inventaire getInventaire();
	void deplacement(sf::Vector2f);
	void loop();
	void soin(int i);
	string pokeball(Pokemon pokemon, sf::Texture& texture);
	void loopPokemon();
	void danse();
};

