// <SBerube>
#include "Collectible.h"
Collectible::Collectible(Sprite sprite) : sprite(sprite)
{
}

Vector2f Collectible::getPosition() { return sprite.getPosition(); }
void Collectible::setPosition(Vector2f position) { sprite.setPosition(position); }
void Collectible::Draw(RenderWindow win) { win.draw(sprite); }
// </SBerube>