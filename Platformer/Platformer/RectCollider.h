#pragma once
// <SBerube>
#include <SFML/Graphics.hpp>
using namespace sf;
class RectCollider
{
public:
	RectCollider();
	RectCollider(Vector2f upLeftLimit, Vector2f downRightLimit);
	bool CollidesWith(RectCollider collider);
	bool CollidesWith(Vector2f upLeftLimit, Vector2f downRightLimit);
	void setLimits(Vector2f upLeft, Vector2f downRight);
	Vector2f GetUpLeftLimit();
	Vector2f GetDownRightLimit();
private:
	Vector2f upLeftLimit;
	Vector2f downRightLimit;
};
// </SBerube>