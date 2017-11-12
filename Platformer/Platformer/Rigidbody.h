#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

namespace platformer
{
    class Rigidbody :public Sprite
    {
    public:
        Rigidbody();
        void Move(const bool up);
    };
}