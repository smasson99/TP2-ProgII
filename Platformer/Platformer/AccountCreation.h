#pragma once
#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
#include "AccountHandler.h"
#include <string>

using namespace platformer;
namespace platformer
{
	class AccountCreation : public Scene
	{
	public:
		/*Le constructeur*/
		AccountCreation();
		/*Le constructeur pour une modification*/
		AccountCreation(bool inModification);
		/*Le destructeur*/
		~AccountCreation();


		/*Fonction run qui sera exécutée par "Game"*/
		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

		void deselectionnerBoutons();
	private:

		// Variables pour la midification d'un account
		bool InModification;

		bool play();

		Texture backgroundTexture;
		Sprite backgroundVisual;

		Font font;

		const int ESPACEMENT_BOUTONS = 48;

		Text usernameLabel;
		Text passwordLabel;
		Text fNameLabel;
		Text lNameLabel;
		Text emailLabel;

		Textbox usernameBox;
		Textbox passwordBox;
		Textbox fNameBox;
		Textbox lNameBox;
		Textbox emailBox;

		Textbox backButton;
		Textbox createButton;

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
			CREATE,
			BACK
		};
		/*Enum des textboxs actives possibles*/
		enum TextBoxT
		{
			NONE_Textbox,
			USERNAME,
			PASSWORD,
			F_NAME,
			L_NAME,
			EMAIL,
		};
		/*Le bouton courant*/
		Button curButton = Button::NONE_Button;
		/*Le textbox courant*/
		TextBoxT curTextbox = TextBoxT::NONE_Textbox;
	};
}