#include "Joueur.h"
#include <iostream>

using namespace platformer;

Joueur::Joueur() : persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
	isOnGround = true;
	isJumping = false;
	jumpTime = milliseconds(500);
	gravityTick = milliseconds(10);
}

Joueur::~Joueur()
{
}

bool Joueur::Init(const int limiteGauche, const int limiteDroite, const String walkAnimPath, const String idleAnimPath)
{
    // <smasson>
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
    /*//*/
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
    // </smasson>

	// <SBerube>
	collider = RectCollider(Vector2f(getPosition().x, getPosition().y), Vector2f(getPosition().x + texture.getSize().x, getPosition().y + texture.getSize().y));
	// </SBerube>
	this->limiteGauche = limiteGauche + TAILLE_RECT / 4;
	this->limiteDroite = limiteDroite - TAILLE_RECT / 4;

	return true;
}

void Joueur::move(const int direction)
{
	// Droite
	if (direction == 1)
	{
		Sprite::move(vitesse/2, 0);
        // <smasson>
        /*Jouer à droite(anim)*/
        animator.PlayAnim(RUN_RIGHT, 0.18f);
        lookLeft = false;
        // </smasson>
	}
	// Gauche
	else if (direction == -1)
	{
		Sprite::move(-vitesse/2, 0);
        // <smasson>
        /*Jouer à gauche(anim)*/
        animator.PlayAnim(RUN_LEFT, 0.18f);
        lookLeft = true;
        // </smasson>
	}
	// <SBerube>
	// Bas
	else if(direction == 2)
	{
		Sprite::move(0, 1);
	}
	// Haut
	else if (direction == -2)
	{
		Sprite::move(0, -1.5);
	}
	// </SBerube>
    // <smasson>

    /*Sinon, nous ne bougeons pas, donc aller en Idle*/
    else
    {
        /*Jouer l'IDLE*/
        animator.PlayAnim(IDLE, 0.3f);
    }
    // </smasson>

	//Test sur les limites de l'écran
	if (getPosition().x < limiteGauche)
	{
		setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x > limiteDroite)
	{
		setPosition(limiteDroite, getPosition().y);
	}
    // <smasson>
    /*Updater la direction de look*/
    if (lookLeft)
        setScale(SCALE_X*-1, SCALE_Y);
    else
        setScale(SCALE_X, SCALE_Y);
    // </smasson>
}
// <SBerube>
void Joueur::Jump()
{
	if (isOnGround)
	{
		isJumping = true;
		timerAfterJump.restart();
	}
}

void Joueur::Update()
{
    // <smasson>
    //Updater l'animateur
    animator.Update();
    //Updater la texture
    setTexture(animator.GetCurAnimTexture());
    setTextureRect(animator.GetCurAnimRect());
    // </smasson>

	if (isJumping)
	{
		auto a = timerAfterJump.getElapsedTime();
		if (timerAfterJump.getElapsedTime() < jumpTime)
		{
			std::cout << timerAfterJump.getElapsedTime().asMilliseconds() << " " << jumpTime.asMilliseconds() << std::endl;
			move(-2); // On fait monter le personnage
		}
		else
		{
			isJumping = false;
		}
	}
	else if (!isOnGround)
	{
		Gravite();
	}
}
void Joueur::Gravite()
{
	if (gravityTimer.getElapsedTime() > gravityTick)
	{
		move(2); // On fait descendre le personnage
		gravityTimer.restart();
	}
}
// </SBerube>