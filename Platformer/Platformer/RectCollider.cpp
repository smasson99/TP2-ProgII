#pragma once
// <SBerube>
#include "RectCollider.h"
RectCollider::RectCollider()
{
	upLeftLimit = Vector2f(0, 0);
	downRightLimit = Vector2f(0, 0);
}
RectCollider::RectCollider(Vector2f upLeftLimit, Vector2f downRightLimit)
{
	this->upLeftLimit = upLeftLimit;
	this->downRightLimit = downRightLimit;
}
bool RectCollider::CollidesWith(RectCollider collider)
{
	// Collision tests

	    // Si le collider est en bas				    OU en haut
	if (downRightLimit.y <= collider.GetUpLeftLimit().y || upLeftLimit.y >= collider.GetDownRightLimit().y) return false; // Il n'a pas de collision
		// Si le collider est a droite                  OU a gauche
	if (downRightLimit.x <= collider.GetUpLeftLimit().x || upLeftLimit.x >= collider.GetDownRightLimit().x) return false; // Il n'a pas de collision

	return true;
}
void RectCollider::setLimits(Vector2f upLeft, Vector2f downRight)
{
	upLeftLimit = upLeft;
	downRightLimit = downRight;
}

Vector2f RectCollider::GetUpLeftLimit() { return upLeftLimit; }
Vector2f RectCollider::GetDownRightLimit() { return downRightLimit; }

bool RectCollider::CollidesWith(Vector2f upLeftLimit, Vector2f downRightLimit)
{
	RectCollider collider;
	collider.setLimits(upLeftLimit, downRightLimit);
	return this->CollidesWith(collider);
}
// </SBerube>