#pragma once
#include "BasicEnemy.h"
#include "Spawner.h"

namespace platformer
{
    class EnemyGenerator
    {
    public:
        static enum EnemyType
        {
            GREEN_ENEMY,
            YELLOW_ENEMY,
            ORANGE_ENEMY
        };
        static void LoadData(Spawner* spawner, const int limiteGauche, const int limiteDroite, const String walkAnimPath, const String idleAnimPath);
        static BasicEnemy* Generate(EnemyType type);
    private:
        static Spawner* spawner;
        static int limiteGauche;
        static int limiteDroite;
        static string walk;
        static string idle;
        
    };
}