#include "Competence.h"
#include <string>
using namespace std;

Competence::Competence()
{
	nom = "";
	multiplicateur = 1;
	effet = "";
	buff = "";
	debuff = "";
}

Competence::Competence(string nom)
{
	this->nom = nom;
	multiplicateur = 1;
	effet = "";
	buff = "";
	debuff = "";
}

Competence::Competence(string nom, int multiplicateur, string effet, string buff, string debuff)
{
	this->nom = nom;
	this->multiplicateur = multiplicateur;
	this->effet = effet;
	this->buff = buff;
	this->debuff = debuff;
}

string Competence::getNom()
{
	return nom;
}

void Competence::setNom(string nom)
{
	this->nom = nom;
}

int Competence::getMultiplicateur()
{
	return multiplicateur;
}

void Competence::setMultiplicateur(int multiplicateur)
{
	this->multiplicateur = multiplicateur;
}

string Competence::getEffet()
{
	return effet;
}

void Competence::setEffet(string effet)
{
	this->effet = effet;
}

string Competence::getBuff()
{
	return buff;
}

void Competence::setBuff(string buff)
{
	this->buff = buff;
}

string Competence::getDebuff()
{
	return debuff;
}

void Competence::setDebuff(string debuff)
{
	this->debuff = debuff;
}

