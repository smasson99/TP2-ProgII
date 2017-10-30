#pragma once
#include "RectCollider.h"
using namespace sf;

/// <summary>
/// Squelette d'une classe joueur.  Y a pas grand chose ici, mais c'est tout de même la sprite
/// De l'ensemble des animations qui est utilisée.
///
///QUATRES CONSEILS IMPORTANTS:
///1- Vous aurez le choix entre animer la spriteSheet ou d'intégrer 4 sprites différentes.  Dans ce cas-ci, votre 
///joueur ne devra plus hériter de sprite
///
///2- Si vous faites plus d'un niveau, le joueur pourrait être portée dans la game et passé par référence plutôt que détruit et crée à chaque niveau de jeu.
///
///3- Pour faire changer votre personnage direction, il faudra le "refléter dans une direction (reflet == scaling à -1)
///
///4- Si vous utilisez les sprites founis pour le joueur et que vous utilisez le cadre du Rectangle de sprite pour vos collisions, vos collisions seront probablement très éloignées.
///Votre jouuer pourrait "porter" un rectangle de collsion faisait 32 pixels de large.
///
/// </summary>
namespace platformer
{
	class Joueur : public Sprite
	{
	public:
		Joueur();
		~Joueur();
		void move(const int direction);
		void Jump();
		void Update();
		void Gravite();
		bool Init(const int limiteGauche, const int limiteDroite, const String texturePath);
	private:
		static const int TAILLE_RECT = 64;

		Texture texture;

		IntRect persoRect;
		float vitesse = 3;
		float limiteGauche;
		float limiteDroite;

		bool isOnGround;

		bool isJumping;
		Clock timerAfterJump;
		Time jumpTime;

		Clock gravityTimer;
		Time gravityTime;
	};
}

