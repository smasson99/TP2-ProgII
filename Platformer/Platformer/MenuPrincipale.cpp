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
    � partir d'ici, le programme a toutes ses textures et tout est 
    un succ�s, pour l'instant*/
    this->mainWin = window;
    isRunning = true;
    /*D�but initialisation des sprites*/
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

    /*Tout va bien, tout s'est bien pass�*/
    return true;
}

void MenuPrincipale::getInputs()
{
    while (mainWin->pollEvent(event))
    {
        /*Event fermeture �cran (X sur la fen�tre)*/
        if (event.type == Event::Closed)
        {
            //Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
            //fin � l'application
            isRunning = false;
            transitionVersScene = Scene::scenes::SORTIE;
        }
        //Si on a un �v�nement de click de souris
        if (event.type == Event::MouseButtonPressed)
        {
            //Si on touche au bouton de login avec la souris
            if (buttonLogin.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonLogin; //Ce bouton devient actif
                curButton = LOG_IN;
                buttonLogin.selectionner(Color::Yellow);  //Appliquer le visuel de s�lection
            }
            //Si on touche au bouton du meilleur score avec la souris
            else if (buttonBestScore.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonBestScore; //Ce bouton devient actif
                curButton = BEST_SCORE;
                buttonBestScore.selectionner(Color::Yellow);  //Appliquer le visuel de s�lection
            }
            else if (buttonAccount.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonAccount; //Ce bouton devient actif
                curButton = ACCOUNT_MANAGEMENT;
                buttonAccount.selectionner(Color::Yellow);  //Appliquer le visuel de s�lection
            }
            else if (buttonQuit.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &buttonQuit; //Ce bouton devient actif
                curButton = QUIT;
                buttonQuit.selectionner(Color::Yellow);  //Appliquer le visuel de s�lection
            }
            else
            {
                //Ce else devrait �tre dans toutes vos fen�tres o� il n'y a pas de textbox.
                deselectionnerBoutons();
            }

        }

    }
}

void MenuPrincipale::update()
{
    //Si nous avons un bouton de s�lectionn�:
    if (curUI != nullptr && curButton != NONE)
    {
        /*Examiner le bouton actif, agir en cons�quence*/
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
    //Nettoyage de l'�cran
    mainWin->clear();
    //Affichage du background
    mainWin->draw(backgroundVisual);
    //Affichage des boutons
    buttonLogin.dessiner(mainWin);
    buttonBestScore.dessiner(mainWin);
    buttonAccount.dessiner(mainWin);
    buttonQuit.dessiner(mainWin);
    //Finalement, afficher l'�cran
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