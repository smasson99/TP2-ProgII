#pragma once
#include "RectCollider.h"
// <smasson>
#include "Rigidbody.h"
#include <SFML/Graphics.hpp>
#include "ObjectAnimator.h"
// </smasson>

using namespace sf;
using namespace platformer;

/// <summary>
/// Squelette d'une classe joueur.  Y a pas grand chose ici, mais c'est tout de m�me la sprite
/// De l'ensemble des animations qui est utilis�e.
///
///QUATRES CONSEILS IMPORTANTS:
///1- Vous aurez le choix entre animer la spriteSheet ou d'int�grer 4 sprites diff�rentes.  Dans ce cas-ci, votre 
///joueur ne devra plus h�riter de sprite
///
///2- Si vous faites plus d'un niveau, le joueur pourrait �tre port�e dans la game et pass� par r�f�rence plut�t que d�truit et cr�e � chaque niveau de jeu.
///
///3- Pour faire changer votre personnage direction, il faudra le "refl�ter dans une direction (reflet == scaling � -1)
///
///4- Si vous utilisez les sprites founis pour le joueur et que vous utilisez le cadre du Rectangle de sprite pour vos collisions, vos collisions seront probablement tr�s �loign�es.
///Votre jouuer pourrait "porter" un rectangle de collsion faisait 32 pixels de large.
///
/// </summary>
namespace platformer
{
	class Personnage : public Rigidbody
	{
	public:
		//class SceneNiveau1;
		Personnage();
		~Personnage();
        // <smasson>
        bool Init(const int limiteGauche, const int limiteDroite, const String walkAnimPath, const String idleAnimPath);
        virtual void Update();
        // </smasson>
	protected:

        static const int TAILLE_RECT = 64;

        // <smasson>
        static enum Animations
        {
            IDLE,
            RUN_LEFT,
            RUN_RIGHT,
            JUMP,
            DIE
        };
        void move(const int direction);
        void moveDown();
        void moveUp();
        void Jump();
        void Jump(bool right);
        /*Les directions possibles, utile dans la d�tection des collisions avec les tuiles*/
        static enum Direction
        {
            NONE,
            HAUT,
            BAS,
            GAUCHE,
            DROITE
        };

       Texture walkTexture;
       Texture idleTexture;

        virtual bool CheckCollisions(const Direction dir, Sprite*(*tab)[15]);

        bool lookLeft;

        Vector2f dir;

        float scaleX = 0.05f;
        float scaleY = 0.05f;

        ObjectAnimator animator;

        bool isJumping = false;
        bool canJump = true;
        bool colRightOnlyWJump = false;
        bool colLeftOnlyWJump = false;
        const float GRAVITY_FORCE = 2.9f;
        const float JUMP_FORCE = GRAVITY_FORCE*0.95f;
        const float MAX_JUMP_TIME = 0.5f;

        Time time;
        Clock clock;
        // </smasson>

        IntRect persoRect;

		// <SBerube>
		float vitesse = 3;
		float limiteGauche;
		float limiteDroite;

		RectCollider collider;
		// </SBerube>
	};
}

