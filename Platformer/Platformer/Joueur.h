#pragma once
// <smasson>
#include "Personnage.h"

namespace platformer
{
    class Joueur : public Personnage
    {
    public:
        Joueur();
        ~Joueur();
        void Update(int command, Sprite*(*tab)[15]);
    private:
        bool CheckCollisions(const int command, const Direction dir, Sprite*(*tab)[15]);
    };
}
// </smasson>