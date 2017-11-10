#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Personnage.h"
// <smasson>
#include "Spawner.h"
// </smasson>

using namespace sf;

namespace platformer
{
	class SceneNiveau1 : public Scene
	{
	public:
		SceneNiveau1();
		~SceneNiveau1();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
		// <SBerube>
		//static Vector2i DeterminerTuileDe(float posX, float posY);
		//static Sprite* GetGrilleAt(int x, int y);
		// </SBerube>
        // <smasson>
        // </smasson>

	private:
		
		static const int NOMBRE_TUILES_X = 20;
		static const int NOMBRE_TUILES_Y = 15;
		static const int TAILLE_TUILES_X = 40;
		static const int TAILLE_TUILES_Y = 32;
		static const int TUILES_ROUGES = 7;
		static const int BACKGROUNDS = 3;
		
		/// <summary>
		/// Th�oriquement la fen�tre pourrait �tre remplie de tuile de mani�re exacte (20 X 15 pour �tre pr�cis, voir plus haut)
		/// On a donc une grille de pointeurs null, et si un bloc doit �tre conc�tis�, alors il ne sera pas null.
		/// </summary>
		Sprite* grilleDeTuiles[NOMBRE_TUILES_X][NOMBRE_TUILES_Y];

		/// <summary>
		/// On a 7 tuiles rouges de base; alors on va toutes les utiliser, pour le moment.
		/// </summary>
		Texture tuilesRougesT[TUILES_ROUGES];
		
		/// <summary>
		/// Trois backgrounds superpos�s pour le plus bel effet visuel
		/// </summary>
		Texture backgroundT[BACKGROUNDS];
		Sprite background[BACKGROUNDS];
		
        // <smasson>
        /*Voici les spawners*/
        Spawner spawner01;
        Spawner spawner02;
        /*Voici l'ensemble des ennemys et des ennemys inactifs*/
        vector<Personnage> ennemys;
        // </smasson>

		Personnage joueur;

		int interfaceCommande;
	};
}