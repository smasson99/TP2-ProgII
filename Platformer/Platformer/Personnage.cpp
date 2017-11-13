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
    jumpTime = seconds(MAX_JUMP_TIME);
    clock.restart();
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

    //On regarde à droite en commençant
    lookLeft = false;
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

// <SBerube>
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

    // Ici, on vérifie la collision entre le joueur et chaque tuile du jeu qui n'est pas vide.
    /*for (size_t i = 0; i < 20; i++)
    {
        for (size_t j = 0; j < 15; j++)
        {
            if (SceneNiveau1::GetGrilleAt(i, j) != nullptr)
            {
                if (SceneNiveau1::GetGrilleAt(i, j)->getTextureRect().intersects(animator.GetCurAnimRect()))
                {
                    collision = true;
                    if (direction == 2)
                    {
                        isOnGround = true;
                    }
                    else if (direction == -2)
                    {
                        isJumping = false;
                    }

                }
            }
        }
    }*/
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
    //// </smasson>

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
    Sprite::move(0, 1 * GRAVITY_FORCE);
}

void Personnage::moveUp()
{
    Sprite::move(0, -1 * JUMP_FORCE);
}

bool Personnage::IsJumping()
{
    return isJumping;
}


void Personnage::Jump()
{
    isJumping = true;
    //clock.restart();
}

void Personnage::Update()
{
    // <smasson>
    //Updater l'animateur
    animator.Update();
    //Updater la texture
    setTexture(animator.GetCurAnimTexture());
    setTextureRect(animator.GetCurAnimRect());

    //jupsection
    if (isJumping && jumpTime.asSeconds() < clock.getElapsedTime().asSeconds())
    {
        isJumping = false;
        clock.restart();
    }
    // </smasson>
}
void Personnage::Gravite()
{
    //if (gravityTimer.getElapsedTime() > gravityTick)
    //{
    //	//if(!isJumping)
    //	//	move(2); // On fait descendre le personnage
    //	gravityTimer.restart();
    //}
}

// </SBerube>