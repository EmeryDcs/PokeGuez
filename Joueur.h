#pragma once
#include <iostream>
#include <string>
#include "Pokemon.h"
#include "Inventaire.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class Joueur
{
	string nom;
	Pokemon tabPokemon[6];
	Inventaire inventaire;


public:
	Joueur();
	Joueur(string nom);
	Joueur(string nom, Pokemon tabPokemon[6], Inventaire inventaire);

	string getNom();
	void setNom(string nom);
	Pokemon getPokemon(int i);
	void setPokemon(int i, Pokemon pokemon);
	Inventaire getInventaire();
};

