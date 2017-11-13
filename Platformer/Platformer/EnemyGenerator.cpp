#include "EnemyGenerator.h"
#include "EnemyGreen.h"

Spawner* EnemyGenerator::spawner = nullptr;
int EnemyGenerator::limiteGauche = 0;
int EnemyGenerator::limiteDroite = 0;
string EnemyGenerator::walk = "";
string EnemyGenerator::idle = "";

void EnemyGenerator::LoadData(Spawner* spawner, const int limiteGauche, const int limiteDroite, const String walkAnimPath, const String idleAnimPath)
{
    EnemyGenerator::spawner = spawner;
    EnemyGenerator::limiteGauche = limiteGauche;
    EnemyGenerator::limiteDroite = limiteDroite;
    EnemyGenerator::walk = walkAnimPath;
    EnemyGenerator::idle = idleAnimPath;
}

BasicEnemy* EnemyGenerator::Generate(EnemyType type)
{
    BasicEnemy* res;
    /*switch (type)
    {
    case GREEN_ENEMY:
        res = &EnemyGreen(*spawner);
        break;
    case YELLOW_ENEMY:
        res = &BasicEnemy(*spawner);
        break;
    case ORANGE_ENEMY:
        res = &BasicEnemy(*spawner);
        break;
    }*/
    res->InitInfos();
    return res;

    /*Probl�me: impossibilit� d'utiliser la fabrique, car la classe d'animations ne semble
    pas aimer les textures statiques. Pour �viter un perte de temps et puisequ'il nous reste
    seulement quelques heures, nous allons ignorer ce crit�re. Voici tout de m�me le code.*/
}
