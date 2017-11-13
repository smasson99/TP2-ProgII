// <SBerube>
#include "Collectible.h"
Collectible::Collectible() : enabled(false)
{
}
Collectible::Collectible(Sprite sprite) : sprite(sprite), enabled(false)
{
}

Vector2f Collectible::getPosition() { return sprite.getPosition(); }
void Collectible::setPosition(Vector2f position) { sprite.setPosition(position); }
void Collectible::Draw(RenderWindow &win) { win.draw(sprite); }
bool Collectible::IsEnabled() { return enabled; }
void Collectible::Enable() { enabled = true; }
void Collectible::Disable() { enabled = false; }
FloatRect Collectible::getIntrect() { return sprite.getGlobalBounds(); }
// </SBerube>