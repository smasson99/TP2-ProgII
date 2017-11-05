#pragma once
#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
#include "AccountHandler.h"

namespace platformer
{
    class AccountManagement : public Scene
    {
    public:
        /*Le constructeur*/
        AccountManagement();
        /*Le destructeur*/
        ~AccountManagement();

        /*Les autres fonctions*/
        /*Fonction run qui sera exécutée par "Game"*/
        scenes run();
        bool init(RenderWindow * const window);
        void getInputs();
        void update();
        void draw();

        void deselectionnerBoutons();
    private:
        void transitButton(int curBut);

        Texture backgroundTexture;
        Sprite backgroundVisual;

        Font font;

        Textbox createAccountButton;
        Textbox modifyAccountButton;
        Textbox deleteAccountButton;
        Textbox returnButton;

        Textbox* curUI = nullptr;

        enum ButtonType
        {
            NONE_Button,
            CREATE,
            MODIFY,
            DELETE,
            RETURN_MENU
        };

        ButtonType curButton = NONE_Button;


        const int ESPACEMENT_BOUTONS = 48;
    };
}