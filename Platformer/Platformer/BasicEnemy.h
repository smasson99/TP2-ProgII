#pragma once
#include "Personnage.h"
#include "Spawner.h"
#include <random>

namespace platformer
{
    class BasicEnemy : public Personnage
    {
    public:
        BasicEnemy();
        ~BasicEnemy();
        void InitInfos();
        void SetActif(bool isActive);
        bool isActive();
        void Update(Sprite *(*tab)[15]);
        void Patrol();
        void Spawn();
    protected:
        Spawner* spawner;

        bool noPatrol = true;
        bool targetAcquired = false;

        const float MIN_PATROL_TIME = 0.9f;
        const float MAX_PATROL_TIME = 4.5f;

        default_random_engine randEngine;

        Time patrolTime;
        Clock clockPatrol;

        int patrolIndex = 0;
        Vector2f destination;

        static Texture textureIdle;
        static Texture textureWalk;
    private:
        void GenPatrolTime();
        bool PosIsRightFromMe(Vector2f pos);
        bool IsAtCurPatrol();
        bool checkPoint = false;
        bool active;
    };
}