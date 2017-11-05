#include "SceneNiveau1.h"

using namespace platformer;

SceneNiveau1::SceneNiveau1()
{
	for (int x=0; x < NOMBRE_TUILES_X; x++)
		for (int y = 0; y < NOMBRE_TUILES_Y; y++)
		{
			grilleDeTuiles[x][y] = nullptr;
		}
}

SceneNiveau1::~SceneNiveau1()
{
	for (int x = 0; x < NOMBRE_TUILES_X; x++)
		for (int y = 0; y < NOMBRE_TUILES_Y; y++)
		{
			if (grilleDeTuiles[x][y] != nullptr)
			{
				delete grilleDeTuiles[x][y];
			}
		}
}

Scene::scenes SceneNiveau1::run()
{
	
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneNiveau1::init(RenderWindow * const window)
{
	for (int i = 0; i < TUILES_ROUGES; i++)
	{
		if (!tuilesRougesT[i].loadFromFile("Ressources\\Tiles\\BlockA" + std::to_string(i) + ".png"))
		{
			return false;
		}
	}

	for (int i = 0; i < BACKGROUNDS; i++)
	{
		if (!backgroundT[i].loadFromFile("Ressources\\Backgrounds\\Layer" + std::to_string(i) + "_1.png"))
		{
			return false;
		}
	}

	if (!joueur.Init(0, window->getSize().x, "Ressources\\Sprites\\2_Knight\\_Walk\\Walk.png", "Ressources\\Sprites\\2_Knight\\_Idle\\Idle.png"))
	{
		return false;
	}

    // <smasson>
    string spawnerPath = "Ressources\\Sprites\\GEMS\\orbs.png";
    if (!spawner01.Init(spawnerPath) || !spawner02.Init(spawnerPath))
    {
        return false;
    }
    
	// </smasson>

	for (int i = 0; i < BACKGROUNDS; i++)
	{
		background[i].setTexture(backgroundT[i]);
	}
	
	srand(time(NULL));
	for (size_t x = 0; x < NOMBRE_TUILES_X; ++x)
	{
		// Plafond
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1]->setPosition(x * TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 1));
		// Sol
		grilleDeTuiles[x][1] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][1]->setPosition(x * TAILLE_TUILES_X, 0);

		// etage 1
		grilleDeTuiles[x][4] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][4]->setPosition(x * TAILLE_TUILES_X, 4 * TAILLE_TUILES_Y);
		// etage 2
		grilleDeTuiles[x][8] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][8]->setPosition(x * TAILLE_TUILES_X, 8 * TAILLE_TUILES_Y);
		// etage 3
		grilleDeTuiles[x][11] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][11]->setPosition(x * TAILLE_TUILES_X, 11 * TAILLE_TUILES_Y);
	}
	for (size_t y = 0; y < NOMBRE_TUILES_Y; ++y)
	{
		// Mur droit
		grilleDeTuiles[NOMBRE_TUILES_X - 1][y] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[NOMBRE_TUILES_X - 1][y]->setPosition((NOMBRE_TUILES_X - 1) * TAILLE_TUILES_X, y * TAILLE_TUILES_Y);
		// Mur gauche
		grilleDeTuiles[0][y] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[0][y]->setPosition(0, y * TAILLE_TUILES_Y);
	}
	// Entrée de la grotte
	grilleDeTuiles[NOMBRE_TUILES_X - 1][2] = nullptr;
	grilleDeTuiles[NOMBRE_TUILES_X - 1][3] = nullptr;
	// Acces 1er etage
	grilleDeTuiles[1][7] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
	grilleDeTuiles[1][7]->setPosition(1 * TAILLE_TUILES_X, 7 * TAILLE_TUILES_Y);
	grilleDeTuiles[1][6] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
	grilleDeTuiles[1][6]->setPosition(1 * TAILLE_TUILES_X, 6 * TAILLE_TUILES_Y);
	grilleDeTuiles[2][7] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
	grilleDeTuiles[2][7]->setPosition(2 * TAILLE_TUILES_X, 7 * TAILLE_TUILES_Y);
	grilleDeTuiles[1][4] = nullptr;
	grilleDeTuiles[2][4] = nullptr;
	// Acces 3e etage
	grilleDeTuiles[10][9] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
	grilleDeTuiles[10][9]->setPosition(10 * TAILLE_TUILES_X, 9 * TAILLE_TUILES_Y);
	grilleDeTuiles[10][10] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
	grilleDeTuiles[10][10]->setPosition(10 * TAILLE_TUILES_X, 10 * TAILLE_TUILES_Y);
	grilleDeTuiles[11][10] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
	grilleDeTuiles[11][10]->setPosition(11 * TAILLE_TUILES_X, 10 * TAILLE_TUILES_Y);
	grilleDeTuiles[11][8] = nullptr;
	grilleDeTuiles[12][8] = nullptr;
	// Acces 4e etage
	grilleDeTuiles[1][11] = nullptr;
	grilleDeTuiles[2][11] = nullptr;
	grilleDeTuiles[17][11] = nullptr;
	grilleDeTuiles[18][11] = nullptr;
	grilleDeTuiles[NOMBRE_TUILES_X - 2][NOMBRE_TUILES_Y - 2] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
	grilleDeTuiles[NOMBRE_TUILES_X - 2][NOMBRE_TUILES_Y - 2]->setPosition((NOMBRE_TUILES_X - 2) * TAILLE_TUILES_X, (NOMBRE_TUILES_Y - 2) * TAILLE_TUILES_Y);
	grilleDeTuiles[1][NOMBRE_TUILES_Y - 2] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
	grilleDeTuiles[1][NOMBRE_TUILES_Y - 2]->setPosition(1 * TAILLE_TUILES_X, (NOMBRE_TUILES_Y - 2) * TAILLE_TUILES_Y);
	//Position arbitraire pour le joueur en x, pas arbitraire en y (sur le plancher)
	joueur.setPosition(100, window->getSize().y - TAILLE_TUILES_Y * 2);

    spawner01.SetPosition(TAILLE_TUILES_X*3.5f, window->getSize().y - TAILLE_TUILES_Y*14.5);

	this->mainWin = window;
	isRunning = true;
	
	return true;
}

void SceneNiveau1::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Scene::scenes::TITRE;
			}
		}
	}

	interfaceCommande = 0;

	//Méthode binaire: appuyer à gauche et à droite sumultanément va donner 3, et le personnage ne se dépalcera alors pas.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		interfaceCommande |= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		interfaceCommande |= 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		interfaceCommande |= 4;
	}
	// <smasson>
    else
    {
        interfaceCommande |= 0;
    }
	// </smasson>
}

void SceneNiveau1::update()
{
	if (interfaceCommande == 1 || interfaceCommande == 5)
	{
		joueur.move(-1);
	}
	else if(interfaceCommande == 2 || interfaceCommande == 6)
	{
		joueur.move(1);
	}
	if (interfaceCommande == 4 || interfaceCommande == 5 || interfaceCommande == 6)
	{
		joueur.Jump();
	}
    else if (interfaceCommande == 0)
    {
        joueur.move(0);
    }
    joueur.Update();
    // <smasson>
    spawner01.Update();
    // </smasson>
}

void SceneNiveau1::draw()
{
	mainWin->clear();

	for (int i = 0; i < BACKGROUNDS; i++)
	{
		mainWin->draw(background[i]);
	}

	for (int x = 0; x < NOMBRE_TUILES_X; x++)
		for (int y = 0; y < NOMBRE_TUILES_Y; y++)
		{
			if (grilleDeTuiles[x][y] != nullptr)
			{
				mainWin->draw(*grilleDeTuiles[x][y]);
			}
		}
	
    // <smasson>
    spawner01.Draw(mainWin);
    // </smasson>

	mainWin->draw(joueur);
	mainWin->display();
}

