#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Joueur.h"
#include "Pokemon.h"
using namespace std;

const int HAUTEUR	= 720;
const int LARGEUR	= 1280;
const float SCALE_L = 3.878787878787879;
const float SCALE_H = 3.287671232876712;
const int POSX_BOUTON_GAUCHE	= 890;
const int POSX_BOUTON_DROITE	= 1090;
const int POSY_BOUTON_HAUT		= 580;
const int POSY_BOUTON_BAS		= 650;
const int POSX_BOUTON_COMPETENCE1	= 51;
const int POSX_BOUTON_COMPETENCE2	= 346;
const int POSX_BOUTON_COMPETENCE3	= 640;
const int POSX_BOUTON_COMPETENCE4	= 935;
const int POSY_BOUTON_COMPETENCE	= 561;

sf::Texture POKEMONS;
sf::Texture POKEMONS_ENNEMIS;
sf::Texture PERSONNAGE;
sf::Texture TEXTUREMAP;
sf::Texture TEXTURE_FOND_COMBAT;
sf::Texture TEXTURE_HUD_TEXTE;
sf::Texture TEXTURE_HUD_CHOIX_ACTION;
sf::Texture TEXTURE_HUD_CHOIX_COMPETENCE;
sf::Texture TEXTURE_PV;
sf::Sprite	MAP;
sf::Sprite	FOND_COMBAT;
sf::Sprite	HUD;
sf::Sprite 	PV_POKEMON_ALLIE;
sf::Sprite 	PV_POKEMON_ENNEMI;
sf::Font	FONT;
sf::Text	TEXTE;
sf::Text	TEXTE_NOM_ALLIE;
sf::Text	TEXTE_NOM_ENNEMI;
sf::Image	MASQUE;

sf::Clock HORLOGE_CHOIX;
sf::Clock HORLOGE_BUISSON;

int initialisation() {
	//Initialisation des textures
	if (!POKEMONS.loadFromFile("Ressource/images/sprisheet_pokemons.png"))
		return EXIT_FAILURE;

	if (!POKEMONS_ENNEMIS.loadFromFile("Ressource/images/sprisheet_pokemons.png")) // !!!!!!!! spritesheet � changer !!!!!!!!
		return EXIT_FAILURE;

	if (!PERSONNAGE.loadFromFile("Ressource/images/sprisheet_personnage.png"))
		return EXIT_FAILURE;

	//Initialisation de la map
	if (!TEXTUREMAP.loadFromFile("Ressource/images/map/map.png"))
		return EXIT_FAILURE;
	MAP.setTexture(TEXTUREMAP);
	MAP.setPosition(0, 0);

	//Initialisation du masque
	if (!MASQUE.loadFromFile("Ressource/images/map/masque.png"))
		return EXIT_FAILURE;

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
	
	//Initialisation du texte
	if (!FONT.loadFromFile("Ressource/font/pokemon.ttf"))
		return EXIT_FAILURE;
	TEXTE.setFont(FONT);
	TEXTE.setCharacterSize(24);
	TEXTE.setFillColor(sf::Color::White);
	TEXTE.setPosition(75, 600);
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

	//Initialisation des horloges
	HORLOGE_CHOIX.restart();
	HORLOGE_BUISSON.restart();

	return EXIT_SUCCESS;
}

void creation(Joueur& joueur, Pokemon tabPokemonEnnemi[2]) {
	//Cr�ation des Pokemons
	Competence competencesAerodactyl[4];
	Competence competencesDimoret[4];
	Pokemon starter = Pokemon("Aerodactyl", "Vol", 120, 10, 10, competencesAerodactyl, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 0, 100, 100));
	starter.getSprite().setPosition(225, 334);
	starter.getSprite().setScale(4,4);

	tabPokemonEnnemi[0] = Pokemon("Aerodactyl", "Vol", 120, 10, 10, competencesAerodactyl, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 0, 100, 100));
	tabPokemonEnnemi[1] = Pokemon("Dimoret", "Normal", 120, 10, 10, competencesDimoret, 0, POKEMONS_ENNEMIS, sf::IntRect(0, 100, 100, 100));
	tabPokemonEnnemi[0].getSprite().setPosition(930, 0);
	tabPokemonEnnemi[0].getSprite().setScale(4,4);
	tabPokemonEnnemi[1].getSprite().setPosition(930, 0);
	tabPokemonEnnemi[1].getSprite().setScale(4,4);

	//Cr�ation du joueur

	Inventaire inventaire = Inventaire();
	joueur = Joueur("Sacha", starter, inventaire, PERSONNAGE, sf::IntRect(0, 0, 32, 35));
	joueur.getSprite().setPosition(450, 300); 
	joueur.getSprite().setOrigin(16, 17);
}

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

bool estSurCaseVerte(Joueur& joueur) {
	int couleurPixelMasque = MASQUE.getPixel(joueur.getSprite().getPosition().x, joueur.getSprite().getPosition().y).toInteger();
	int random = rand() % 100;

	if (HORLOGE_BUISSON.getElapsedTime().asSeconds() > 1) {
		HORLOGE_BUISSON.restart();
		if (couleurPixelMasque == 598040063 && random >= 50)
			return true;
	} 
	else
		return false;
}

void hud(int action) {
	switch (action) {
	case 0:
		HUD.setTexture(TEXTURE_HUD_CHOIX_ACTION);
		break;
	case 1:
		HUD.setTexture(TEXTURE_HUD_CHOIX_COMPETENCE);
		break;
	case 2:
		HUD.setTexture(TEXTURE_HUD_TEXTE);
		TEXTE.setString("Vous avez soign� votre Pok�mon !");
		break;
	case 3:
		HUD.setTexture(TEXTURE_HUD_TEXTE);
		TEXTE.setString("Vous avez lanc� une Pok�ball !");
		break;
	case 4:
		HUD.setTexture(TEXTURE_HUD_TEXTE);
		TEXTE.setString("Vous prenez la fuite !");
		break;
	}
}

void texte(int action) {
	switch (action) {
	case 0:
		TEXTE.setString("Un Pok�mon sauvage appara�t !\n Que voulez-vous faire ?");
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

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

int checkPositionCompetence(sf::RenderWindow& window) {
	sf::Vector2i position = sf::Mouse::getPosition(window);

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

void gestionChoix(int& action, int competence, bool& combat, bool& joueurLance, Joueur& joueur, Pokemon& pokemonEnnemi) {
	//bool joueurJoue = true; // � changer en fonction de la vitesse du Pok�mon
	static string s = "";

	//cout << joueurLance << endl;
	switch (action) {
	case 0: 
		break;
	case 1:
		//Choix de la comp�tence
		if (competence != 4)
			joueur.getPokemon(0).attaquer(pokemonEnnemi, joueur.getPokemon(0).getCompetence(competence));
		break;
	case 2:
		//Soigner
		if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 2) {
			HORLOGE_CHOIX.restart();
			joueur.soin(0);
			action = 0;
		}
		break;
	case 3:
		//Pok�ball
		if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 2 && HORLOGE_CHOIX.getElapsedTime().asSeconds() < 4) {
			if (joueurLance == false) {
				joueurLance = true;
				s = joueur.pokeball(pokemonEnnemi);
			}
			TEXTE.setString(s);
		}
		else if (HORLOGE_CHOIX.getElapsedTime().asSeconds() > 4) {
			HORLOGE_CHOIX.restart();
			action = 0;
			if (s == "Capture reussie" || s == "Capture r�ussie, mais vous �tes d�j� complet en Pok�mon.")
				combat = false;
			HORLOGE_BUISSON.restart();
		}
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

void scalePv(Joueur& joueur, Pokemon& pokemonEnnemi) {
	float longueurJoueur = 5.32 * joueur.getPokemon(0).getPv()/joueur.getPokemon(0).getPvMax() ;
	float longueurEnnemi = 5.32 * pokemonEnnemi.getPv()/pokemonEnnemi.getPvMax() ;
	cout << longueurJoueur << " et " << longueurEnnemi << endl;
	PV_POKEMON_ALLIE.setScale(longueurJoueur*SCALE_L, SCALE_H);
	PV_POKEMON_ENNEMI.setScale(longueurEnnemi*SCALE_L, SCALE_H);
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
	Pokemon tabPokemonEnnemi[2];

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

	//Bool�en pour savoir si le joueur a boug�
	bool aBouge = true;

	//Bool�en pour savoir si le joueur a lanc� une pok�ball
	bool joueurLance = false;

	//Entier pour conna�tre l'action du joueur
	int action = 0; // 0. choix_action 1. competence 2. soin 3. pok�ball 4. fuir
	int competence = 0; // 0. competence1 1. competence2 2. competence3 3. competence4
		
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
					aBouge = true;
					vecteurDeplacement = sf::Vector2f(0, -.010);
				}
				else if (event.key.code == sf::Keyboard::Down) {
					aBouge = true;
					vecteurDeplacement = sf::Vector2f(0, .010);
				}
				else if (event.key.code == sf::Keyboard::Left) {
					aBouge = true;
					vecteurDeplacement = sf::Vector2f(-.010, 0);
				}
				else if (event.key.code == sf::Keyboard::Right) {
					aBouge = true;
					vecteurDeplacement = sf::Vector2f(.010, 0);
				}
				break;
			case sf::Event::KeyReleased:
				vecteurDeplacement = sf::Vector2f(0, 0);
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (action == 0) {
						HORLOGE_CHOIX.restart();
						action = checkPosition(window);
						joueurLance = false;
					}
					else {
						competence = checkPositionCompetence(window);
					}
				}
			}
		}

		if (combat) {
			//---------Code et affichage pour le combat--------
			aBouge = false;

			window.clear();

			//Affichage du fond de combat
			window.draw(FOND_COMBAT);

			//Loop sur les animations des pokemons
			joueur.loopPokemon();
			tabPokemonEnnemi[1].loop();
			//Affichage des pokemons
			window.draw(joueur.getPokemon(0).getSprite());
			window.draw(tabPokemonEnnemi[1].getSprite());
			
			//Affichage de l'HUD.
			hud(action);
			window.draw(HUD);

			//Gestion du combat
			gestionChoix(action, competence, combat, joueurLance,  joueur, tabPokemonEnnemi[1]);

			//Affichage du texte
			texte(action);
			window.draw(TEXTE);
			TEXTE_NOM_ALLIE.setString(joueur.getPokemon(0).getNom());
			TEXTE_NOM_ENNEMI.setString(tabPokemonEnnemi[1].getNom());
			window.draw(TEXTE_NOM_ALLIE);
			window.draw(TEXTE_NOM_ENNEMI);

			//Affichage des PV
			scalePv(joueur, tabPokemonEnnemi[1]);
			window.draw(PV_POKEMON_ALLIE);
			window.draw(PV_POKEMON_ENNEMI);

			//Gestion de la View
			gameView.setSize(window.getSize().x, window.getSize().y);
			gameView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
			window.setView(gameView);

			window.display();
		}
		else {
			//---------Code et affichage pour l'exploration--------
			
			//V�rifications des collisions et bordures puis d�placement du joueur.
			if (aBouge)
				combat = estSurCaseVerte(joueur);
			vecteurDeplacement = collisionsEtBordures(vecteurDeplacement, joueur);
			joueur.deplacement(vecteurDeplacement);

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
}








// Ancienne version, permet de m'inspirer

//	// Create the main window
//sf::RenderWindow window(sf::VideoMode(LARGEUR, HAUTEUR), "Pok�guez");
//
////Textures.
//sf::Texture pokemon;
//if (!pokemon.loadFromFile("Ressource/images/sprisheet_pokemons.png"))
//return EXIT_FAILURE;
//sf::Texture personnage;
//if (!personnage.loadFromFile("Ressource/images/sprisheet_personnage.png"))
//return EXIT_FAILURE;
//
////Sprite.
//sf::Sprite spriteAerodactyl(pokemon);
//sf::IntRect rectAerodactyl(0, 0, 100, 100);
//spriteAerodactyl.setTextureRect(rectAerodactyl);
//
//sf::Sprite spriteDimoret(pokemon);
//sf::IntRect rectDimoret(0, 100, 100, 100);
//spriteDimoret.setPosition(0, 100);
//spriteDimoret.setTextureRect(rectDimoret);
//
//sf::Sprite spritePerso(personnage);
//sf::IntRect rectPerso(0, 0, 32, 35);
//spritePerso.setPosition(450, 300);
//spritePerso.setOrigin(16, 17);
//spritePerso.setTextureRect(rectPerso);
//
//sf::Clock horlogeAnim;
//horlogeAnim.restart();
//
////Map.
//sf::Texture map;
//if (!map.loadFromFile("Ressource/images/map/map.png"))
//return EXIT_FAILURE;
//sf::Sprite spriteMap(map);
//
//sf::Image masque;
//if (!masque.loadFromFile("Ressource/images/map/masque.png"))
//return EXIT_FAILURE;
//
////Vue de la cam�ra.
//float zoom = 0.4f;
//sf::View gameView(sf::FloatRect(0, 0, LARGEUR, HAUTEUR));
//gameView.setSize(window.getSize().x * zoom, window.getSize().y * zoom);
//gameView.setCenter(spritePerso.getPosition());
//window.setView(gameView);
//
////
//
//const float minCameraX = gameView.getSize().x / 2.0f;
//const float minCameraY = gameView.getSize().y / 2.0f;
//const float maxCameraX = spriteMap.getGlobalBounds().width - minCameraX;
//const float maxCameraY = spriteMap.getGlobalBounds().height - minCameraY;
//
////Bool�en pour savoir si le personnage est en mouvement.
//bool persoIsMovingToUp = false;
//bool persoIsMovingToDown = false;
//bool persoIsMovingToLeft = false;
//bool persoIsMovingToRight = false;
//bool persoIsMoving = false;
//
////D�placement
//sf::Vector2f mvt(0, 0);
//sf::Vector2f pos(spritePerso.getPosition());
//
//// Create a graphical text to display
//sf::Font font;/*
//if (!font.loadFromFile("Ressource/font/arial.ttf"))
//	return EXIT_FAILURE;
//sf::Text text("Hello SFML", font, 50);*/
//
//// Load a music to play
//sf::Music music;
//if (!music.openFromFile("Ressource/musique/nice_music.mp3"))
//return EXIT_FAILURE;
//
//// Play the music
////music.play();
//sf::RectangleShape pixelTest;
//pixelTest.setSize(sf::Vector2f(10, 10));
//pixelTest.setFillColor(sf::Color::Red);
//// Start the game loop
//while (window.isOpen())
//{
//	// Process events
//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		persoIsMovingToUp = false;
//		persoIsMovingToDown = false;
//		persoIsMovingToLeft = false;
//		persoIsMovingToRight = false;
//		// Close window: exit
//		if (event.type == sf::Event::Closed)
//			window.close();
//		if (event.type == sf::Event::KeyPressed) {
//			if (event.key.code == sf::Keyboard::Up) {
//				persoIsMoving = true;
//				persoIsMovingToUp = true;
//				mvt = sf::Vector2f(0, -0.010);
//				rectPerso.top = 0;
//			}
//			else if (event.key.code == sf::Keyboard::Down) {
//				persoIsMoving = true;
//				persoIsMovingToDown = true;
//				mvt = sf::Vector2f(0, .010);
//				rectPerso.top = 35;
//			}
//			else if (event.key.code == sf::Keyboard::Left) {
//				persoIsMoving = true;
//				persoIsMovingToLeft = true;
//				mvt = sf::Vector2f(-.010, 0);
//				rectPerso.top = 70;
//			}
//			else if (event.key.code == sf::Keyboard::Right) {
//				persoIsMoving = true;
//				persoIsMovingToRight = true;
//				mvt = sf::Vector2f(.010, 0);
//				rectPerso.top = 105;
//			}
//		}
//		else if (event.type == sf::Event::KeyReleased) {
//			if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
//				mvt = sf::Vector2f(0, 0);
//				persoIsMoving = false;
//			}
//		}
//	}
//
//	// Clear screen
//	window.clear();
//
//	// Update the sprite
//	if (horlogeAnim.getElapsedTime().asSeconds() > .05f) {
//		rectAerodactyl.left += 100;
//		if (rectAerodactyl.left >= 2000)
//			rectAerodactyl.left = 0;
//		spriteAerodactyl.setTextureRect(rectAerodactyl);
//
//		rectDimoret.left += 100;
//		if (rectDimoret.left >= 1800)
//			rectDimoret.left = 0;
//		spriteDimoret.setTextureRect(rectDimoret);
//
//		if (!persoIsMoving) {
//			rectPerso.left = 0;
//			spritePerso.setTextureRect(rectPerso);
//		}
//		else {
//			rectPerso.left += 32;
//			if (rectPerso.left >= 96)
//				rectPerso.left = 0;
//			spritePerso.setTextureRect(rectPerso);
//		}
//
//		horlogeAnim.restart();
//	}
//
//	// Update the position of the sprite
//	sf::Vector2f playerCenterPosition(spritePerso.getPosition().x, spritePerso.getPosition().y);
//	sf::Vector2i nextPixelPosition(playerCenterPosition.x + mvt.x * 16 * 100, playerCenterPosition.y + mvt.y * 18 * 100);
//	int nextPixelColored = masque.getPixel(nextPixelPosition.x, nextPixelPosition.y).toInteger();
//	pixelTest.setPosition(nextPixelPosition.x, nextPixelPosition.y);
//
//
//	if (nextPixelColored == 255) {
//		cout << "Collision en : " << playerCenterPosition.x << ";" << playerCenterPosition.y << endl;
//		mvt = sf::Vector2f(0, 0);
//	}
//
//	spritePerso.move(mvt);
//
//	// Update the view
//
//	float newCameraX = min(max(minCameraX, spritePerso.getPosition().x), maxCameraX);
//	float newCameraY = min(max(minCameraY, spritePerso.getPosition().y), maxCameraY);
//
//	gameView.setCenter(newCameraX, newCameraY);
//	window.setView(gameView);
//
//	// Draw the sprite
//	window.draw(spriteMap);
//	window.draw(spriteAerodactyl);
//	window.draw(spriteDimoret);
//	window.draw(spritePerso);
//	window.draw(pixelTest);
//
//	// Update the window
//	window.display();
//}
//
//return EXIT_SUCCESS;