#pragma once
#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
#include "AccountHandler.h"

using namespace platformer;

namespace platformer
{
    class Login : public Scene
    {
    public:
        /*Le constructeur*/
        Login();
        /*Le destructeur*/
        ~Login();

        /*Les autres fonctions*/
        /*Fonction run qui sera exécutée par "Game"*/
        scenes run();
        bool init(RenderWindow * const window);
        void getInputs();
        void update();
        void draw();

        void deselectionnerBoutons();
    private:
        bool play();

        Texture backgroundTexture;
        Sprite backgroundVisual;

        Font font;

        const int ESPACEMENT_BOUTONS = 48;

        Text usernameLabel;
        Text passwordLabel;

        Textbox usernameBox;
        Textbox passwordBox;
        Textbox buttonPlay;

        //Pour savoir si enter est actif
        bool enterActif = false;
        //Pour savoir si backspace est actif et pour ne pas écrire comme caractère dans une textbox
        bool backspaceActif = false;

        /*L'UI active*/
        Textbox* curUI = nullptr;
        /*Enum des boutons actifs possibles*/
        enum Button
        {
            NONE_Button,
            PLAY
        };
        /*Enum des textboxs actives possibles*/
        enum TextBoxT
        {
            NONE_Textbox,
            USERNAME,
            PASSWORD
        };
        /*Le bouton courant*/
        Button curButton = Button::NONE_Button;
        /*Le textbox courant*/
        TextBoxT curTextbox = TextBoxT::NONE_Textbox;
    };
}