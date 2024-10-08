#include "Pokemon.h"
#include "Perso.h"

Pokemon::Pokemon()
{
	nom = "Pokéball vide";
	type = "";
	pv = 0;
	pvMax = 0;
	attaque = 0;
	vitesse = 0;
	etat = 0;
}

Pokemon::Pokemon(string nom, string type, int pv, int attaque, int vitesse, Competence competence[4], int etat, sf::Texture& texture, sf::IntRect rect)
	: Perso(texture, rect)
{
	this->nom = nom;
	this->type = type;
	this->pv = pv;
	this->pvMax = pv;
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

string Pokemon::getNomEtat()
{
	switch (etat) {
	case 0:
		return "Normal";
		break;
	case 1:
		return "Paralyse";
		break;
	case 2:
		return "Brule";
		break;
	}
}

int Pokemon::getPvMax()
{
	return pvMax;
}

void Pokemon::loop() {
	if (horloge.getElapsedTime().asSeconds() > .1f) {
		rect.left += 100;
		if (rect.left >= 2000)
			rect.left = 0;
		sprite.setTextureRect(rect);
		horloge.restart();
	}
}

void Pokemon::attaquer(Pokemon& cible, Competence competence)
{
	float avantageElementaire = coeffAvantage(cible);
	int pvPerdus = 0;

	if (competence.getMultiplicateur() != 0) {
		pvPerdus = ((((20 * 0.4 + 2) * attaque * competence.getMultiplicateur() / 100) / 50) + 2) * avantageElementaire;
	}
	cout << "PV Perdus : " << pvPerdus << endl;
	cible.setPv(cible.getPv() - pvPerdus);

	buffEtDebuff(cible, competence);
}

void Pokemon::buffEtDebuff(Pokemon& cible, Competence competence) {
	int random = rand() % 100;

	//Debuff Ennemis
	if ((competence.getDebuff() == "Paralysie" || competence.getDebuff() == "Peur") && random > 70) {
		cible.setEtat(1);
	}
	else if (competence.getDebuff() == "Brulure" && random > 70) {
		cible.setEtat(2);
	}
	else if (competence.getDebuff() == "Baisse Attaque" && random > 70) {
		cible.setAttaque(cible.getAttaque() - 30);
	}
	else if (competence.getDebuff() == "Baisse Vitesse" && random > 70) {
		cible.setVitesse(cible.getVitesse() - 30);
	}

	//Buff Alliés
	if (competence.getBuff() == "Buff tout") {
		setAttaque(getAttaque() + 20);
		setVitesse(getVitesse() + 30);
	}
	else if (competence.getBuff() == "Vitesse max") {
		setVitesse(getVitesse() + 100);
	}
	else if (competence.getBuff() == "Augmentation Attaque") {
		setAttaque(getAttaque() + 30);
	}
	else if (competence.getBuff() == "Se blesse") {
		setPv(getPv() - 10);
	}
}

float Pokemon::coeffAvantage(Pokemon cible)
{
	if (type == "Feu" && cible.getType() == "Glace") {
		return 2;
	}
	else if (type == "Glace" && cible.getType() == "Plante") {
		return 2;
	}
	else if (type == "Plante" && cible.getType() == "Electrik") {
		return 2;
	}
	else if (type == "Electrik" && cible.getType() == "Vol") {
		return 2;
	}
	else if (type == "Vol" && cible.getType() == "Dragon") {
		return 2;
	}
	else if (type == "Dragon" && cible.getType() == "Feu") {
		return 2;
	}
	else 
		return 1;
}

void Pokemon::soin()
{
	pv += 10;
}