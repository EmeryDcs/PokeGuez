#pragma once
#include <iostream>
#include <string>
using namespace std;

class Competence
{
	string nom;
	int multiplicateur;
	string effet;
	string buff;
	string debuff;

public:
	Competence();
	Competence(string nom);
	Competence(string nom, int multiplicateur, string effet, string buff, string debuff);

	string getNom();
	void setNom(string nom);
	int getMultiplicateur();
	void setMultiplicateur(int multiplicateur);
	string getEffet();
	void setEffet(string effet);
	string getBuff();
	void setBuff(string buff);
	string getDebuff();
	void setDebuff(string debuff);
};

