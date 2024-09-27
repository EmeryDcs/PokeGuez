#pragma once
#include <iostream>
#include <string>	
using namespace std;

class Inventaire
{
	int nbPotion;
	int nbSpray;
	int nbPokeball;

public:
	Inventaire();
	Inventaire(int nbPotion, int nbSpray, int nbPokeball);

	int getNbPotion();
	void setNbPotion(int nbPotion);
	int getNbSpray();
	void setNbSpray(int nbSpray);
	int getNbPokeball();
	void setNbPokeball(int nbPokeball);

	void utiliserPotion();
	void utiliserSpray();
	void utiliserPokeball();

	void ajouterPotion();
	void ajouterSpray();
	void ajouterPokeball();
};

