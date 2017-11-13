#pragma once
// <SBerube>
#include <SFML\Graphics.hpp>
using namespace sf;
class Collectible
{
public:
	Collectible();
	// Constructeur pour le flyweight
	Collectible(Sprite sprite);
	// Méthodes get / set de la position
	Vector2f getPosition();
	void setPosition(Vector2f position);
	// permet de dessiner l'objet à l'écran
	void Draw(RenderWindow &win);
	// Les méthodes get / set pour l'activation de l'objet
	bool IsEnabled();
	void Enable();
	void Disable();
	// Méthode pour les collisions
	FloatRect getIntrect();
private:
	// Le visuel du collectible en flyweight
	Sprite sprite;
	// La condition d'apparition dans le jeu
	bool enabled;
};
// </SBerube>