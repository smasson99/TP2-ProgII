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
	// M�thodes get / set de la position
	Vector2f getPosition();
	void setPosition(Vector2f position);
	// permet de dessiner l'objet � l'�cran
	void Draw(RenderWindow &win);
	// Les m�thodes get / set pour l'activation de l'objet
	bool IsEnabled();
	void Enable();
	void Disable();
	// M�thode pour les collisions
	FloatRect getIntrect();
private:
	// Le visuel du collectible en flyweight
	Sprite sprite;
	// La condition d'apparition dans le jeu
	bool enabled;
};
// </SBerube>