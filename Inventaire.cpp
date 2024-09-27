#include "Inventaire.h"
#include <iostream>
#include <string>
using namespace std;

Inventaire::Inventaire()
{
	nbPotion = 0;
	nbSpray = 0;
	nbPokeball = 0;
}

Inventaire::Inventaire(int nbPotion, int nbSpray, int nbPokeball)
{
	this->nbPotion = nbPotion;
	this->nbSpray = nbSpray;
	this->nbPokeball = nbPokeball;
}

int Inventaire::getNbPotion()
{
	return nbPotion;
}

void Inventaire::setNbPotion(int nbPotion)
{
	this->nbPotion = nbPotion;
}

int Inventaire::getNbSpray()
{
	return nbSpray;
}

void Inventaire::setNbSpray(int nbSpray)
{
	this->nbSpray = nbSpray;
}

int Inventaire::getNbPokeball()
{
	return nbPokeball;
}

void Inventaire::setNbPokeball(int nbPokeball)
{
	this->nbPokeball = nbPokeball;
}

void Inventaire::utiliserPotion()
{
	nbPotion--;
}

void Inventaire::utiliserSpray()
{
	nbSpray--;
}

void Inventaire::utiliserPokeball()
{
	nbPokeball--;
}

void Inventaire::ajouterPotion()
{
	nbPotion++;
}

void Inventaire::ajouterSpray()
{
	nbSpray++;
}

void Inventaire::ajouterPokeball()
{
	nbPokeball++;
}

