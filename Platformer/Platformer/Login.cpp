// <smasson>
#include "Login.h"
#include "Game.h"
Login::Login()
{
	inModification = false;
}
Login::Login(bool inModification)
{
	this->inModification = inModification;
}
Login::~Login()
{
}

Scene::scenes Login::run()
{
    while (isRunning)
    {
        getInputs();
        update();
        draw();
    }
    return transitionVersScene;
}

bool Login::init(RenderWindow * const window)
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

    usernameBox.init(480, 24, Vector2f(430, 250), font);
    usernameLabel.setPosition(190, 210);
    usernameLabel.setCharacterSize(usernameBox.getTailleTexte()*0.8f);
    usernameLabel.setString("Nom d'utilisateur:");

    passwordBox.init(480, 24, Vector2f(430, 250 + ESPACEMENT_BOUTONS*2), font);
    passwordLabel.setPosition(190, 310);
    passwordLabel.setCharacterSize(passwordBox.getTailleTexte()*0.8f);
    passwordLabel.setString("Mot de passe:");
    
    buttonPlay.init(480, 24, Vector2f(430, 250 + ESPACEMENT_BOUTONS*3.5f), font);
    buttonPlay.insererTexte("Valider");

    //Initialisation réussie
    return true;
}

void Login::getInputs()
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
            //Si on touche au bouton play avec la souris
            if (buttonPlay.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonPlay;
                curButton = PLAY;
                buttonPlay.selectionner(Color::Yellow);
                bool playSucceded = play();
                //Si le mot de passe ou le username n'est pas valide
                if (!playSucceded)
                {

                }
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
                //Valider contenu mot de passe, si la textbox est celle du mot de passe
                if (curTextbox == TextBoxT::PASSWORD)
                {
                    if (!play())
                    {

                    }
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

void Login::update()
{
}

void Login::draw()
{
    //Nettoyage de l'écran
    mainWin->clear();
    //Dessiner contenu
    //TextBoxs
    mainWin->draw(backgroundVisual);
    usernameBox.dessiner(mainWin);
    passwordBox.dessiner(mainWin);
    //Boutons
    buttonPlay.dessiner(mainWin);
    //Textes
    mainWin->draw(usernameLabel);
    mainWin->draw(passwordLabel);
    //Dessiner l'écran
    mainWin->display();
}

void Login::deselectionnerBoutons()
{
    if (curButton != NONE_Textbox)
        curUI = nullptr;
    curButton = Button::NONE_Button;
    curTextbox = TextBoxT::NONE_Textbox;
    usernameBox.deSelectionner();
    passwordBox.deSelectionner();
    buttonPlay.deSelectionner();
}

bool Login::play()
{
    if (AccountHandler::GetInstance()->validerAccount(usernameBox.getTexte(), passwordBox.getTexte()))
    {
        //Bon username, bon mot de passe
		// ON vérifie si on est en mode modification
		if (inModification)
		{
			{
				AccountHandler::GetInstance()->setModVariables(usernameBox.getTexte());
			}
			transitionVersScene = Scene::MODIFICATION;
			isRunning = false;
			return true;
		}
		else
		{
			transitionVersScene = Scene::NIVEAU1;
			isRunning = false;
			return true;
		}

    }
    return false;
}
// </smasson>