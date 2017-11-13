// <Sberube>
#include "AccountCreation.h"
#include "AccountDelete.h"
AccountCreation::AccountCreation()
{
	InModification = false;
}
AccountCreation::AccountCreation(bool inModification)
{
	this->InModification = inModification;
}
AccountCreation::~AccountCreation()
{
}

Scene::scenes AccountCreation::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}
	return transitionVersScene;
}

bool AccountCreation::init(RenderWindow * const window)
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
	fNameLabel.setFont(font);
	lNameLabel.setFont(font);
	emailLabel.setFont(font);

	// Username
	usernameBox.init(480, 24, Vector2f(400, 70), font);
	usernameLabel.setPosition(160, 30);
	usernameLabel.setCharacterSize(usernameBox.getTailleTexte()*0.8f);
	usernameLabel.setString("Username:");

	// Password
	passwordBox.init(480, 24, Vector2f(400,42 + ESPACEMENT_BOUTONS * 2), font);
	passwordLabel.setPosition(160, 100);
	passwordLabel.setCharacterSize(passwordBox.getTailleTexte()*0.8f);
	passwordLabel.setString("Password:");

	// First name
	fNameBox.init(480, 24, Vector2f(400, 112 + ESPACEMENT_BOUTONS * 2), font);
	fNameLabel.setPosition(160, 170);
	fNameLabel.setCharacterSize(passwordBox.getTailleTexte()*0.8f);
	fNameLabel.setString("First Name:");

	// Last name
	lNameBox.init(480, 24, Vector2f(400, 182 + ESPACEMENT_BOUTONS * 2), font);
	lNameLabel.setPosition(160, 240);
	lNameLabel.setCharacterSize(passwordBox.getTailleTexte()*0.8f);
	lNameLabel.setString("Last Name:");

	// Email
	emailBox.init(480, 24, Vector2f(400, 252 + ESPACEMENT_BOUTONS * 2), font);
	emailLabel.setPosition(160, 310);
	emailLabel.setCharacterSize(passwordBox.getTailleTexte()*0.8f);
	emailLabel.setString("Email:");

	// Create button (valider)
	createButton.init(180, 24, Vector2f(550, 260 + ESPACEMENT_BOUTONS*3.5f), font);
	createButton.insererTexte("OK");

	// Back button (retour)
	backButton.init(160, 24, Vector2f(240, 260 + ESPACEMENT_BOUTONS*3.5f), font);
	backButton.insererTexte("Back");
	if (InModification)
	{
		usernameBox.insererTexte(AccountHandler::GetInstance()->getModVariable(1));
		passwordBox.insererTexte(AccountHandler::GetInstance()->getModVariable(2));
		fNameBox.insererTexte(AccountHandler::GetInstance()->getModVariable(3));
		lNameBox.insererTexte(AccountHandler::GetInstance()->getModVariable(4));
		emailBox.insererTexte(AccountHandler::GetInstance()->getModVariable(5));
	}
	//Initialisation réussie
	return true;
}

void AccountCreation::getInputs()
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
			//Si on touche au bouton create avec la souris
			if (createButton.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &createButton;
				curButton = CREATE;
				createButton.selectionner(Color::Yellow);
				// On supprime l'account si on est en modification
				if (InModification)
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
							if (user != usernameBox.getTexte())
							{
								temp << line << endl;
							}
						}
					}

					// On remplace le fichier des accounts par le temporaire.
					remove("Ressources\\Other\\accounts.txt");
					rename("Ressources\\Other\\temp.txt", "Ressources\\Other\\accounts.txt");
				}
				// Vérifications des champs.
				int validationCode = AccountHandler::GetInstance()->newAccount(usernameBox.getTexte(), 
																			   passwordBox.getTexte(), 
																			   fNameBox.getTexte(), 
																			   lNameBox.getTexte(), 
																			   emailBox.getTexte());
				
				string newUName = usernameBox.getTexte();
				string newPWord = passwordBox.getTexte();
				string newLName = lNameBox.getTexte();
				string newFName = fNameBox.getTexte();
				string newEmail = emailBox.getTexte();

				ofstream accounts;
				switch (validationCode)
				{
				case 0:
					// Les entrées sont valides, on procède à la création du compte.
						accounts.open("Ressources\\Other\\accounts.txt", std::ios_base::app | std::ios_base::out);
						accounts << newUName << " " << newPWord << " " << newLName << " " << newFName << " " << newEmail << "\n";
						accounts.close();
						transitionVersScene = scenes::MENU_PRINCIPALE;
						isRunning = false;

					// Les autres cas sont des messages d'erreur.
				//	break;
				//case 1:
				//	break;
				//case 2:
				//	break;
				//case 3:
				//	break;
				//case 4:
				//	break;
				//case 5:
				//	break;
				//case 6:
				//	break;
				//case 7:
				//	break;
				//case 8:
				//	break;
				//case 9:
				//	break;
				//case 10:
				//	break;

				}
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
			//Si on touche au textbox First name avec la souris
			else if (fNameBox.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &fNameBox;
				curTextbox = TextBoxT::F_NAME;
				curUI->selectionner(Color::Yellow);
			}
			//Si on touche au textbox Last name avec la souris
		    else if (lNameBox.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &lNameBox;
				curTextbox = TextBoxT::L_NAME;
				curUI->selectionner(Color::Yellow);
			}
			//Si on touche au textbox Email avec la souris
			else if (emailBox.touche(Mouse::getPosition(*mainWin)))
			{
				deselectionnerBoutons();
				curUI = &emailBox;
				curTextbox = TextBoxT::EMAIL;
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
			if (event.key.code == Keyboard::Return && curButton == Button::NONE_Button)
			{
				//Pour s'assurer que enter n'est pas saisie comme caractère
				enterActif = true;

				int indexT = (int)curTextbox;
				//Valider contenu mot de passe, si la textbox est celle du mot de passe
				if (curTextbox == TextBoxT::EMAIL)
				{
					deselectionnerBoutons();
					curUI = &emailBox;
					curTextbox = TextBoxT::EMAIL;
					curUI->selectionner(Color::Yellow);
				}
				//Sinon
				else
				{
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
					case TextBoxT::F_NAME:
						deselectionnerBoutons();
						curUI = &fNameBox;
						curTextbox = TextBoxT::F_NAME;
						curUI->selectionner(Color::Yellow);
						break;
					case TextBoxT::L_NAME:
						deselectionnerBoutons();
						curUI = &lNameBox;
						curTextbox = TextBoxT::L_NAME;
						curUI->selectionner(Color::Yellow);
						break;
					}
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

void AccountCreation::update()
{
}

void AccountCreation::draw()
{
	//Nettoyage de l'écran
	mainWin->clear();
	//Dessiner contenu
	//TextBoxs
	mainWin->draw(backgroundVisual);
	usernameBox.dessiner(mainWin);
	passwordBox.dessiner(mainWin);
	fNameBox.dessiner(mainWin);
	lNameBox.dessiner(mainWin);
	emailBox.dessiner(mainWin);
	//Boutons
	createButton.dessiner(mainWin);
	backButton.dessiner(mainWin);
	//Textes
	mainWin->draw(usernameLabel);
	mainWin->draw(passwordLabel);
	mainWin->draw(fNameLabel);
	mainWin->draw(lNameLabel);
	mainWin->draw(emailLabel);
	//Dessiner l'écran
	mainWin->display();
}

void AccountCreation::deselectionnerBoutons()
{
	if (curButton != NONE_Textbox)
		curUI = nullptr;
	curButton = Button::NONE_Button;
	curTextbox = TextBoxT::NONE_Textbox;
	usernameBox.deSelectionner();
	passwordBox.deSelectionner();
	fNameBox.deSelectionner();
	lNameBox.deSelectionner();
	emailBox.deSelectionner();
	createButton.deSelectionner();
	backButton.deSelectionner();
}

bool AccountCreation::play()
{
	// Validation des informations AccountHandler::GetInstance()->validerAccount(usernameBox.getTexte(), passwordBox.getTexte())
	if (true)
	{
		//Bon username, bon mot de passe
		transitionVersScene = Scene::NIVEAU1;
		isRunning = false;
		return true;
	}
	return false;
}
// </Sberube>