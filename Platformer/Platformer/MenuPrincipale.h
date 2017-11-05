#pragma once
#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"

using namespace platformer;

namespace platformer
{
    class MenuPrincipale: public Scene
    {
    public:
        /*Le constructeur*/
        MenuPrincipale();
        /*Le destructeur*/
        ~MenuPrincipale();
        
        /*Les autres fonctions*/
        /*Fonction run qui sera exécutée par "Game"*/
        scenes run();
        bool init(RenderWindow * const window);
        void getInputs();
        void update();
        void draw();

        void deselectionnerBoutons();
    private:
        Texture backgroundTexture;
        Sprite backgroundVisual;

        Font font;
        
        const int ESPACEMENT_BOUTONS = 48;

        Textbox buttonLogin;
        Textbox buttonBestScore;
        Textbox buttonAccount;
        Textbox buttonQuit;
        /*L'UI active*/
        Textbox* curUI = nullptr;
        /*Enum des boutons actifs possibles*/
        enum Button
        {
            NONE,
            LOG_IN,
            BEST_SCORE,
            ACCOUNT_MANAGEMENT,
            QUIT
        };
        /*Le bouton courant*/
        Button curButton = NONE;
    };
}