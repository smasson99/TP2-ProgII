#include "AccountDelete.h"
// <SBerube>
AccountDelete::AccountDelete()
{
}

AccountDelete::~AccountDelete()
{
}

Scene::scenes AccountDelete::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}
	return transitionVersScene;
}

bool AccountDelete::init(RenderWindow * const window)
{
	/*Chargement des textures*/
	if (!backgroundTexture.loadFromFile("Ressources\\Sprites\\UI\\Backgrounds\\BlackSquare.png"))
		return false;
	/*Chargement de la font*/
	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
		return false;
	/*Fin chargement des textures
	À partir d'ici, le programme a toutes ses textures et tout est
	un succès, pour l'instant*/
	this->mainWin = window;
	isRunning = true;

	//Initialisation des assets
	backgroundVisual.setTexture(backgroundTexture);
	backgroundVisual.setScale(window->getSize().x, window->getSize().y);
	backgroundVisual.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);

	/*Initialisation Interface*/
	usernameLabel.setFont(font);
	passwordLabel.setFont(font);
	confirmLabel.setFont(font);

	usernameBox.init(480, 24, Vector2f(430, 50), font);
	usernameLabel.setPosition(190, 10);
	usernameLabel.setCharacterSize(usernameBox.getTailleTexte()*0.8f);
	usernameLabel.setString("Username");

	passwordBox.init(480, 24, Vector2f(430, 30 + ESPACEMENT_BOUTONS * 2), font);
	passwordLabel.setPosition(190, 90);
	passwordLabel.setCharacterSize(passwordBox.getTailleTexte()*0.8f);
	passwordLabel.setString("Password");

	buttonDelete.init(480, 24, Vector2f(430, 30 + ESPACEMENT_BOUTONS*3), font);
	buttonDelete.insererTexte("DELETE");

	backButton.init(480, 24, Vector2f(430, 30 + ESPACEMENT_BOUTONS * 4), font);
	backButton.insererTexte("Back");

	yesButton.init(160, 200, Vector2f(270, 200 + ESPACEMENT_BOUTONS*3.5f), font);
	yesButton.insererTexte("YES");

	noButton.init(160, 200, Vector2f(590, 200 + ESPACEMENT_BOUTONS*3.5f), font);
	noButton.insererTexte("NO");


	confirmLabel.setPosition(220, 280);
	confirmLabel.setCharacterSize(passwordBox.getTailleTexte()*0.8f);
	confirmLabel.setString("Are you sure you wanna delete this account?");

	//Initialisation réussie
	return true;
}

void AccountDelete::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		/*Event fermeture écran (X sur la fenêtre)*/
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}
		//Les événements de la souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche au bouton delete avec la souris
			if (buttonDelete.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &buttonDelete;
				curButton = DELETE;
				buttonDelete.selectionner(Color::Red);

				confirmation = true;
			}
			//Si on touche au bouton Yes avec la souris
			else if (confirmation && yesButton.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &yesButton;
				curButton = YES;
				backButton.selectionner(Color::Yellow);
				// On doit supprimer l'acconut si il existe
				if (AccountHandler::GetInstance()->validerAccount(usernameBox.getTexte(), passwordBox.getTexte()))
				{
					DeleteAcc(usernameBox.getTexte());
				}
				confirmation = false;
			}
			//Si on touche au bouton No avec la souris
			else if (confirmation && noButton.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &noButton;
				curButton = NO;
				backButton.selectionner(Color::Yellow);

				confirmation = false;
			}
			//Si on touche au bouton back avec la souris
			else if (backButton.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &backButton;
				curButton = BACK;
				backButton.selectionner(Color::Yellow);
				transitionVersScene = scenes::GESTION_COMPTE;
				isRunning = false;
			}
			//Si on touche au textbox username avec la souris
			else if (usernameBox.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &usernameBox;
				curTextbox = TextBoxT::USERNAME;
				curUI->selectionner(Color::Yellow);
			}
			//Si on touche au textbox password avec la souris
			else if (passwordBox.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &passwordBox;
				curTextbox = TextBoxT::PASSWORD;
				curUI->selectionner(Color::Yellow);
			}
			else
			{
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				deselectionnerBoutons();
			}

		}

		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && curUI != nullptr)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return && curButton == Button::NONE_Button)
			{
				//Pour s'assurer que enter n'est pas saisie comme caractère
				enterActif = true;

				int indexT = (int)curTextbox;

					//Incrémenter le textBox courant
					++indexT;
					switch (indexT)
					{
					case TextBoxT::PASSWORD:
						deselectionnerBoutons();
						curUI = &passwordBox;
						curTextbox = TextBoxT::PASSWORD;
						curUI->selectionner(Color::Yellow);
						break;
					}
			}
			else if (event.key.code == Keyboard::BackSpace && curButton == Button::NONE_Button)
			{
				curUI->retirerChar();
				//Pour s'assurer que backspace n'est pas saisie comme caractère
				backspaceActif = true;
			}
		}

		//Entrer les charactères dans la textBox courante, s'il y en a une
		if (!backspaceActif && !enterActif && curUI != nullptr && curButton == Button::NONE_Button && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128)
			{
				curUI->ajouterChar((char)event.text.unicode);
			}
		}
	}
	//Dans tous les cas on netoie ces conditions après chaque boucle.
	enterActif = false;
	backspaceActif = false;
}

void AccountDelete::update()
{
}

void AccountDelete::draw()
{
	//Nettoyage de l'écran
	mainWin->clear();
	//Dessiner contenu
	//TextBoxs
	mainWin->draw(backgroundVisual);
	usernameBox.dessiner(mainWin);
	passwordBox.dessiner(mainWin);
	//Boutons
	buttonDelete.dessiner(mainWin);
	backButton.dessiner(mainWin);
	//Textes
	mainWin->draw(usernameLabel);
	mainWin->draw(passwordLabel);
	// La confirmation
	if (confirmation)
	{
		mainWin->draw(confirmLabel);
		yesButton.dessiner(mainWin);
		noButton.dessiner(mainWin);
	}
	//Dessiner l'écran
	mainWin->display();
}

void AccountDelete::deselectionnerBoutons()
{
	if (curButton != NONE_Textbox)
		curUI = nullptr;
	curButton = Button::NONE_Button;
	curTextbox = TextBoxT::NONE_Textbox;
	usernameBox.deSelectionner();
	passwordBox.deSelectionner();
	buttonDelete.deSelectionner();
	yesButton.deSelectionner();
	noButton.deSelectionner();
	backButton.deSelectionner();
	// On enlève le confirmation
	confirmation = false;
}

bool AccountDelete::play()
{
	if (AccountHandler::GetInstance()->validerAccount(usernameBox.getTexte(), passwordBox.getTexte()))
	{
		//Bon username, bon mot de passe
		transitionVersScene = Scene::NIVEAU1;
		isRunning = false;
		return true;
	}
	return false;
}

void AccountDelete::DeleteAcc(string username)
{

	{
		ifstream iFich("Ressources\\Other\\accounts.txt");
		ofstream temp("Ressources\\Other\\temp.txt");
		string line;

		while (getline(iFich, line))
		{
			stringstream l(line);
			string user, trash;
			l >> user >> trash;
			// On écrit dans le temporaire les lignes qu ne comportent pas le username à supprimer.
			if (user != username)
			{
				temp << line << endl;
			}
		}
	}

	// On remplace le fichier des accounts par le temporaire.
	remove("Ressources\\Other\\accounts.txt");
	rename("Ressources\\Other\\temp.txt", "Ressources\\Other\\accounts.txt");
}
// </SBerube>