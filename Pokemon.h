#pragma once
#include <iostream>
#include <string>
#include "Competence.h"
using namespace std;

class Pokemon
{
	string nom;
	string type;
	int pv;
	int attaque;
	int vitesse;
	Competence competence[4];
	int etat;

public:
	Pokemon();
	Pokemon(string nom, string type, int pv, int attaque, int vitesse, Competence competence[4], int etat);

	string getNom();
	void setNom(string nom);
	string getType();
	void setType(string type);
	int getPv();
	void setPv(int pv);
	int getAttaque();
	void setAttaque(int attaque);
	int getVitesse();
	void setVitesse(int vitesse);
	Competence getCompetence(int i);
	void setCompetence(int i, Competence competence);
	int getEtat();
	void setEtat(int etat);

	void attaquer(Pokemon& cible, Competence competence);
	
};

