#include "Joueur.h"
#include <iostream>
#include <string>
#include "Pokemon.h"
#include "Inventaire.h"
using namespace std;

Joueur::Joueur()
{
	nom = "Sacha";
}

Joueur::Joueur(string nom)
{
	this->nom = nom;
}

Joueur::Joueur(string nom, Pokemon tabPokemon[6], Inventaire inventaire)
{
	this->nom = nom;
	for (int i = 0; i < 6; i++)
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