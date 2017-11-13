// <smasson>
#include "Joueur.h"
#include "SceneNiveau1.h"

using namespace platformer;

Joueur* Joueur::instance = nullptr;

platformer::Joueur::Joueur()
{
    
}

platformer::Joueur::~Joueur()
{
}

Joueur* platformer::Joueur::GetInstance()
{
    if (instance == nullptr)
        instance = new Joueur();
    return instance;
}

void Joueur::Update(int command, Sprite *(*tab)[15])
{
    Direction curMoveDir;
    Vector2f lastPos = getPosition();

    //Player seulement
    //Gauche
    if (command == 1 || command == 5)
    {
        curMoveDir = GAUCHE;
        move(-1);
    }
    //Droite
    else if (command == 2 || command == 6)
    {
        curMoveDir = DROITE;
        move(1);
    }
    //None (IDLE)
    else
    {
        curMoveDir = NONE;
        move(0);
    }
    //Jump
    if (command & 4 && canJump)
    {
        //Droite-Diagonale
        if (command == 2 || command == 6)
        {
            Jump(true);
        }
        //Gauche-Diagonale
        else if (command == 1 || command == 5)
        {
            Jump(false);
        }
        else
            Jump();
    }

    //Update dans la super-classe
    Personnage::Update();

    //S'il y a collision pour les déplacements gauche-droite
    if (CheckCollisions(command, curMoveDir, tab))
    {
        setPosition(Vector2f(lastPos));
    }

    //Updater lastPos
    lastPos = Vector2f(getPosition());
    //Updater déplacements liés à la gravité
    if (!isJumping)
    {
        if (!CheckCollisions(command, BAS, tab))
        {
            moveDown();
        }
        else
            canJump = true;
    }
    else
    {
        if (!CheckCollisions(command, HAUT, tab))
        {
            moveUp();
        }
        else
            isJumping = false;
    }
    if (colLeftOnlyWJump || colRightOnlyWJump)
    {
        setPosition(lastPos.x, getPosition().y);
        colLeftOnlyWJump = false;
        colRightOnlyWJump = false;
    }
    if (isJumping && clock.getElapsedTime().asSeconds() >= time.asSeconds())
    {
        isJumping = false;
        clock.restart();
    }
}

bool Joueur::CheckCollisions(const int command, const Direction dir, Sprite*(*tab)[15])
{
    bool collides = Personnage::CheckCollisions(dir, tab);
    if (collides == false && (dir == HAUT || dir == BAS))
    {
        //Droite-Diagonale
        if (command == 2 || command == 6)
        {
            colRightOnlyWJump = CheckCollisions(command, DROITE, tab);
        }
        //Gauche-Diagonale
        else if (command == 1 || command == 5)
        {
            colLeftOnlyWJump = CheckCollisions(command, GAUCHE, tab);
        }
    }
    return collides;
}
// </smasson>