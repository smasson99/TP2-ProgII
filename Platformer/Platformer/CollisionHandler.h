#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

namespace platformer
{
    class CollisionHandler
    {
    public:
        static CollisionHandler* GetInstance();
        bool IsColliding(Sprite* sprite1, Sprite* sprite2);
        bool IsColliding(Sprite* sprite, Sprite* tabSprites, const int length);
        bool IsColliding(Sprite* sprite, Sprite** tab2DSprites, const int width, const int height);
    private:
        CollisionHandler();
        ~CollisionHandler();
        static CollisionHandler* instance;
    };
}
