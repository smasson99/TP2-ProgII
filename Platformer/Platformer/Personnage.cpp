//#include "Joueur.h"
#include "SceneNiveau1.h"
#include <iostream> // Debbogage

using namespace platformer;

// <smasson>
/*
    Notes:
    *Je vais temporairement rendre inactive les animations, pour pouvoir me concentrer sur les collisions

    Animations:
        1-Le joueur s'anime aux mouvements
        status:inactif
    Collisions:
        1-Le joueur doit ne pas sortir de l'écran
        status:actif
        2-Le joueur doit ne pas traverser les blocs
        status:non
*/
// </smasson>

Personnage::Personnage() : persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
    time = seconds(MAX_JUMP_TIME);
    clock.restart();

    dir.x = 0;
    dir.y = 1;
}

Personnage::~Personnage()
{
}

bool Personnage::Init(const int limiteGauche, const int limiteDroite, const String walkAnimPath, const String idleAnimPath)
{
    // <smasson>
    //Temporaire, retirer au rajout des anims:
    if (!texture.loadFromFile(walkAnimPath))
    {
        return false;
    }
    //

    if (!runAnimTexture.loadFromFile(walkAnimPath))
    {
        return false;
    }
    if (!idleAnimTexture.loadFromFile(idleAnimPath))
    {
        return false;
    }

    /*Ici, l'ordre d'appel est important et est dépendant de l'enum: Animations*/
    /*IDLE = 0, RUN_LEFT = 1, RUN_RIGHT= 2, JUMP = 3, DIE = 4*/

    animator.AddAnim(idleAnimTexture);
    animator.AddAnim(runAnimTexture);
    animator.AddAnim(runAnimTexture);

    //On regarde à gauche en commençant
    lookLeft = true;
    //On start l'IDLE
    /*Il faut user de cette fonction pour démarrer, autrement nous assisterons à une crise d'épilepsie*/
    animator.InitAnim(IDLE, 0.3f);
    /*Nous setons la texture de base avec son rect*/
    setTexture(animator.GetCurAnimTexture());
    setTextureRect(animator.GetCurAnimRect());
    /*Setter l'origine (très important)*/
    setOrigin(animator.GetCurAnimRect().width / 2, animator.GetCurAnimRect().height / 2);
    //Temporaire, enlever au rajout des anims
    setTexture(texture);
    setTextureRect(persoRect);
    // </smasson>

    this->limiteGauche = limiteGauche + TAILLE_RECT / 4;
    this->limiteDroite = limiteDroite - TAILLE_RECT / 4;

    return true;
}

void Personnage::move(const int direction)
{
    bool collision = false;
    Vector2f oldPosition = getPosition();

    // On fait d'abbord bouger le personnage pour savoir si c'est possible
    // Droite
    if (direction == 1)
    {
        Sprite::move(vitesse / 4.0f, 0);
    }
    // Gauche
    else if (direction == -1)
    {
        Sprite::move(-vitesse / 4.0f, 0);
    }

    if (direction == 1)
    {
        // <smasson>
        /*Jouer à droite(anim)*/
        animator.PlayAnim(RUN_RIGHT, 0.1f);
        lookLeft = false;
        // </smasson>
    }
    // Gauche
    else if (direction == -1)
    {
        // <smasson>
        /*Jouer à gauche(anim)*/
        animator.PlayAnim(RUN_LEFT, 0.1f);
        lookLeft = true;
        // </smasson>
    }
    // <smasson>
    /*Sinon, nous ne bougeons pas, donc aller en Idle*/
    else
    {
        /*Jouer l'IDLE*/
        animator.PlayAnim(IDLE, 0.3f);
    }
    // </smasson>

    // <smasson>
    /*Updater la direction de look*/
    if (lookLeft)
        setScale(SCALE_X*-1, SCALE_Y);
    else
        setScale(SCALE_X, SCALE_Y);

    //Pour s'assurer de ne pas dépasser les limites de l'écran
    if (getPosition().x < limiteGauche)
    {
        setPosition(limiteGauche, getPosition().y);
    }
    else if (getPosition().x > limiteDroite)
    {
        setPosition(limiteDroite, getPosition().y);
    }
    // </smasson>
}

void Personnage::moveDown()
{
    Sprite::move(dir.x, dir.y * GRAVITY_FORCE);
}

void Personnage::moveUp()
{
    Sprite::move(dir.x, -dir.y * JUMP_FORCE);
}

void Personnage::Jump()
{
    canJump = false;
    isJumping = true;
    dir.x = 0;
    dir.y = 1;
    clock.restart();
}

void platformer::Personnage::Jump(bool right)
{
    canJump = false;
    isJumping = true;
    //Droite
    if (right)
    {
        dir.x = cos(45);
        dir.y = sin(45);
    }
    //Gauche
    else
    {
        dir.x = -cos(45);
        dir.y = sin(45);
    }
    clock.restart();
}

void platformer::Personnage::Update()
{
    //Updater l'animateur
    animator.Update();
    //Updater la texture
    setTexture(animator.GetCurAnimTexture());
    setTextureRect(animator.GetCurAnimRect());
}

// <smasson>

bool platformer::Personnage::CheckCollisions(const Direction dir, Sprite*(*tab)[15])
{
    bool collides = false;
    //Pour chaque tuile en x et en y
    for (size_t x = 0; x < SceneNiveau1::NOMBRE_TUILES_X; ++x)
    {
        for (size_t y = 0; y < SceneNiveau1::NOMBRE_TUILES_Y; ++y)
        {
            //Si nous n'allons pas vers le bas et que nous n'allons pas vers le haut
            if (dir != HAUT && dir != BAS)
            {
                //S'il y a une tuile
                if (tab[x][y] != nullptr)
                {
                    switch (dir)
                    {
                    case DROITE:
                        if (tab[x][y]->getGlobalBounds().intersects(getGlobalBounds()) && tab[x][y]->getPosition().y < getPosition().y && 
                            tab[x][y]->getPosition().x > getPosition().x)
                        {
                            //Visuel temporaire
                            tab[x][y]->setColor(Color::Black);
                            collides = true;
                        }
                        //Pas de collision
                        else
                            tab[x][y]->setColor(Color::White);
                        break;

                    case GAUCHE:
                        if (tab[x][y]->getGlobalBounds().intersects(getGlobalBounds()) && tab[x][y]->getPosition().y < getPosition().y &&
                            tab[x][y]->getPosition().x < getPosition().x)
                        {
                            //Visuel temporaire
                            tab[x][y]->setColor(Color::Black);
                            collides = true;
                        }
                        //Pas de collision
                        else
                            tab[x][y]->setColor(Color::White);
                        break;
                    }
                }
            }
            //Sinon, nous allons vers le bas ou vers le haut
            else
            {
                if (tab[x][y] != nullptr)
                {
                    if (dir == BAS)
                    {
                        //S'il y a collision
                        if (tab[x][y]->getGlobalBounds().intersects(getGlobalBounds()) && tab[x][y]->getPosition().y > getPosition().y
                            && y + 1 <= 15 && tab[x][y + 1] == nullptr)
                        {
                            tab[x][y]->setColor(Color::Black);
                            collides = true;
                        }
                        else
                        {
                            tab[x][y]->setColor(Color::White);
                        }
                    }
                    else if (dir == HAUT)
                    {
                        //S'il y a collision
                        if (tab[x][y]->getGlobalBounds().intersects(getGlobalBounds()) && tab[x][y]->getPosition().y < getPosition().y
                            && y - 1 >= 0 && tab[x][y - 1] == nullptr)
                        {
                            tab[x][y]->setColor(Color::Black);
                            collides = true;
                        }
                        else
                            tab[x][y]->setColor(Color::White);
                    }
                }
            }
        }
    }
    return collides;
}

// </smasson>

// </SBerube>