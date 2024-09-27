#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int HAUTEUR = 720;
int LARGEUR = 1280;

int main()
{

}








// Ancienne version, permet de m'inspirer

//	// Create the main window
//sf::RenderWindow window(sf::VideoMode(LARGEUR, HAUTEUR), "Pokéguez");
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
////Vue de la caméra.
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
////Booléen pour savoir si le personnage est en mouvement.
//bool persoIsMovingToUp = false;
//bool persoIsMovingToDown = false;
//bool persoIsMovingToLeft = false;
//bool persoIsMovingToRight = false;
//bool persoIsMoving = false;
//
////Déplacement
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