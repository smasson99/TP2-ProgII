// <smasson>
#include "AccountManagement.h"

using namespace platformer;

AccountManagement::AccountManagement()
{
}

AccountManagement::~AccountManagement()
{
}

Scene::scenes AccountManagement::run()
{
    while (isRunning)
    {
        getInputs();
        update();
        draw();
    }

    return transitionVersScene;
}

bool AccountManagement::init(RenderWindow * const window)
{
    this->mainWin = window;
    isRunning = true;
    //Chargments
    /*Chargement des textures*/
    if (!backgroundTexture.loadFromFile("Ressources\\Sprites\\UI\\Backgrounds\\BlackSquare.png"))
        return false;
    /*Chargement de la font*/
    if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
        return false;

    //Initialisation des assets
    backgroundVisual.setTexture(backgroundTexture);
    backgroundVisual.setScale(window->getSize().x, window->getSize().y);
    backgroundVisual.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);

    /*Initialisation Interface*/
    createAccountButton.init(480, 24, Vector2f(430, 200), font);
    createAccountButton.insererTexte("Creer un compte");

    modifyAccountButton.init(480, 24, Vector2f(430, 200 + ESPACEMENT_BOUTONS), font);
    modifyAccountButton.insererTexte("Modifier un compte");

    deleteAccountButton.init(480, 24, Vector2f(430, 200 + ESPACEMENT_BOUTONS * 2), font);
    deleteAccountButton.insererTexte("Effacer un compte");

    returnButton.init(480, 35, Vector2f(430, 200 + ESPACEMENT_BOUTONS * 3), font);
    returnButton.insererTexte("Retour au \"Menu Principale\"");

    return true;
}

void AccountManagement::getInputs()
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
        //Événements de la souris
        if (event.type == Event::MouseButtonPressed)
        {
            //Si nous touchons le bouton de création d'account
            if (createAccountButton.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &createAccountButton;
                curUI->selectionner(Color::Yellow);
                curButton = CREATE;
            }
            //Si nous touchons le bouton de modification de l'account
            else if (modifyAccountButton.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &modifyAccountButton;
                curUI->selectionner(Color::Yellow);
                curButton = MODIFY;
            }
            //Si nous touchons le bouton d'effacement de l'account
            else if (deleteAccountButton.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &deleteAccountButton;
                curUI->selectionner(Color::Yellow);
                curButton = DELETE;
            }
            else if (returnButton.touche(Mouse::getPosition(*mainWin)))
            {
                deselectionnerBoutons();
                curUI = &returnButton;
                curUI->selectionner(Color::Yellow);
                curButton = RETURN_MENU;
            }
            //Si nous ne touchons rien
            else
            {
                deselectionnerBoutons();
            }
        }
    }
}

void AccountManagement::update()
{
    if (curButton > 0)
    {
        transitButton(curButton);
    }
}

void AccountManagement::draw()
{
    //Clean-up
    mainWin->clear();
    //Dessiner
    //Boutons
    createAccountButton.dessiner(mainWin);
    modifyAccountButton.dessiner(mainWin);
    deleteAccountButton.dessiner(mainWin);
    returnButton.dessiner(mainWin);
    //Afficher
    mainWin->display();
}

void AccountManagement::deselectionnerBoutons()
{
    curUI = nullptr;
    curButton = NONE_Button;
    createAccountButton.deSelectionner();
    modifyAccountButton.deSelectionner();
    deleteAccountButton.deSelectionner();
    returnButton.deSelectionner();
}

void AccountManagement::transitButton(int curBut)
{
    switch (curBut)
    {
    case CREATE:
        
        break;
    case MODIFY:
        
        break;
    case DELETE:
        
        break;
    case RETURN_MENU:
        transitionVersScene = Scene::scenes::MENU_PRINCIPALE;
        isRunning = false;
        break;
    }
}
// </smasson>