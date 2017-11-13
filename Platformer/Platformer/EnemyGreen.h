#pragma once
#include "BasicEnemy.h"

namespace platformer
{
    class EnemyGreen :public BasicEnemy
    {
    public:
        EnemyGreen(Spawner& spawner);
        ~EnemyGreen();
    private:
    };
}