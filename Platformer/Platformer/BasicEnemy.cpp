#include "BasicEnemy.h"
#include <iostream>

using namespace platformer;

BasicEnemy::BasicEnemy()
{
    //this->spawner = &spawner;
}

platformer::BasicEnemy::~BasicEnemy()
{
}

void platformer::BasicEnemy::InitInfos()
{
    //Ici, on vérifie qu'il y a des points de patrouille ou non
    noPatrol = (spawner->GetPatrolCoords().size() == 0);
    //Initialiser la destination
    if (!noPatrol)
    {
        std::cout << "Pas de patrouilles" << std::endl;
        //Générer un temp de patrouille
        GenPatrolTime();
        //Index de base
        patrolIndex = 0;
        //Seter la destination initiale
        destination = spawner->GetPatrolCoords().at(patrolIndex);
    }
    //Sinon, pas de patrouille, alors reser au spawner;
    else
    {
        std::cout << "Il y a des patrouilles" << std::endl;
        destination = spawner->GetPosition();
    }

    //Inactif par défaut
    active = false;
}

void platformer::BasicEnemy::SetActif(bool isActive)
{
    active = isActive;
}

bool platformer::BasicEnemy::isActive()
{
    return active;
}

void platformer::BasicEnemy::Update(Sprite *(*tab)[15])
{
    Vector2f lastPos = getPosition();
    Direction dir = NONE;
    //S'il y a des points de patrouille et qu'aucune cible n'est trouvée
    if (!noPatrol && !targetAcquired)
    {
        //Si le temps de patrouille au point est dépassé et que nous sommes au point de destination
        if (checkPoint && patrolTime.asSeconds() < clockPatrol.getElapsedTime().asSeconds())
        {
            //CheckPoint
            checkPoint = false;
            //Reset du temps du timer
            GenPatrolTime();
            //Relancer l'horloge
            clockPatrol.restart();
        }
        //Sinon, alors nous sommes encore en mouvement
        else
        {
            //Si nous avons atteint la destination
            if (!checkPoint && getPosition().x < spawner->GetPatrolCoords().at(patrolIndex).x+5 && 
                spawner->GetPatrolCoords().at(patrolIndex).x -5 < getPosition().x)
            {
                //CheckPoint
                checkPoint = true;
                //Changer destination
                Patrol();
                //Idle
                move(0);
                dir = NONE;
                //Lancer le timer
                clockPatrol.restart();
            }
            //Sinon, si la position cherchée est à droite 
            else if (!checkPoint && PosIsRightFromMe(spawner->GetPatrolCoords().at(patrolIndex)))
            {
                //Bouger vers la droite
                move(1);
                dir = DROITE;
            }
            //Sinon, elle est à gauche
            else if (!checkPoint)
            {
                //Bouger vers la gauche
                move(-1);
                dir = GAUCHE;
            }
            else
                move(0);
        }
    }
    //Sinon, rien ne se passe alors IDLE
    else
        move(0);

    //Update de l'animation en fonction des mouvements
    Personnage::Update();

    //S'il y a collision pour les déplacements gauche-droite
    if (CheckCollisions(dir, tab))
    {
        setPosition(Vector2f(lastPos));
    }

    //Updater lastPos
    lastPos = Vector2f(getPosition());
    //Updater déplacements liés à la gravité
    if (!isJumping)
    {
        if (!CheckCollisions(BAS, tab))
        {
            moveDown();
        }
        else
            canJump = true;
    }
    else
    {
        if (!CheckCollisions(HAUT, tab))
        {
            moveUp();
        }
        else
            isJumping = false;
    }
}

void platformer::BasicEnemy::Patrol()
{
    //Incrémentation de l'index de patrouille, s'assurer de ne pas dépasser
    if (patrolIndex + 1 < spawner->GetPatrolCoords().size())
        ++patrolIndex;
    else
        patrolIndex = 0;
    //Updater la destination
    destination = spawner->GetPatrolCoords().at(patrolIndex);
}

void BasicEnemy::Spawn()
{
    setPosition(spawner->GetPosition().x, spawner->GetPosition().y);
}

void platformer::BasicEnemy::GenPatrolTime()
{
    std::uniform_real_distribution<float> newTime(MIN_PATROL_TIME, MAX_PATROL_TIME);
    patrolTime = seconds(newTime(randEngine));
}

bool platformer::BasicEnemy::PosIsRightFromMe(Vector2f pos)
{
    return (pos.x > Personnage::getPosition().x);
}

bool platformer::BasicEnemy::IsAtCurPatrol()
{
    return Personnage::getPosition().x == spawner->GetPatrolCoords().at(patrolIndex).x;
}


