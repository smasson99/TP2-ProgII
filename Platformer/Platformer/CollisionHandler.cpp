// <smasson>
#include "CollisionHandler.h"

using namespace platformer;

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{

}

CollisionHandler* CollisionHandler::instance = nullptr;

CollisionHandler* CollisionHandler::GetInstance()
{
    if (instance == nullptr)
        instance = new CollisionHandler();
    return instance;
}

bool CollisionHandler::IsColliding(Sprite* sprite1, Sprite* sprite2)
{
    return sprite1->getTextureRect().intersects(sprite2->getTextureRect());
}

bool platformer::CollisionHandler::IsColliding(Sprite* sprite, Sprite * tabSprites, int length)
{
    for (int i = 0; i < length; ++i)
    {
        if (tabSprites[i].getTextureRect().intersects(sprite->getTextureRect()))
        {
            return true;
        }
    }
    return false;
}

bool CollisionHandler::IsColliding(Sprite* sprite, Sprite** tab2DSprites, int width, int height)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (tab2DSprites[i][j].getTextureRect().intersects(sprite->getTextureRect()))
            {
                return true;
            }
        }
    }
    return false;
}
// </smasson>