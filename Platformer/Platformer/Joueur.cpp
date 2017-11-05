//#include "Joueur.h"
#include "SceneNiveau1.h"
#include <iostream> // Debbogage

using namespace platformer;

Joueur::Joueur() : persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
	// <SBerube>
	isOnGround = false;
	isJumping = false;
	jumpTime = milliseconds(100);
	gravityTick = milliseconds(10);
	// </SBerube>
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
	collider = RectCollider(Vector2f(getPosition().x - (getScale().x * animator.GetCurAnimRect().width / 2), getPosition().y - (getScale().y * animator.GetCurAnimRect().height / 2)),
							Vector2f(getPosition().x + (getScale().x * animator.GetCurAnimRect().width / 2), getPosition().y + (getScale().y * animator.GetCurAnimRect().height / 2)));
	// </SBerube>
	this->limiteGauche = limiteGauche + TAILLE_RECT / 4;
	this->limiteDroite = limiteDroite - TAILLE_RECT / 4;

	return true;
}

// <SBerube>
void Joueur::move(const int direction)
{
	bool collision = false;
	IntRect oldAnimRect = animator.GetCurAnimRect();
	Vector2f oldPosition = getPosition();
	RectCollider oldCollider = collider;
	// Droite
	if (direction == 1)
	{
		Sprite::move(vitesse / 2, 0);

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

	// Bas
	else if(direction == 2)
	{
		Sprite::move(0, 1);
	}
	// Haut
	else if (direction == -2)
	{
		Sprite::move(0, -1);
	}

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

	// Ici, on vérifie la collision entre le joueur et chaque tuile du jeu qui n'est pas vide.
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 15; j++)
		{
			if (SceneNiveau1::GetGrilleAt(i, j) != nullptr)
			{
				if (collider.CollidesWith(Vector2f(SceneNiveau1::GetGrilleAt(i, j)->getPosition().x, SceneNiveau1::GetGrilleAt(i, j)->getPosition().y),
					Vector2f(SceneNiveau1::GetGrilleAt(i, j)->getPosition().x + 20, SceneNiveau1::GetGrilleAt(i, j)->getPosition().y + 15)))
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
	}

	// Si il y a une collision avec un des tuiles du jeu, on annule tout le déplacement
	if (collision)
	{
		setPosition(oldPosition);
		IntRect oldAnimRect = animator.GetCurAnimRect();
		animator.SetCurAnimRect(oldAnimRect);
		collider = oldCollider;
	}
	// <smasson>
	/*Updater la direction de look*/
	if (lookLeft)
		setScale(SCALE_X*-1, SCALE_Y);
	else
		setScale(SCALE_X, SCALE_Y);
	// </smasson>
	// On remet le collider sur le joueur après son déplacement
	collider = RectCollider(Vector2f(getPosition().x - getScale().x * animator.GetCurAnimRect().width / 2, getPosition().y - getScale().y * animator.GetCurAnimRect().height / 2),
		Vector2f(getPosition().x + getScale().x * animator.GetCurAnimRect().width / 2, getPosition().y + getScale().y * animator.GetCurAnimRect().height / 2));

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

	if (isJumping)
	{
		if (timerAfterJump.getElapsedTime() < jumpTime)
		{
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
	// <smasson>
	//Updater l'animateur
	animator.Update();
	//Updater la texture
	setTexture(animator.GetCurAnimTexture());
	setTextureRect(animator.GetCurAnimRect());
	// </smasson>
}
void Joueur::Gravite()
{
	if (gravityTimer.getElapsedTime() > gravityTick)
	{
		//if(!isJumping)
			move(2); // On fait descendre le personnage
		gravityTimer.restart();
	}
}

// </SBerube>