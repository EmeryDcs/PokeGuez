#include "Pokemon.h"

Pokemon::Pokemon()
{
	nom = "";
	type = "";
	pv = 0;
	attaque = 0;
	vitesse = 0;
	etat = 0;
}

Pokemon::Pokemon(string nom, string type, int pv, int attaque, int vitesse, Competence competence[4], int etat)
{
	this->nom = nom;
	this->type = type;
	this->pv = pv;
	this->attaque = attaque;
	this->vitesse = vitesse;
	for (int i = 0; i < 4; i++)
	{
		this->competence[i] = competence[i];
	}
	this->etat = etat;
}

string Pokemon::getNom()
{
	return nom;
}

void Pokemon::setNom(string nom)
{
	this->nom = nom;
}

string Pokemon::getType()
{
	return type;
}

void Pokemon::setType(string type)
{
	this->type = type;
}

int Pokemon::getPv()
{
	return pv;
}

void Pokemon::setPv(int pv)
{
	this->pv = pv;
}

int Pokemon::getAttaque()
{
	return attaque;
}

void Pokemon::setAttaque(int attaque)
{
	this->attaque = attaque;
}

int Pokemon::getVitesse()
{
	return vitesse;
}

void Pokemon::setVitesse(int vitesse)
{
	this->vitesse = vitesse;
}

Competence Pokemon::getCompetence(int i)
{
	return competence[i];
}

void Pokemon::setCompetence(int i, Competence competence)
{
	this->competence[i] = competence;
}

int Pokemon::getEtat()
{
	return etat;
}

void Pokemon::setEtat(int etat)
{
	this->etat = etat;
}

void Pokemon::attaquer(Pokemon& cible, Competence competence)
{
	//À modifier
	//cible.setPv(cible.getPv() - competence.getPuissance());
}