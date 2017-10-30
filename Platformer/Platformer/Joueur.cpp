#include "Joueur.h"
#include <iostream>

using namespace platformer;

Joueur::Joueur() : persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
}

Joueur::~Joueur()
{
}

bool Joueur::Init(const int limiteGauche, const int limiteDroite, const String texturePath, const String runAnimPath, const String idleAnimPath)
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}
    // <smasson>
    if (!runAnimTexture.loadFromFile(runAnimPath))
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
    /*animator.AddAnim(idleAnimTexture);
    animator.AddAnim(runAnimTexture);
    animator.AddAnim(runAnimTexture);*/
    // </smasson>

	setTexture(texture);
	setTextureRect(persoRect);
	setOrigin(TAILLE_RECT / 2, TAILLE_RECT /2);

	this->limiteGauche = limiteGauche + TAILLE_RECT / 4;
	this->limiteDroite = limiteDroite - TAILLE_RECT / 4;
	isOnGround = true;
	isJumping = false;

	jumpTime = milliseconds(1400);

	return true;
}

void Joueur::move(const int direction)
{
	// Droite
	if (direction == 1)
	{
		Sprite::move(vitesse, 0);
        // <smasson>
        /*Jouer à droite(anim)*/
        /*animator.PlayAnim(RUN_RIGHT, 0.09f);
        setScale(-1, 1);*/
        // </smasson>
	}
	// Gauche
	else if (direction == -1)
	{
		Sprite::move(-vitesse, 0);
        // <smasson>
        /*Jouer à gauche(anim)*/
        /*animator.PlayAnim(RUN_LEFT, 0.09f);
        setScale(1, 1);*/
        // </smasson>
	}
	// Bas
	else if(direction == 2)
	{
		Sprite::move(0, 3);
	}
	// Haut
	else if (direction == -2)
	{
		Sprite::move(0, -2);
	}

    // <smasson>

    /*Sinon, nous ne bougeons pas, donc aller en Idle*/
    else
    {
        /*Jouer l'IDLE*/
        /*animator.PlayAnim(IDLE, 0.0f);*/
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
}

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
    //animator.Update();
    //Updater la texture
    //setTexture(animator.GetCurAnimTexture());
    //setTextureRect(animator.GetCurAnimRect());
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
			//isJumping = false;
		}
	}
	else if (!isOnGround)
	{
		Gravite();
	}
}

void Joueur::Gravite()
{
	if (gravityTimer.getElapsedTime() > gravityTime)
	{
		move(2); // On fait descendre le personnage
		gravityTimer.restart();
	}
}