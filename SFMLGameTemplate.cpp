#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Joueur.h"
#include "Pokemon.h"
#include "bezier.h"
using namespace std;

const int HAUTEUR	= 720;
const int LARGEUR	= 1280;
//Variable de scale pour afficher les textures en 720p
const float SCALE_L = 3.878787878787879;
const float SCALE_H = 3.287671232876712;
//Positions des boutons du menu de combat
const int POSX_BOUTON_GAUCHE	= 790;
const int POSX_BOUTON_DROITE	= 990;
const int POSY_BOUTON_HAUT		= 580;
const int POSY_BOUTON_BAS		= 650;
//Positions des boutons des comp�tences
const int POSX_BOUTON_COMPETENCE1	= 51;
const int POSX_BOUTON_COMPETENCE2	= 346;
const int POSX_BOUTON_COMPETENCE3	= 640;
const int POSX_BOUTON_COMPETENCE4	= 935;
const int POSY_BOUTON_COMPETENCE	= 561;

sf::Texture POKEMONS;
sf::Texture POKEMONS_ENNEMIS;
sf::Texture PERSONNAGE;
sf::Texture PERSONNAGE_DANSE;
sf::Texture TEXTUREMAP;
sf::Texture TEXTURE_FOND_COMBAT;
sf::Texture TEXTURE_HUD_TEXTE;
sf::Texture TEXTURE_HUD_CHOIX_ACTION;
sf::Texture TEXTURE_HUD_CHOIX_COMPETENCE;
sf::Texture TEXTURE_PV;
sf::Texture TEXTURE_POKEBALL;
sf::Texture TEXTURE_HUD_INVENTAIRE;
sf::Texture TEXTURE_HUD_CHOIX_POKEMON;
sf::Texture TEXTURE_MENU;
sf::Texture TEXTURE_FIN;
sf::Texture TEXTURE_BRULE;
sf::Texture TEXTURE_PARALYSIE;

sf::Sprite  DEBUFF;
sf::Sprite	DEBUFF_ENNEMI;
sf::Sprite	MAP;
sf::Sprite  MENU;
sf::Sprite  FIN;
sf::Sprite	FOND_COMBAT;
sf::Sprite	HUD;
sf::Sprite 	PV_POKEMON_ALLIE;
sf::Sprite 	PV_POKEMON_ENNEMI;
sf::Sprite 	POKEBALL;
sf::Sprite	PV_CHOIX_POKEMON[6];

sf::Font	FONT;
sf::Text	TEXTE;
sf::Text	TEXTE_NOM_ALLIE;
sf::Text	TEXTE_NOM_ENNEMI;
sf::Text	TEXTE_NOM_POKEMON[6];
sf::Text 	TEXTE_ETAT_POKEMON[6];
sf::Text	TEXTE_COMPETENCE[4];

sf::Image	MASQUE;

sf::RectangleShape RECTANGLE_ANIMATION_COMBAT;

sf::Music MUSIQUE_COMBAT;
sf::Music MUSIQUE_MAP;
sf::Music SON_SOIN;

sf::Clock HORLOGE_CHOIX;
sf::Clock HORLOGE_BUISSON;
sf::Clock HORLOGE_POKEBALL;
sf::Clock HORLOGE_TOUR;
sf::Clock HORLOGE_ANIMATION_COMBAT;
sf::Clock HORLOGE_EASTER_EGG;

//Initialise toutes les variables globales
int initialisation() {
	//Initialisation des textures
	if (!TEXTURE_POKEBALL.loadFromFile("Ressource/images/combat/pokeball.png"))
		return EXIT_FAILURE;
	POKEBALL.setTexture(TEXTURE_POKEBALL);
	POKEBALL.setTextureRect(sf::IntRect(0, 0, 16, 16));
	POKEBALL.setScale(SCALE_L, SCALE_H);
	POKEBALL.setPosition(0, 400);

	if (!POKEMONS.loadFromFile("Ressource/images/sprisheet_pokemons.png"))
		return EXIT_FAILURE;

	if (!POKEMONS_ENNEMIS.loadFromFile("Ressource/images/spritesheet_pokemons_ennemis.png"))
		return EXIT_FAILURE;

	if (!PERSONNAGE.loadFromFile("Ressource/images/sprisheet_personnage.png"))
		return EXIT_FAILURE;
	if (!PERSONNAGE_DANSE.loadFromFile("Ressource/images/sprisheet_personnage_danse.png"))
		return EXIT_FAILURE;

	//Initialisation de la map
	if (!TEXTUREMAP.loadFromFile("Ressource/images/map/map.png"))
		return EXIT_FAILURE;
	MAP.setTexture(TEXTUREMAP);
	MAP.setPosition(0, 0);

	//Initialisation du masque
	if (!MASQUE.loadFromFile("Ressource/images/map/masque.png"))
		return EXIT_FAILURE;

	//Initialisation des textures de combat
	if (!TEXTURE_FOND_COMBAT.loadFromFile("Ressource/images/combat/battle_arena_fond.png"))
		return EXIT_FAILURE;
	FOND_COMBAT.setTexture(TEXTURE_FOND_COMBAT);
	FOND_COMBAT.setScale(SCALE_L, SCALE_H);
	FOND_COMBAT.setPosition(0, 0);

	if (!TEXTURE_HUD_TEXTE.loadFromFile("Ressource/images/combat/battle_arena_encart_texte.png"))
		return EXIT_FAILURE;

	if (!TEXTURE_HUD_CHOIX_ACTION.loadFromFile("Ressource/images/combat/battle_arena_encart_texte_+_choix.png"))
		return EXIT_FAILURE;
	HUD.setTexture(TEXTURE_HUD_CHOIX_ACTION);
	HUD.setScale(SCALE_L, SCALE_H);
	HUD.setPosition(0, 0);

	if (!TEXTURE_HUD_CHOIX_COMPETENCE.loadFromFile("Ressource/images/combat/battle_arena_encart_competences.png"))
		return EXIT_FAILURE;

	if (!TEXTURE_PV.loadFromFile("Ressource/images/combat/pv.png"))
		return EXIT_FAILURE;
	PV_POKEMON_ALLIE.setTexture(TEXTURE_PV);
	PV_POKEMON_ALLIE.setScale(SCALE_L, SCALE_H);
	PV_POKEMON_ALLIE.setPosition(1020, 447);
	PV_POKEMON_ENNEMI.setTexture(TEXTURE_PV);
	PV_POKEMON_ENNEMI.setScale(SCALE_L, SCALE_H);
	PV_POKEMON_ENNEMI.setPosition(330, 79);
	int cptY = 0;
	for (int i = 0; i < 6; i++) {
		PV_CHOIX_POKEMON[i].setTexture(TEXTURE_PV);
		PV_CHOIX_POKEMON[i].setScale(SCALE_L, SCALE_H);
		if (i % 2 == 0) {
			PV_CHOIX_POKEMON[i].setPosition(586, 362 + cptY);
		}
		else {
			PV_CHOIX_POKEMON[i].setPosition(1051, 362 + cptY);
			if (i < 3)
				cptY += 157;
			else 
				cptY += 158;
		}
	}

	if (!TEXTURE_HUD_INVENTAIRE.loadFromFile("Ressource/images/combat/affichage_inventaire.png"))
		return EXIT_FAILURE;

	if (!TEXTURE_HUD_CHOIX_POKEMON.loadFromFile("Ressource/images/combat/choix_pokemon.png"))
		return EXIT_FAILURE;

	if (!TEXTURE_MENU.loadFromFile("Ressource/images/menu.png"))
		return EXIT_FAILURE;
	MENU.setTexture(TEXTURE_MENU);
	MENU.setPosition(0, 0);

	if (!TEXTURE_FIN.loadFromFile("Ressource/images/fin.png"))
		return EXIT_FAILURE;
	FIN.setTexture(TEXTURE_FIN);
	FIN.setPosition(0, 0);

	if (!TEXTURE_BRULE.loadFromFile("Ressource/images/combat/brule.png"))
		return EXIT_FAILURE;

	if (!TEXTURE_PARALYSIE.loadFromFile("Ressource/images/combat/paralyse.png"))
		return EXIT_FAILURE;
	DEBUFF.setScale(3, 3);
	DEBUFF.setPosition(890, 440);
	DEBUFF_ENNEMI.setScale(3, 3);
	DEBUFF_ENNEMI.setPosition(200, 71);
	
	//Initialisation du texte
	if (!FONT.loadFromFile("Ressource/font/pokemon.ttf"))
		return EXIT_FAILURE;
	TEXTE.setFont(FONT);
	TEXTE.setCharacterSize(24);
	TEXTE.setFillColor(sf::Color::White);
	TEXTE.setPosition(50, 590);
	TEXTE.setString("");
	TEXTE_NOM_ALLIE.setFont(FONT);
	TEXTE_NOM_ALLIE.setCharacterSize(24);
	TEXTE_NOM_ALLIE.setFillColor(sf::Color::Black);
	TEXTE_NOM_ALLIE.setPosition(889, 405);
	TEXTE_NOM_ALLIE.setString("");
	TEXTE_NOM_ENNEMI.setFont(FONT);
	TEXTE_NOM_ENNEMI.setCharacterSize(24);
	TEXTE_NOM_ENNEMI.setFillColor(sf::Color::Black);
	TEXTE_NOM_ENNEMI.setPosition(200, 37);
	TEXTE_NOM_ENNEMI.setString("");
	cptY = 0;
	for (int i = 0; i < 6; i++) {
		TEXTE_NOM_POKEMON[i].setFont(FONT);
		TEXTE_NOM_POKEMON[i].setCharacterSize(24);
		TEXTE_NOM_POKEMON[i].setFillColor(sf::Color::Black);
		TEXTE_NOM_POKEMON[i].setString("");
		TEXTE_ETAT_POKEMON[i].setFont(FONT);
		TEXTE_ETAT_POKEMON[i].setCharacterSize(24);
		TEXTE_ETAT_POKEMON[i].setFillColor(sf::Color::Black);
		TEXTE_ETAT_POKEMON[i].setString("");

		if (i % 2 == 0) {
			TEXTE_NOM_POKEMON[i].setPosition(475, 275+cptY);
			TEXTE_ETAT_POKEMON[i].setPosition(485, 313 + cptY);
		}
		else {
			TEXTE_NOM_POKEMON[i].setPosition(945, 275 + cptY);
			TEXTE_ETAT_POKEMON[i].setPosition(955, 313 + cptY);
			cptY += 158;
		}
	}
	for (int i = 0; i < 4; i++) {
		TEXTE_COMPETENCE[i].setFont(FONT);
		TEXTE_COMPETENCE[i].setCharacterSize(24);
		TEXTE_COMPETENCE[i].setFillColor(sf::Color::Black);
		TEXTE_COMPETENCE[i].setPosition(POSX_BOUTON_COMPETENCE1 + 5 + 300 * i, POSY_BOUTON_COMPETENCE + 75);
		TEXTE_COMPETENCE[i].setString("");
	}

	//Initialisation de la shape de l'animation de combat
	RECTANGLE_ANIMATION_COMBAT.setSize(sf::Vector2f(80,80));
	RECTANGLE_ANIMATION_COMBAT.setFillColor(sf::Color::Black);
	RECTANGLE_ANIMATION_COMBAT.setPosition(0, 0);

	//Initialisation des horloges
	HORLOGE_CHOIX.restart();
	HORLOGE_BUISSON.restart();
	HORLOGE_POKEBALL.restart();
	HORLOGE_TOUR.restart();
	HORLOGE_ANIMATION_COMBAT.restart();

	//Initialisation des musique
	if (!MUSIQUE_COMBAT.openFromFile("Ressource/musique/combat.mp3"))
		return EXIT_FAILURE;
	MUSIQUE_COMBAT.setVolume(50);
	if (!MUSIQUE_MAP.openFromFile("Ressource/musique/map.mp3"))
		return EXIT_FAILURE;
	MUSIQUE_COMBAT.setVolume(50);
	if (!SON_SOIN.openFromFile("Ressource/musique/soin.mp3"))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

//Fonction qui g�re la cr�ation des Pokemons et du joueur en fonction des variables globales
void creation(Joueur& joueur, Pokemon tabPokemonEnnemi[]) {
	//Cr�ation des Pokemons
	Competence competencesAerodactyl[4] = { 
		Competence("Morsure",			60,		"Aucun",		"Aucun",						"Peur"), 
		Competence("Pouvoir \nAntique",	60,		"Aucun",		"Buff tout",					"Aucun"),
		Competence("Cru-Ailes",			60,		"Aucun",		"Aucun",						"Aucun"),
		Competence("Grimace",			0,		"Aucun",		"Aucun",						"Baisse Vitesse")
	};
	Competence competencesDimoret[4] = { 
		Competence("Assurance",			60,		"Dgts doubles",	"Aucun",						"Aucun"),
		Competence("Groz'Yeux",			0,		"Aucun",		"Aucun",						"Baisse Attaque"),
		Competence("Griffe",			40,		"Aucun",		"Aucun",						"Aucun"),
		Competence("H�te",				0,		"Aucun",		"Vitesse max",					"Aucun")
	};
	Competence competencesDemolos[4] = { 
		Competence("Flamm�che",			40,		"Aucun",		"Aucun",						"Brulure"),
		Competence("Crocs Feu",			65,		"Aucun",		"Aucun",						"Brulure"),
		Competence("Morsure",			60,		"Aucun",		"Aucun",						"Peur"),
		Competence("Griffe",			40,		"Aucun",		"Aucun",						"Aucun")
	};
	Competence competencesTropius[4] = { 
		Competence("Croissance",		0,		"Aucun",		"Augmentation Attaque",			"Aucun"),
		Competence("Tranch'Herbe",		55,		"Aucun",		"Aucun",						"Aucun"),
		Competence("Feuille \nMagik",		60,		"Aucun",		"Aucun",						"Aucun"),
		Competence("�crasement",		65,		"Aucun",		"Aucun",						"Peur")
	};
	Competence competencesRayquaza[4] = {
		Competence("Ouragan",			40,		"Aucun",		"Aucun",						"Peur"),
		Competence("Danse Draco",		0,		"Aucun",		"Buff tout",					"Aucun"),
		Competence("Draco-\nAscension",	120,	"Aucun",		"Aucun",						"Baisse Attaque"),
		Competence("Lame d'Air",		75,		"Aucun",		"Aucun",						"Peur")
	};
	Competence competencesArceus[4] = { 
		Competence("Vitesse \nExtr�me",	80,		"Prioritaire",	"Aucun",						"Aucun"),
		Competence("Ultralaser",		150,	"Repos",		"Aucun",						"Aucun"),
		Competence("Jugement",			100,	"Aucun",		"Aucun",						"Aucun"),
		Competence("Requiem",			100,	"Aucun",		"Aucun",						"Mort dans trois")
	};
	Competence competencesHeydaim[4] = {
		Competence("Balle \nGraine",		25,		"2 � 5",		"Aucun",						"Aucun"),
		Competence("�co-Sph�re",		90,		"Aucun",		"Aucun",						"Aucun"),
		Competence("Lance-Soleil",		120,	"Aucun",		"Aucun",						"Aucun"),
		Competence("B�lier",			90,		"Aucun",		"Se blesse",					"Aucun")
	};
	Competence competencesZekrom[4] = { 
		Competence("Crocs \n�clair",		65,		"Aucun",		"Aucun",						"Paralysie"),
		Competence("Tonerre",			90,		"Aucun",		"Aucun",						"Paralysie"),
		Competence("Fatal-Foudre",		110,	"Aucun",		"Aucun",						"Paralysie"),
		Competence("Charge \nFoudre",		130,	"Aucun",		"Aucun",						"Paralysie")
	};

	Pokemon starter = Pokemon("Aerodactyl", "Vol", 80, 80, 130, competencesAerodactyl, 0, POKEMONS, sf::IntRect(0, 0, 100, 100));
	starter.getSprite().setPosition(225, 250);
	starter.getSprite().setScale(4,4);

	tabPokemonEnnemi[0] = Pokemon("Pt�ra", "Vol", 80, 80, 130, competencesAerodactyl, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 0, 100, 100));
	tabPokemonEnnemi[1] = Pokemon("Dimoret", "Glace", 70, 120, 125, competencesDimoret, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 100, 100, 100));
	tabPokemonEnnemi[2] = Pokemon("Demolos", "Feu", 75, 90, 95, competencesDemolos, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 200, 100, 100));
	tabPokemonEnnemi[3] = Pokemon("Tropius", "Plante", 99, 68, 51, competencesTropius, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 300, 100, 100));
	tabPokemonEnnemi[4] = Pokemon("Rayquaza", "Dragon", 105, 150, 95, competencesRayquaza, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 400, 100, 100));
	tabPokemonEnnemi[5] = Pokemon("Arceus", "Normal", 120, 120, 120, competencesArceus, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 500, 100, 100));
	tabPokemonEnnemi[6] = Pokemon("Haydaim", "Plante", 80, 100, 95, competencesHeydaim, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 600, 100, 100));
	tabPokemonEnnemi[7] = Pokemon("Zekrom", "Electrik", 100, 150, 90, competencesZekrom, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 700, 100, 100));

	for (int i = 0; i < 8; i++) {
		tabPokemonEnnemi[i].getSprite().setScale(3, 3);
		tabPokemonEnnemi[i].getSprite().setPosition(880, -20);
	}

	//Cr�ation du joueur

	Inventaire inventaire = Inventaire();
	joueur = Joueur("Sacha", starter, inventaire, PERSONNAGE, sf::IntRect(0, 0, 32, 35));
	joueur.getSprite().setPosition(450, 630);
	joueur.getSprite().setOrigin(16, 17);
}

//Fonction qui v�rifie les collisions gr�ce au masque
sf::Vector2f collisionsEtBordures(sf::Vector2f vecteurDeplacement, Joueur& joueur) {
	// Gestion des collisions
	sf::Vector2f playerCenterPosition(joueur.getSprite().getPosition().x, joueur.getSprite().getPosition().y+14);
	sf::Vector2i nextPixelPosition(playerCenterPosition.x + vecteurDeplacement.x * 10 * 100, playerCenterPosition.y + vecteurDeplacement.y * 2 * 100);
	int nextPixelColored = MASQUE.getPixel(nextPixelPosition.x, nextPixelPosition.y).toInteger();


	if (nextPixelColored == 255) {
		vecteurDeplacement = sf::Vector2f(0, 0);
	}

	// Gestion des bordures
	if (nextPixelPosition.x < 5 || nextPixelPosition.x > MAP.getGlobalBounds().width + 5 || nextPixelPosition.y < 5 || nextPixelPosition.y > MAP.getGlobalBounds().height + 5) {
		vecteurDeplacement = sf::Vector2f(0, 0);
	}

	return vecteurDeplacement;
}

//Fonction qui g�re l'al�atoire de l'entr�e en combat
bool estSurCaseVerte(Joueur& joueur) {
	int couleurPixelMasque = MASQUE.getPixel(joueur.getSprite().getPosition().x, joueur.getSprite().getPosition().y).toInteger();
	int random = rand() % 100;

	if (HORLOGE_BUISSON.getElapsedTime().asSeconds() > 1) {
		HORLOGE_BUISSON.restart();
		if (couleurPixelMasque == 598040063 && random >= 50) {
			return true;
		} 
	} 
	return false;
}

bool estSurCaseRouge(Joueur& joueur) {
	int couleurPixelMasque = MASQUE.getPixel(joueur.getSprite().getPosition().x, joueur.getSprite().getPosition().y).toInteger();
	if (couleurPixelMasque == -67108609) {
		return true;
	}
	return false;
}

//Fonction qui g�re l'affichage du combat
void hud(int action, Joueur& joueur) {
	switch (action) {
	case 0:
		HUD.setTexture(TEXTURE_HUD_CHOIX_ACTION);
		break;
	case 1:
		HUD.setTexture(TEXTURE_HUD_CHOIX_COMPETENCE);
		for (int i = 0; i < 4; i++) {
			TEXTE_COMPETENCE[i].setString(joueur.getPokemon(0).getCompetence(i).getNom());
		}
		break;
	case 2:
		HUD.setTexture(TEXTURE_HUD_CHOIX_POKEMON);
		for (int i = 0; i < 6; i++) {
			TEXTE_NOM_POKEMON[i].setString(joueur.getPokemon(i).getNom());
			TEXTE_ETAT_POKEMON[i].setString(joueur.getPokemon(i).getNomEtat());
		}
		break;
	case 3:
		HUD.setTexture(TEXTURE_HUD_INVENTAIRE);
		TEXTE.setString("Que voulez-vous utiliser ?");
		break;
	case 4:
		HUD.setTexture(TEXTURE_HUD_TEXTE);
		TEXTE.setString("Vous prenez la fuite !");
		break;
	case 5:
		HUD.setTexture(TEXTURE_HUD_TEXTE);
		TEXTE.setString("Vous avez soign� votre Pok�mon !");
		break;
	case 6:
		HUD.setTexture(TEXTURE_HUD_TEXTE);
		TEXTE.setString("Vous avez lanc� une Pok�ball !");
		break;
	}
}

//Fonction qui v�rifie o� se trouve la souris parmis les 4 boutons des choix du combat
int checkPosition(sf::RenderWindow& window) {
	sf::Vector2i position = sf::Mouse::getPosition(window);
	cout << "CheckPosition : " << position.x << ";" << position.y << endl;
	TEXTE.setString("");
	//Bouton Haut Gauche
	if ((position.x >= POSX_BOUTON_GAUCHE && position.x < POSX_BOUTON_DROITE) && (position.y >= POSY_BOUTON_HAUT && position.y < POSY_BOUTON_BAS))
		return 1;
	//Bouton Haut Droite
	else if ((position.x >= POSX_BOUTON_DROITE && position.x < POSX_BOUTON_DROITE + 200) && (position.y >= POSY_BOUTON_HAUT && position.y < POSY_BOUTON_BAS))
		return 2;
	//Bouton Bas Gauche
	else if ((position.x >= POSX_BOUTON_GAUCHE && position.x < POSX_BOUTON_DROITE) && (position.y >= POSY_BOUTON_BAS && position.y < POSY_BOUTON_BAS + 70))
		return 3;
	//Bouton Bas Droite
	else if ((position.x >= POSX_BOUTON_DROITE && position.x < POSX_BOUTON_DROITE + 200) && (position.y >= POSY_BOUTON_BAS && position.y < POSY_BOUTON_BAS + 70))
		return 4;
	else
		return 0;
}

//Fonction qui v�rifie o� se trouve la souris parmis les 4 boutons de l'inventaire
int checkPositionInventaire(sf::RenderWindow& window) {
	cout << "clic" << endl;
	sf::Vector2i position = sf::Mouse::getPosition(window);
	TEXTE.setString("");
	//Bouton Haut Gauche
	if ((position.x >= POSX_BOUTON_GAUCHE && position.x < POSX_BOUTON_DROITE) && (position.y >= POSY_BOUTON_HAUT && position.y < POSY_BOUTON_BAS))
		return 1;
	//Bouton Haut Droite
	else if ((position.x >= POSX_BOUTON_DROITE && position.x < POSX_BOUTON_DROITE + 200) && (position.y >= POSY_BOUTON_HAUT && position.y < POSY_BOUTON_BAS))
		return 2;
	//Bouton Bas Gauche
	else if ((position.x >= POSX_BOUTON_GAUCHE && position.x < POSX_BOUTON_DROITE) && (position.y >= POSY_BOUTON_BAS && position.y < POSY_BOUTON_BAS + 70))
		return 3;
	//Bouton Bas Droite
	else if ((position.x >= POSX_BOUTON_DROITE && position.x < POSX_BOUTON_DROITE + 200) && (position.y >= POSY_BOUTON_BAS && position.y < POSY_BOUTON_BAS + 70))
		return 4;
	else
		return 0;
}

//Fonction qui v�rifie o� se trouve la souris parmis les 4 boutons des comp�tences
int checkPositionCompetence(sf::RenderWindow& window) {
	sf::Vector2i position = sf::Mouse::getPosition(window);

	HORLOGE_TOUR.getElapsedTime().asSeconds();
	if (position.x >= POSX_BOUTON_COMPETENCE1 && position.x < POSX_BOUTON_COMPETENCE2 && position.y > POSY_BOUTON_COMPETENCE)
		return 0;
	else if (position.x >= POSX_BOUTON_COMPETENCE2 && position.x < POSX_BOUTON_COMPETENCE3 && position.y > POSY_BOUTON_COMPETENCE)
		return 1;
	else if (position.x >= POSX_BOUTON_COMPETENCE3 && position.x < POSX_BOUTON_COMPETENCE4 && position.y > POSY_BOUTON_COMPETENCE)
		return 2;
	else if (position.x >= POSX_BOUTON_COMPETENCE4 && position.x < POSX_BOUTON_COMPETENCE4 + 300 && position.y > POSY_BOUTON_COMPETENCE)
		return 3;

	return 4;
}

//Fonction qui v�rifie o� se trouve la souris parmis les 6 boutons de choix de Pok�mon
int checkPositionChoixPokemon(sf::RenderWindow& window, Joueur& joueur, int iPokemonActif) {
	sf::Vector2i position = sf::Mouse::getPosition(window);

	int l = 120 * SCALE_L;
	int h = 48 * SCALE_H;

	if ((position.x >= 349 && position.x < 349 + l && position.y > 247 && position.y < 247 + h) && joueur.getPokemon(0).getNom() != "Pok�ball vide")//HAUT GAUCHE
		return 0;
	else if ((position.x >= 349 + l && position.x < 945 + 400 + l * 2 && position.y > 247 && position.y < 247 + h) && joueur.getPokemon(1).getNom() != "Pok�ball vide") // HAUT DROITE
		return 1;
	else if ((position.x >= 349 && position.x < 475 + 400 + l && position.y > 247 + 158 && position.y < 247 + 158 + h) && joueur.getPokemon(2).getNom() != "Pok�ball vide") // MILIEU GAUCHE
		return 2;
	else if ((position.x >= 349 + l && position.x < 945 + 400 + l * 2 && position.y > 247 + 158 && position.y < 247 + 158 + h) && joueur.getPokemon(3).getNom() != "Pok�ball vide") // MILIEU DROITE
		return 3;
	else if ((position.x >= 349 && position.x < 475 + 400 + l && position.y > 247 + 158 * 2 - 1 && position.y < 247 + 158 * 2 - 1 + h) && joueur.getPokemon(4).getNom() != "Pok�ball vide") // BAS GAUCHE
		return 4;
	else if ((position.x >= 349 + l && position.x < 945 + 400 + l * 2 && position.y > 247 + 158 * 2 - 1 && position.y < 247 + 158 * 2 - 1 + h) && joueur.getPokemon(5).getNom() != "Pok�ball vide") // BAS DROITE
		return 5;

	return -1;
}

//Fonction d'animation de la pok�ball lors du lancer
void animPokeball(float t, sf::RenderWindow& window) {
	static int cptTop = 0;
	sf::Vector2f vDebut(0, 400);
	sf::Vector2f vFin(1000, 240);
	sf::Vector2f vMilieu(350, 100);
	sf::Vector2f vMove = bezierQuadratic(vDebut, vMilieu, vFin, t/1.9);

	if (HORLOGE_POKEBALL.getElapsedTime().asSeconds() > 0.2f && HORLOGE_CHOIX.getElapsedTime().asSeconds() < 2.0) {
		HORLOGE_POKEBALL.restart();
		cptTop += 16;
		if (cptTop >= 128)
			cptTop = 0;
		POKEBALL.setTextureRect(sf::IntRect(0, cptTop, 16, 16));
	}
	else if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 2.0) {
		POKEBALL.setTextureRect(sf::IntRect(0, 0, 16, 16));
	}

	if (vMove.x > vFin.x)
		vMove = vFin;

	POKEBALL.setPosition(vMove);
	window.draw(POKEBALL);
}

//Fonction qui g�re la partie Inventaire dans le menu Inventaire du combat
void gestionInventaire(int& action, int& positionClicInventaire, bool& combat, int i, Joueur& joueur, Pokemon& pokemonEnnemi, sf::RenderWindow& window) {
	static string s = "";
	static bool joueurLance = false;
	static bool aSoigne = false;

	//Gestion de l'inventaire
	switch (positionClicInventaire) {
	case 1:
		//Soigner
		if (joueur.getInventaire().getNbPotion() <= 0) {
			TEXTE.setString("Vous n'avez plus de potion !");
			action = 0;
			positionClicInventaire = 0;
		}
		else {
			if (HORLOGE_CHOIX.getElapsedTime().asSeconds() < 2) {
				TEXTE.setString("Vous soignez votre Pok�mon !");
			}
			else if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 2 && HORLOGE_CHOIX.getElapsedTime().asSeconds() < 4) {
				TEXTE.setString("Le Pok�mon ennemi attaque !");
				if (!aSoigne) {
					aSoigne = true;
					joueur.soin(0);
				}
			}
			else if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 4) {
				HORLOGE_CHOIX.restart();
				pokemonEnnemi.attaquer(joueur.getPokemon(i), pokemonEnnemi.getCompetence(rand() % 4));
				action = 0;
				positionClicInventaire = 0;
				aSoigne = false;
			}
		}
		break;
	case 2:
		//Pok�ball
		if (joueur.getInventaire().getNbPokeball() <= 0) {
			TEXTE.setString("Vous n'avez plus de pok�ball !");
			if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 2) {
				action = 0;
				positionClicInventaire = 0;
			}
		}
		else {
			animPokeball(HORLOGE_CHOIX.getElapsedTime().asSeconds(), window);
			if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 2 && HORLOGE_CHOIX.getElapsedTime().asSeconds() < 4) {
				pokemonEnnemi.getSprite().setColor(sf::Color(0, 0, 0, 0));
				if (!joueurLance) {
					joueurLance = true;
					s = joueur.pokeball(pokemonEnnemi, POKEMONS);
				}
				TEXTE.setString(s);
			}
			else if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 4) {
				HORLOGE_CHOIX.restart();
				action = 0;
				positionClicInventaire = 0;
				if (s == "Capture reussie" || s == "Capture r�ussie, mais vous �tes d�j� complet en Pok�mon.") {
					combat = false;
				}
				pokemonEnnemi.getSprite().setColor(sf::Color(255, 255, 255, 255));
				joueurLance = false;
			}
		}
		break;
	case 3:
		//Spray
		if (joueur.getInventaire().getNbSpray() <= 0) {
			TEXTE.setString("Vous n'avez plus de spray !");
			positionClicInventaire = 0;
			action = 0;
		}
		else {
			if (HORLOGE_CHOIX.getElapsedTime().asSeconds() < 4)
				TEXTE.setString("Spray utilis� !");
			else {
				joueur.getPokemon(i).setEtat(0);
				positionClicInventaire = 0;
				action = 0;
			}
		}
		break;
	case 4:
		//Retour
		action = 0;
		positionClicInventaire = 0;
		break;
	}
}

//Fonction qui g�re la partie d'Attaque et le choix de la comp�tence
void gestionAttaque(int& action, int& competence, bool& combat, Joueur& joueur, int& iPokemonActif, Pokemon& pokemonEnnemi, sf::RenderWindow& window) {
	static bool joueurJoue = true;
	static bool pokemonJoue = true;
	static bool seRepose = false;
	static bool debuffApplique = false;
	static bool debuffAppliqueEnnemi = false;
	static int competenceRandomEnnemi = 0;
	int randomParalysie = 0;

	if (competence != 4) { //Si le joueur a choisi une comp�tence
		if (joueur.getPokemon(iPokemonActif).getEtat() == 2 && !debuffApplique) { //Si le pok�mon du joueur est brul�
			HUD.setTexture(TEXTURE_HUD_TEXTE);
			TEXTE.setString("Votre Pok�mon br�le !");
			joueur.getPokemon(iPokemonActif).setPv(joueur.getPokemon(iPokemonActif).getPv() - 10);
			debuffApplique = true;
		}
		if (pokemonEnnemi.getEtat() == 2 && !debuffAppliqueEnnemi) { //Si le pok�mon ennemi est brul�
			HUD.setTexture(TEXTURE_HUD_TEXTE);
			TEXTE.setString("Le Pok�mon ennemi br�le !");
			pokemonEnnemi.setPv(pokemonEnnemi.getPv() - 10);
			debuffAppliqueEnnemi = true;
		}

		string competenceJoueur = joueur.getPokemon(iPokemonActif).getCompetence(competence).getEffet();

		//Condition si jamais le joueur a utilis� une technique obligeant le repos
		if (seRepose || joueur.getPokemon(iPokemonActif).getEtat() == 1) {
			HUD.setTexture(TEXTURE_HUD_TEXTE);
			if (seRepose)
				TEXTE.setString("Votre Pok�mon se repose !");
			else
				TEXTE.setString("Votre Pok�mon est paralys� !");
			if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
				TEXTE.setString("Le Pok�mon ennemi attaque !");
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 4.0) {
					competence = 4;
					joueurJoue = true;
					pokemonEnnemi.attaquer(joueur.getPokemon(iPokemonActif), pokemonEnnemi.getCompetence(rand() % 4));
					HORLOGE_TOUR.restart();
					action = 0;
					seRepose = false;
					debuffApplique = false;
					debuffAppliqueEnnemi = false;
					randomParalysie = rand() % 100;
					if (joueur.getPokemon(iPokemonActif).getEtat() == 1 && randomParalysie >= 50)
						joueur.getPokemon(iPokemonActif).setEtat(0);
					if (pokemonEnnemi.getEtat() == 1 && randomParalysie >= 50)
						pokemonEnnemi.setEtat(0);
				}
			}
		}
		//Condition si le joueur est plus rapide ou que sa comp�tence poss�de l'effet Prioritaire
		else if (joueur.getPokemon(iPokemonActif).getVitesse() >= pokemonEnnemi.getVitesse() || competenceJoueur == "Prioritaire") {
			if (joueurJoue) { //Tour du joueur
				HUD.setTexture(TEXTURE_HUD_TEXTE);
				TEXTE.setString("Vous avez utilis� " + joueur.getPokemon(iPokemonActif).getCompetence(competence).getNom() + " !");
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
					if (competenceJoueur == "Dgts double") {
						joueur.getPokemon(iPokemonActif).attaquer(pokemonEnnemi, joueur.getPokemon(iPokemonActif).getCompetence(competence));
					}
					else if (competenceJoueur == "2 � 5") {
						int random = rand() % 4;
						for (int i = 0; i < random; i++) {
							joueur.getPokemon(iPokemonActif).attaquer(pokemonEnnemi, joueur.getPokemon(iPokemonActif).getCompetence(competence));
						}
					}
					joueur.getPokemon(iPokemonActif).attaquer(pokemonEnnemi, joueur.getPokemon(iPokemonActif).getCompetence(competence));
					joueurJoue = false;
					HORLOGE_TOUR.restart();
					competenceRandomEnnemi = rand() % 4;
				}
			}
			else if (pokemonEnnemi.getPv() > 0 && pokemonEnnemi.getEtat() != 1) { //Tour du Pok�mon ennemi s'il n'est pas paralys�
				HUD.setTexture(TEXTURE_HUD_TEXTE);
				TEXTE.setString("Le Pok�mon ennemi attaque  et utilise " + pokemonEnnemi.getCompetence(competenceRandomEnnemi).getNom() + "!");
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
					competence = 4;
					joueurJoue = true;
					pokemonEnnemi.attaquer(joueur.getPokemon(iPokemonActif), pokemonEnnemi.getCompetence(competenceRandomEnnemi));
					HORLOGE_TOUR.restart();
					action = 0;
					debuffAppliqueEnnemi = false;
					debuffApplique = false;
					if (competenceJoueur == "Repos")
						seRepose = true;
					randomParalysie = rand() % 100;
					if (joueur.getPokemon(iPokemonActif).getEtat() == 1 && randomParalysie >= 50)
						joueur.getPokemon(iPokemonActif).setEtat(0);
					if (pokemonEnnemi.getEtat() == 1 && randomParalysie >= 50)
						pokemonEnnemi.setEtat(0);
				}
			}
			else if (pokemonEnnemi.getPv() > 0 && pokemonEnnemi.getEtat() == 1) { //Tour du Pok�mon ennemi s'il est paralys�
				HUD.setTexture(TEXTURE_HUD_TEXTE);
				TEXTE.setString("Le Pok�mon ennemi est paralys� !"); 
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
					cout << "coucou" << endl;
					competence = 4;
					joueurJoue = true;
					HORLOGE_TOUR.restart();
					action = 0;
					debuffAppliqueEnnemi = false;
					debuffApplique = false;
					if (competenceJoueur == "Repos")
						seRepose = true;
					randomParalysie = rand() % 100;
					if (joueur.getPokemon(iPokemonActif).getEtat() == 1 && randomParalysie >= 50)
						joueur.getPokemon(iPokemonActif).setEtat(0);
					if (pokemonEnnemi.getEtat() == 1 && randomParalysie >= 50)
						pokemonEnnemi.setEtat(0);
				}
			}
			else if (pokemonEnnemi.getPv() <= 0) { //Fin du combat, ennemi K.O.
				HUD.setTexture(TEXTURE_HUD_TEXTE);
				TEXTE.setString("Vous avez vaincu le Pok�mon ennemi !");
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
					joueurJoue = true;
					HORLOGE_TOUR.restart();
					action = 0;
					debuffAppliqueEnnemi = false;
					debuffApplique = false;
					combat = false;
					randomParalysie = rand() % 100;
					if (joueur.getPokemon(iPokemonActif).getEtat() == 1 && randomParalysie >= 50)
						joueur.getPokemon(iPokemonActif).setEtat(0);
					if (pokemonEnnemi.getEtat() == 1 && randomParalysie >= 50)
						pokemonEnnemi.setEtat(0);
				}
			}
		}
		//Condition si l'ennemi est plus rapide
		else { //if (joueur.getPokemon(iPokemonActif).getVitesse() >= pokemonEnnemi.getVitesse())
			if (pokemonJoue && pokemonEnnemi.getEtat() != 1) { //Pok�mon ennemi attaque
				HUD.setTexture(TEXTURE_HUD_TEXTE);
				TEXTE.setString("Le Pok�mon ennemi attaque !");
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
					pokemonJoue = false;
					pokemonEnnemi.attaquer(joueur.getPokemon(iPokemonActif), pokemonEnnemi.getCompetence(rand() % 4));
					HORLOGE_TOUR.restart();
				}
			}
			else if (pokemonJoue && pokemonEnnemi.getEtat() == 1) { //Pok�mon ennemi paralys�
				HUD.setTexture(TEXTURE_HUD_TEXTE);
				TEXTE.setString("Le Pok�mon ennemi est paralys� !");
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
					pokemonJoue = false;
					HORLOGE_TOUR.restart();
				}
			}
			else if (joueur.getPokemon(iPokemonActif).getPv() > 0) { //Tour du joueur
				if (competence != 4) {
					HUD.setTexture(TEXTURE_HUD_TEXTE);
					TEXTE.setString("Vous avez utilis� " + joueur.getPokemon(iPokemonActif).getCompetence(competence).getNom() + " !");
					if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
						joueur.getPokemon(iPokemonActif).attaquer(pokemonEnnemi, joueur.getPokemon(iPokemonActif).getCompetence(competence));
						pokemonJoue = true;
						HORLOGE_TOUR.restart();
						competence = 4;
						action = 0;
						debuffAppliqueEnnemi = false;
						debuffApplique = false;
						if (competenceJoueur == "Repos")
							seRepose = true;
						randomParalysie = rand() % 100;
						if (joueur.getPokemon(iPokemonActif).getEtat() == 1 && randomParalysie >= 50)
							joueur.getPokemon(iPokemonActif).setEtat(0);
						if (pokemonEnnemi.getEtat() == 1 && randomParalysie >= 50)
							pokemonEnnemi.setEtat(0);
					}
				}
			}
			else if (joueur.getPokemon(iPokemonActif).getPv() <= 0) {
				TEXTE.setString("Changement de Pokemon !");
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
					pokemonJoue = true;
					HORLOGE_TOUR.restart();
					action = 0;
					debuffAppliqueEnnemi = false;
					debuffApplique = false;
					randomParalysie = rand() % 100;
					if (joueur.getPokemon(iPokemonActif).getEtat() == 1 && randomParalysie >= 50)
						joueur.getPokemon(iPokemonActif).setEtat(0);
					if (pokemonEnnemi.getEtat() == 1 && randomParalysie >= 50)
						pokemonEnnemi.setEtat(0);
				}
			}
		}
	}
}

//Fonction qui g�re les choix du joueur
void gestionChoix(int& action, int& clicPositionInventaire, int& clicPokemonActif, int& competence, bool& combat, bool& joueurLance, Joueur& joueur, int& iPokemonActif, Pokemon& pokemonEnnemi, sf::RenderWindow& window) {

	switch (action) {
	case 0:
		TEXTE.setString("Un Pok�mon sauvage appara�t !\nQue voulez-vous faire ?");
		break;
	case 1:
		//Choix de la comp�tence
		TEXTE.setString("A vous !");
		gestionAttaque(action, competence, combat, joueur, iPokemonActif, pokemonEnnemi, window);
		break;
	case 2:
		//Changement de Pok�mon
		if (clicPokemonActif != -1) {
			HUD.setTexture(TEXTURE_HUD_TEXTE);
			TEXTE.setString("Viens " + joueur.getPokemon(clicPokemonActif).getNom() + " !");
			if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 2.0) {
				iPokemonActif = clicPokemonActif;
				action = 0;
				clicPokemonActif = -1;
				HORLOGE_CHOIX.restart();
			}
		}
		break;
	case 3:
		//Inventaire
		gestionInventaire(action, clicPositionInventaire, combat, iPokemonActif, joueur, pokemonEnnemi, window);
		HORLOGE_TOUR.restart();
		break;
	case 4:
		//Fuir
		if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 2) {
			HORLOGE_CHOIX.restart();
			combat = false;
			HORLOGE_BUISSON.restart();
			action = 0;
		}
		break;
	}
}

//Fonction qui g�re l'affichage des PV des Pok�mons
void scalePv(Joueur& joueur, Pokemon& pokemonEnnemi, int iPokemonActif) {
	float longueurJoueur = 5.32 * joueur.getPokemon(iPokemonActif).getPv() / joueur.getPokemon(iPokemonActif).getPvMax();
	float longueurEnnemi = 5.32 * pokemonEnnemi.getPv() / pokemonEnnemi.getPvMax();
	if (joueur.getPokemon(iPokemonActif).getPv() <= 0) {
		longueurJoueur = 0;
	}
	if (pokemonEnnemi.getPv() <= 0) {
		longueurEnnemi = 0;
	}
	PV_POKEMON_ALLIE.setScale(longueurJoueur*SCALE_L, SCALE_H);
	PV_POKEMON_ENNEMI.setScale(longueurEnnemi*SCALE_L, SCALE_H);
} 

//Fonction qui g�re l'affichage des PV des Pok�mons dans le menu de choix de Pok�mon
void scalePvChoixPokemon(Pokemon& pokemon, int i) {
	float longueur = 5.32 * pokemon.getPv() / pokemon.getPvMax();
	PV_CHOIX_POKEMON[i].setScale(longueur * SCALE_L, SCALE_H);
}

//Fonction qui g�re le changement de Pok�mon si le Pok�mon actif est mort
bool changementPokemonMort(int& iPokemonActif, Joueur& joueur, int& action, bool& combat) {
	if (joueur.getPokemon(iPokemonActif).getPv() <= 0) {
		for (int i = 0; i < 6; i++) {
			if (joueur.getPokemon(i).getPv() > 0) {
				iPokemonActif = i;
				break;
			}
			else {
				TEXTE.setString("Vous avez perdu !");
				if (HORLOGE_TOUR.getElapsedTime().asSeconds() > 2.0) {
					HORLOGE_TOUR.restart();
					action = 0;
					combat = false;
				}
				return true;
			}
		}
	}
	return false;
}

//Fonction qui soigne tous les Pok�mons et rempli l'inventaire du joueur
void soinEtRefill(Joueur& joueur) {
	for (int i = 0; i < 6; i++) {
		joueur.getPokemon(i).setPv(joueur.getPokemon(i).getPvMax());
		joueur.getPokemon(i).setEtat(0);
	}
	joueur.getInventaire().setNbPotion(5);
	joueur.getInventaire().setNbPokeball(20);
	joueur.getInventaire().setNbSpray(5);


}

//Fonction qui r�initialise les PV et l'�tat de tous les Pok�mons ennemis apr�s un combat
void resetEnnemi(Pokemon pokemon[], int taille) {
	for (int i = 0; i < taille; i++) {
		pokemon[i].setPv(pokemon[i].getPvMax());
		pokemon[i].setEtat(0);
	}
}

//Fonction qui g�re la musique
void jouerMusique(bool& combat) {
	if (combat) {
		MUSIQUE_MAP.stop();
		if (MUSIQUE_COMBAT.getStatus() == sf::Music::Stopped) {
			MUSIQUE_COMBAT.play();
		}
	}
	else {
		MUSIQUE_COMBAT.stop();
		if (MUSIQUE_MAP.getStatus() == sf::Music::Stopped) {
			MUSIQUE_MAP.play();
		}
	}
}

int main()
{
	//Initialisation de la seed pour les fonctions al�atoires
	srand(time(NULL));

	//Cr�ation de la fen�tre
	sf::RenderWindow window(sf::VideoMode(LARGEUR, HAUTEUR), "Pok�guez");

	//Initialisation des textures et de la map
	if (initialisation() == EXIT_FAILURE) {
		cout << "Erreur lors de l'initialisation des textures" << endl;
		return EXIT_FAILURE;
	}

	//Cr�ation des personnages et Pokemons
	Joueur joueur;
	Pokemon aerodactyl;
	Pokemon dimoret;
	Pokemon tabPokemonEnnemi[8];

	creation(joueur, tabPokemonEnnemi);

	//Camera du jeu 
	float zoom = 0.4f;
	sf::View gameView(sf::FloatRect(0, 0, LARGEUR, HAUTEUR));
	gameView.setSize(window.getSize().x * zoom, window.getSize().y * zoom);
	gameView.setCenter(joueur.getSprite().getPosition());
	window.setView(gameView);
	const float minCameraX = gameView.getSize().x / 2.0f;
	const float minCameraY = gameView.getSize().y / 2.0f;
	const float maxCameraX = MAP.getGlobalBounds().width - minCameraX;
	const float maxCameraY = MAP.getGlobalBounds().height - minCameraY;
	float newCameraX = 0;
	float newCameraY = 0;
	sf::Vector2f vecteurDeplacement = sf::Vector2f(0, 0);

	//Bool�en pour savoir si le joueur est en combat
	bool combat = false;

	//Bool�en pour savoir si le joueur bouge
	bool bouge = true;

	//Bool�en pour savoir si le joueur a lanc� une pok�ball
	bool joueurLance = false;

	//Entier pour conna�tre l'action du joueur
	int action = 0; // 0. choix_action | 1. competence | 2. inventaire | 3. choix pokemon | 4. fuir 
	int competence = 4; // 0. competence1 1. competence2 2. competence3 3. competence4
	int clicPositionInventaire = 0; // 0. rien | 1. soin | 2. pok�ball | 3. spray | 4. retour

	//Entier pour conna�tre le pok�mon actif
	int iPokemonActif = 0;
	int clicPokemonActif = -1;

	//Random pour conna�tre le pok�mon ennemi
	int randomEnnemi = 0;

	//Compteur pour l'animation pr�-combat
	int cptAnimCombat = 0;
	int xRect = 0;
	int yRect = 0;

	//String permettant de savoir quelle fen�tre afficher
	string ecran = "menu"; // "menu" | "jeu" | "fin"
		
	//Boucle de la fen�tre
	while (window.isOpen()) {
		sf::Event event;

		//Gestion des �v�nements 
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Up) {
					HORLOGE_EASTER_EGG.restart();
					bouge = true;
					vecteurDeplacement = sf::Vector2f(0, -.010);
				}
				else if (event.key.code == sf::Keyboard::Down) {
					HORLOGE_EASTER_EGG.restart();
					bouge = true;
					vecteurDeplacement = sf::Vector2f(0, .010);
				}
				else if (event.key.code == sf::Keyboard::Left) {
					HORLOGE_EASTER_EGG.restart();
					bouge = true;
					vecteurDeplacement = sf::Vector2f(-.010, 0);
				}
				else if (event.key.code == sf::Keyboard::Right) {
					HORLOGE_EASTER_EGG.restart();
					bouge = true;
					vecteurDeplacement = sf::Vector2f(.010, 0);
				}
				else if (event.key.code == sf::Keyboard::Enter && (ecran == "menu" || ecran == "fin")) {
					ecran = "jeu";
				}
				else if (event.key.code == sf::Keyboard::Enter && ecran == "jeu") {
					if (estSurCaseRouge(joueur)) {
						soinEtRefill(joueur);
						if (SON_SOIN.getStatus() == sf::Music::Stopped) {
							SON_SOIN.play();
						}
					}
				}
				break;
			case sf::Event::KeyReleased:
				vecteurDeplacement = sf::Vector2f(0, 0);
				bouge = false;
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (action == 0) {
						HORLOGE_CHOIX.restart();
						HORLOGE_TOUR.restart();
						action = checkPosition(window);
						joueurLance = false;
					}
					else if (action == 3) {
						clicPositionInventaire = checkPositionInventaire(window);
					}
					else if (action == 2) {
						clicPokemonActif = checkPositionChoixPokemon(window, joueur, iPokemonActif);
					}
					else {
						competence = checkPositionCompetence(window);
					}
				}
				break;
			}
		}

		if (ecran == "menu") {
			//---------Code et affichage pour le menu--------
			window.clear();
			window.draw(MENU);
			gameView.setSize(window.getSize().x, window.getSize().y);
			gameView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
			window.setView(gameView);
			window.display();
			HORLOGE_EASTER_EGG.restart();
		}
		else if (ecran == "jeu") {
			jouerMusique(combat);
			if (combat && cptAnimCombat < 144) {
				if (cptAnimCombat == 0) {
					xRect = 0;
					yRect = 0;
				}
				RECTANGLE_ANIMATION_COMBAT.setPosition(sf::Vector2f(xRect, yRect));
				if (HORLOGE_ANIMATION_COMBAT.getElapsedTime().asSeconds() > 0.02f) {
					HORLOGE_ANIMATION_COMBAT.restart();
					cptAnimCombat++;
					window.draw(RECTANGLE_ANIMATION_COMBAT);
					xRect += 80;
					if (xRect >= 1280) {
						xRect = 0;
						yRect += 80;
					}
					window.display();
				}
			}
			else if (combat && cptAnimCombat >= 144) {
				//---------Code et affichage pour le combat--------
				window.clear();

				//Affichage du fond de combat
				window.draw(FOND_COMBAT);

				//Loop sur les animations des pokemons
				joueur.loopPokemon();
				tabPokemonEnnemi[randomEnnemi].loop();
				//Affichage des pokemons
				window.draw(joueur.getPokemon(iPokemonActif).getSprite());
				window.draw(tabPokemonEnnemi[randomEnnemi].getSprite());

				//On check les PV du pok�mon actif et on change si il est mort

				if (!changementPokemonMort(iPokemonActif, joueur, action, combat)) {

					//Affichage de l'HUD.
					hud(action, joueur);

					//Gestion du combat
					gestionChoix(action, clicPositionInventaire, clicPokemonActif, competence, combat, joueurLance, joueur, iPokemonActif, tabPokemonEnnemi[randomEnnemi], window);

				}
				else {
					//On t�l�porte le joueur au centre Pok�mon, on soigne les Pok�mon et on retourne � l'exploration
					joueur.getSprite().setPosition(450, 630);
					for (int i = 0; i < 6; i++) {
						joueur.getPokemon(i).setPv(joueur.getPokemon(i).getPvMax());
					}
					combat = false;
					action = 0;
					if (SON_SOIN.getStatus() == sf::Music::Stopped) {
						SON_SOIN.play();
					}
				}

				//Affichage du texte
				TEXTE_NOM_ALLIE.setString(joueur.getPokemon(iPokemonActif).getNom());
				TEXTE_NOM_ENNEMI.setString(tabPokemonEnnemi[randomEnnemi].getNom());

				//Affichage des PV
				scalePv(joueur, tabPokemonEnnemi[randomEnnemi], iPokemonActif);
				for (int i = 0; i < 6; i++) {
					scalePvChoixPokemon(joueur.getPokemon(i), i);
				}

				//Gestion de la View
				gameView.setSize(window.getSize().x, window.getSize().y);
				gameView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
				window.setView(gameView);

				//On affiche tout ce qui �volue dans le combat
				window.draw(PV_POKEMON_ALLIE);
				window.draw(PV_POKEMON_ENNEMI);
				window.draw(TEXTE_NOM_ALLIE);
				window.draw(TEXTE_NOM_ENNEMI);
				window.draw(HUD);
				if (action == 2) {
					for (int i = 0; i < 6; i++) {
						if (HUD.getTexture() == &TEXTURE_HUD_CHOIX_POKEMON) {
							window.draw(TEXTE_ETAT_POKEMON[i]);
							window.draw(TEXTE_NOM_POKEMON[i]);
							window.draw(PV_CHOIX_POKEMON[i]);
						}
					}
				}
				else if (action == 1 && competence == 4) {
					for (int i = 0; i < 4; i++) {
						window.draw(TEXTE_COMPETENCE[i]);
					}
				}
				window.draw(TEXTE);

				//Si le pok�mon alli� est d�buff, on affiche
				if (joueur.getPokemon(iPokemonActif).getEtat() == 2) {
					DEBUFF.setTexture(TEXTURE_BRULE);
					window.draw(DEBUFF);
				}
				else if (joueur.getPokemon(iPokemonActif).getEtat() == 1) {
					DEBUFF.setTexture(TEXTURE_PARALYSIE);
					window.draw(DEBUFF);
				}
				//Si le pok�mon ennemi est d�buff, on affiche
				if (tabPokemonEnnemi[randomEnnemi].getEtat() == 2) {
					DEBUFF_ENNEMI.setTexture(TEXTURE_BRULE);
					window.draw(DEBUFF_ENNEMI);
				}
				else if (tabPokemonEnnemi[randomEnnemi].getEtat() == 1) {
					DEBUFF_ENNEMI.setTexture(TEXTURE_PARALYSIE);
					window.draw(DEBUFF_ENNEMI);
				}

				window.display();

				HORLOGE_EASTER_EGG.restart();

			}
			else {
				//---------Code et affichage pour l'exploration--------
				cptAnimCombat = 0;
				//V�rifications des collisions et bordures puis d�placement du joueur.
				if (bouge) {
					if (combat = estSurCaseVerte(joueur))
						resetEnnemi(tabPokemonEnnemi, 8);
					randomEnnemi = rand() % 8;
				}
				vecteurDeplacement = collisionsEtBordures(vecteurDeplacement, joueur);

				//Easter Egg, joueur danse sur la musique
				if (HORLOGE_EASTER_EGG.getElapsedTime().asSeconds() > 10.0f) {
					joueur.getSprite().setTexture(PERSONNAGE_DANSE);
					joueur.danse();
				}
				else {
					joueur.getSprite().setTexture(PERSONNAGE);
					joueur.deplacement(vecteurDeplacement);
				}

				//Affichage des �l�ments

				window.clear();

				window.draw(MAP);

				newCameraX = min(max(minCameraX, joueur.getSprite().getPosition().x), maxCameraX);
				newCameraY = min(max(minCameraY, joueur.getSprite().getPosition().y), maxCameraY);

				gameView.setSize(window.getSize().x * zoom, window.getSize().y * zoom);
				gameView.setCenter(newCameraX, newCameraY);
				window.setView(gameView);

				window.draw(joueur.getSprite());

				window.display();
			}
		}
		else if (ecran == "fin") {
			window.clear();
			window.draw(MENU);
			gameView.setSize(window.getSize().x, window.getSize().y);
			gameView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
			window.setView(gameView);
			window.display();
		}
	}
}
