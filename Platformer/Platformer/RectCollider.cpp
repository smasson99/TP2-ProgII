#pragma once
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
	//float width1 = downRightLimit.x - upLeftLimit.x;
	//float width2 = collider.GetDownRightLimit().x - collider.GetUpLeftLimit().x;
	//float height1 = downRightLimit.y - upLeftLimit.y;
	//float height2 = collider.GetDownRightLimit().y - collider.GetUpLeftLimit().y;
	if (upLeftLimit.x > collider.GetUpLeftLimit().x && 
		upLeftLimit.x < collider.GetDownRightLimit().x &&
		downRightLimit.y > collider.GetUpLeftLimit().y &&
		downRightLimit.y < collider.GetDownRightLimit().y)
	{
		return true;
	}
	return false;
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