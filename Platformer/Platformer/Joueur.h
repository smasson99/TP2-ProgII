#pragma once
// <smasson>
#include "Personnage.h"

namespace platformer
{
    class Joueur : public Personnage
    {
    public:
        static Joueur* GetInstance();
        ~Joueur();
        //bool Init(const int limiteGauche, const int limiteDroite, const String walkAnimPath, const String idleAnimPath);
        void Update(int command, Sprite*(*tab)[15]);
    private:
        Joueur();
        bool CheckCollisions(const int command, const Direction dir, Sprite*(*tab)[15]);
        static Joueur* instance;
    };
}
// </smasson>