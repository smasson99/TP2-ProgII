//#include "Joueur.h"
#include "SceneNiveau1.h"
#include <iostream> // Debbogage

using namespace platformer;

Personnage::Personnage() : persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
	// <SBerube>
	isOnGround = false;
	isJumping = false;
	jumpTime = milliseconds(100);
	gravityTick = milliseconds(10);
	// </SBerube>
}

Personnage::~Personnage()
{
}

bool Personnage::Init(const int limiteGauche, const int limiteDroite, const String walkAnimPath, const String idleAnimPath)
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

    /*Ici, l'ordre d'appel est important et est d�pendant de l'enum: Animations*/
    /*IDLE = 0, RUN_LEFT = 1, RUN_RIGHT= 2, JUMP = 3, DIE = 4*/
    /*//*/
    animator.AddAnim(idleAnimTexture);
    animator.AddAnim(runAnimTexture);
    animator.AddAnim(runAnimTexture);

    //On regarde � droite en commen�ant
    lookLeft = false;
    //On start l'IDLE
    /*Il faut user de cette fonction pour d�marrer, autrement nous assisterons � une crise d'�pilepsie*/
    animator.InitAnim(IDLE, 0.3f);
    /*Nous setons la texture de base avec son rect*/
    setTexture(animator.GetCurAnimTexture());
    setTextureRect(animator.GetCurAnimRect());
    /*Setter l'origine (tr�s important)*/
	setOrigin(animator.GetCurAnimRect().width / 2, animator.GetCurAnimRect().height / 2);
    // </smasson>

	// <SBerube>
	//collider = RectCollider(Vector2f(getPosition().x - (getScale().x * animator.GetCurAnimRect().width / 2), getPosition().y - (getScale().y * animator.GetCurAnimRect().height / 2)),
	//                        Vector2f(getPosition().x + (getScale().x * animator.GetCurAnimRect().width / 2), getPosition().y + (getScale().y * animator.GetCurAnimRect().height / 2)));
	// </SBerube>
	this->limiteGauche = limiteGauche + TAILLE_RECT / 4;
	this->limiteDroite = limiteDroite - TAILLE_RECT / 4;

	return true;
}

// <SBerube>
void Personnage::move(const int direction)
{
	bool collision = false;
	Vector2f oldPosition = getPosition();
	//RectCollider oldCollider = collider;

	// On fait d'abbord bouger le personnage pour savoir si c'est possible
	// Droite
	if (direction == 1)
	{
		Sprite::move(vitesse/4.0f, 0);
	}
	// Gauche
	else if (direction == -1)
	{
		Sprite::move(-vitesse / 4.0f, 0);
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


	// Ici, on v�rifie la collision entre le joueur et chaque tuile du jeu qui n'est pas vide.
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 15; j++)
		{
			if (SceneNiveau1::GetGrilleAt(i, j) != nullptr)
			{
				//if (collider.CollidesWith(Vector2f(SceneNiveau1::GetGrilleAt(i, j)->getPosition().x, SceneNiveau1::GetGrilleAt(i, j)->getPosition().y),
				//	Vector2f(SceneNiveau1::GetGrilleAt(i, j)->getPosition().x + 20, SceneNiveau1::GetGrilleAt(i, j)->getPosition().y + 15)))
				if(SceneNiveau1::GetGrilleAt(i, j)->getTextureRect().intersects(animator.GetCurAnimRect()))
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

	// Si il y a une collision avec un des tuiles du jeu, on annule tout le d�placement
	if (collision)
	{
		setPosition(oldPosition);
		//collider = oldCollider;
	}
	// Sinon on effectue les animations associ�s au mouvement
	//else
	//{
	//	if (direction == 1)
	//	{
	//		// <smasson>
	//		/*Jouer � droite(anim)*/
	//		animator.PlayAnim(RUN_RIGHT, 0.1f);
	//		lookLeft = false;
	//		// </smasson>
	//	}
	//	// Gauche
	//	else if (direction == -1)
	//	{
	//		// <smasson>
	//		/*Jouer � gauche(anim)*/
	//		animator.PlayAnim(RUN_LEFT, 0.1f);
	//		lookLeft = true;
	//		// </smasson>
	//	}
	//	// <smasson>
	//	/*Sinon, nous ne bougeons pas, donc aller en Idle*/
	//	else
	//	{
	//		/*Jouer l'IDLE*/
	//		animator.PlayAnim(IDLE, 0.3f);
	//	}
	//	// </smasson>

	//}
	// <smasson>
	/*Updater la direction de look*/
	if (lookLeft)
		setScale(SCALE_X*-1, SCALE_Y);
	else
		setScale(SCALE_X, SCALE_Y);

	//Test sur les limites de l'�cran
	if (getPosition().x < limiteGauche)
	{
		setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x > limiteDroite)
	{
		setPosition(limiteDroite, getPosition().y);
	}
	// </smasson>
	// On remet le collider sur le joueur apr�s son d�placement
	//collider = RectCollider(Vector2f(getPosition().x - getScale().x * animator.GetCurAnimRect().width / 2, getPosition().y - getScale().y * animator.GetCurAnimRect().height / 2),
		//Vector2f(getPosition().x + getScale().x * animator.GetCurAnimRect().width / 2, getPosition().y + getScale().y * animator.GetCurAnimRect().height / 2));

}

void Personnage::Jump()
{
	if (isOnGround)
	{
		isJumping = true;
		timerAfterJump.restart();
	}
}

void Personnage::Update()
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
	//setTexture(animator.GetCurAnimTexture());
	//setTextureRect(animator.GetCurAnimRect());
	// </smasson>
}
void Personnage::Gravite()
{
	if (gravityTimer.getElapsedTime() > gravityTick)
	{
		//if(!isJumping)
		//	move(2); // On fait descendre le personnage
		gravityTimer.restart();
	}
}

// </SBerube>