#include "Rigidbody.h"

using namespace platformer;

platformer::Rigidbody::Rigidbody()
{
    
}

void platformer::Rigidbody::Move(const bool up)
{
    if (up)
        Sprite::move(0, 1);
    else
        Sprite::move(0, 1);
}

