// <smasson>
#include "MenuPrincipale.h"
#include "AccountManagement.h"

MenuPrincipale::MenuPrincipale()
{

}

MenuPrincipale::~MenuPrincipale()
{

}

Scene::scenes MenuPrincipale::run()
{
    while (isRunning)
    {
        getInputs();
        update();
        draw();
    }

    return transitionVersScene;
}

bool MenuPrincipale::init(RenderWindow * const window)
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
    /*Début initialisation des sprites*/
    backgroundVisual.setTexture(backgroundTexture);
    backgroundVisual.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
    backgroundVisual.setScale(window->getSize().x, window->getSize().y);

    /*Initialisation Interface*/
    buttonLogin.init(480, 24, Vector2f(430, 280), font);
    buttonLogin.insererTexte("Log-in");
    buttonBestScore.init(480, 24, Vector2f(430, 280+ESPACEMENT_BOUTONS), font);
    buttonBestScore.insererTexte("Meilleurs Scores");
    buttonAccount.init(480, 24, Vector2f(430, 280 + ESPACEMENT_BOUTONS*2), font);
    buttonAccount.insererTexte("Gestion de compte");
    buttonQuit.init(480, 24, Vector2f(430, 280 + ESPACEMENT_BOUTONS*3), font);
    buttonQuit.insererTexte("Quitter");

    /*Tout va bien, tout s'est bien passé*/
    return true;
}

void MenuPrincipale::getInputs()
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
        //Si on a un événement de click de souris
        if (event.type == Event::MouseButtonPressed)
        {
            //Si on touche au bouton de login avec la souris
            if (buttonLogin.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonLogin; //Ce bouton devient actif
                curButton = LOG_IN;
                buttonLogin.selectionner(Color::Yellow);  //Appliquer le visuel de sélection
            }
            //Si on touche au bouton du meilleur score avec la souris
            else if (buttonBestScore.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonBestScore; //Ce bouton devient actif
                curButton = BEST_SCORE;
                buttonBestScore.selectionner(Color::Yellow);  //Appliquer le visuel de sélection
            }
            else if (buttonAccount.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonAccount; //Ce bouton devient actif
                curButton = ACCOUNT_MANAGEMENT;
                buttonAccount.selectionner(Color::Yellow);  //Appliquer le visuel de sélection
            }
            else if (buttonQuit.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonQuit; //Ce bouton devient actif
                curButton = QUIT;
                buttonQuit.selectionner(Color::Yellow);  //Appliquer le visuel de sélection
            }
            else
            {
                //Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
                deselectionnerBoutons();
            }

        }

    }
}

void MenuPrincipale::update()
{
    //Si nous avons un bouton de sélectionné:
    if (curUI != nullptr && curButton != NONE)
    {
        /*Examiner le bouton actif, agir en conséquence*/
        switch (curButton)
        {
        case LOG_IN:
            transitionVersScene = Scene::scenes::LOGIN;
            isRunning = false;
            break;
        case BEST_SCORE:

            break;
        case ACCOUNT_MANAGEMENT:
            transitionVersScene = Scene::scenes::GESTION_COMPTE;
            isRunning = false;
            break;
        case QUIT:
            transitionVersScene = Scene::scenes::SORTIE;
            isRunning = false;
            break;
        }
    }
}

void MenuPrincipale::draw()
{
    //Nettoyage de l'écran
    mainWin->clear();
    //Affichage du background
    mainWin->draw(backgroundVisual);
    //Affichage des boutons
    buttonLogin.dessiner(mainWin);
    buttonBestScore.dessiner(mainWin);
    buttonAccount.dessiner(mainWin);
    buttonQuit.dessiner(mainWin);
    //Finalement, afficher l'écran
    mainWin->display();
}

void MenuPrincipale::deselectionnerBoutons()
{
    if (curButton != NONE)
        curUI = nullptr;
    curButton = NONE;
    buttonLogin.deSelectionner();
    buttonBestScore.deSelectionner();
    buttonAccount.deSelectionner();
    buttonQuit.deSelectionner();
}
// </smasson>