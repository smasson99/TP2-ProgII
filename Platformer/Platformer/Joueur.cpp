#include "Joueur.h"

using namespace platformer;

Joueur::Joueur() : persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
}

Joueur::~Joueur()
{
}

bool Joueur::init(const int limiteGauche, const int limiteDroite, const String texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}

	setTexture(texture);
	setTextureRect(persoRect);
	setOrigin(TAILLE_RECT / 2, TAILLE_RECT /2);

	this->limiteGauche = limiteGauche + TAILLE_RECT / 4;
	this->limiteDroite = limiteDroite - TAILLE_RECT / 4;

	return true;
}

void Joueur::move(const int direction)
{
	if (direction == 1)
	{
		Sprite::move(vitesse, 0);
	}
	else if (direction == -1)
	{
		Sprite::move(-vitesse, 0);
	}

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