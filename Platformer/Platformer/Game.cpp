#include "Game.h"
#include "SceneTitre.h"
#include "SceneNiveau1.h"
// <smasson>
#include "MenuPrincipale.h"
#include "Login.h"
#include "AccountManagement.h"
// </smasson>
// <SBerube>
#include "AccountCreation.h"
#include "AccountDelete.h"
// </SBerube>

using namespace platformer;

Game::Game()
{
	//On place dans le contructeur ce qui permet � la game elle-m�me de fonctionner
    setlocale(LC_ALL, "");
	mainWin.create(VideoMode(LARGEUR, HAUTEUR, 32), "Platformer");  // , Style::Titlebar); / , Style::FullScreen);

	//Synchonisation coordonn�e � l'�cran!  Normalement 60 frames par secondes. � faire absolument
	mainWin.setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);  //�quivalent... normalement, mais pas toujours. � utiliser si la synchonisation de l'�cran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

int Game::testTest()
{
	return 0;
}

int Game::run()
{
	//deux enums et un pointeur de scene pour faire la manipulation de sc�ne
	Scene::scenes selecteurDeScene = Scene::scenes::MENU_PRINCIPALE;
	//Scene::scenes selecteurDeScene = Scene::scenes::GESTION_COMPTE;
	Scene::scenes sceneEnRetour;
	Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle sc�ne

	while (true)
	{
		//Seule condition de sortie de toute l'app
		if (selecteurDeScene == Scene::scenes::SORTIE)
		{
			return EXIT_SUCCESS;
		}
		else			
		{
			//Vous allez ajouter d'autre sc�nes, alors elles devront
			//�tre ajout�es ici
			switch (selecteurDeScene)
			{
                // <smasson>
            case Scene::scenes::MENU_PRINCIPALE:
                sceneActive = new MenuPrincipale();
                break;
            case Scene::scenes::LOGIN:
                sceneActive = new Login();
                break;
            case Scene::scenes::GESTION_COMPTE:
                sceneActive = new AccountManagement();
                break;
                // </smasson>
				// <SBerube>
			case Scene::scenes::CREATION_COMPTE:
				sceneActive = new AccountCreation();
				break;
			case Scene::scenes::DELETE_COMPTE:
				sceneActive = new AccountDelete();
				break;
			case Scene::scenes::MODIFIER_COMPTE:
				sceneActive = new Login(true);
				break;
			case Scene::scenes::MODIFICATION:
				sceneActive = new AccountCreation(true);
				break;
				// </SBerube>
			case Scene::scenes::TITRE:
				sceneActive = new SceneTitre();
				break;

			case Scene::scenes::NIVEAU1:
				sceneActive = new SceneNiveau1();
				break;
			}
			
			if (sceneActive->init(&mainWin))
			{
				sceneEnRetour = sceneActive->run();
				//� la fin d'une sc�ne, s'il y a des sauvegardes � faire
				//C'est aussi possible de les faire l�.
			}
			else
			{
				//cleap-up � faire pour s'assurer  de ne pas avoir de leak
				//(malgr� l'�chec)
				return EXIT_FAILURE;
			}			
		}

		selecteurDeScene = sceneEnRetour;
		delete sceneActive;
		sceneActive = nullptr;
	}
}

bool Game::init()
{
	return true;
}
