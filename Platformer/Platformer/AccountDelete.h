#pragma once
// <SBerube>
#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
#include "AccountHandler.h"

using namespace platformer;

namespace platformer
{
	class AccountDelete : public Scene
	{
	public:
		/*Le constructeur*/
		AccountDelete();
		/*Le destructeur*/
		~AccountDelete();

		/*Les autres fonctions*/
		/*Fonction run qui sera exécutée par "Game"*/
		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

		void deselectionnerBoutons();
		void DeleteAcc(string username);
	private:
		bool play();

		Texture backgroundTexture;
		Sprite backgroundVisual;

		Font font;

		const int ESPACEMENT_BOUTONS = 48;

		Text usernameLabel;
		Text passwordLabel;
		Text confirmLabel;

		Textbox usernameBox;
		Textbox passwordBox;

		Textbox yesButton;
		Textbox noButton;
		Textbox buttonDelete;
		Textbox backButton;

		//Pour savoir si enter est actif
		bool enterActif = false;
		//Pour savoir si backspace est actif et pour ne pas écrire comme caractère dans une textbox
		bool backspaceActif = false;
		// Pour savoir si on est en mode confimation
		bool confirmation = false;
		/*L'UI active*/
		Textbox* curUI = nullptr;
		/*Enum des boutons actifs possibles*/
		enum Button
		{
			NONE_Button,
			DELETE,
			BACK,
			YES,
			NO
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
// </SBerube>