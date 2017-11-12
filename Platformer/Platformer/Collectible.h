#pragma once
// <SBerube>
#include <SFML\Graphics.hpp>
using namespace sf;
class Collectible
{
public:
	// Constructeur pour le flyweight
	Collectible(Sprite sprite);
	// M�thodes get / set de la position
	Vector2f getPosition();
	void setPosition(Vector2f position);
	void Draw(RenderWindow win);
private:
	// Le visuel du collectible en flyweight
	Sprite sprite;

};
// </SBerube>