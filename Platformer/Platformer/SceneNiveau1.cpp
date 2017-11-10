#include "SceneNiveau1.h"
#include "CollisionHandler.h"
#include <iostream>

using namespace platformer;
using namespace std;

//Sprite* SceneNiveau1::grilleDeTuiles[NOMBRE_TUILES_X][NOMBRE_TUILES_Y];

SceneNiveau1::SceneNiveau1()
{
    //Initialisation de la représentation interne des truiles à nullptr
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

	if (!joueur.Init(0, window->getSize().x, /*"Ressources\\Sprites\\Player\\Player.png"*/ "Ressources\\Sprites\\2_Knight\\_Walk\\Walk.png", "Ressources\\Sprites\\2_Knight\\_Idle\\Idle.png"))
	{
		return false;
	}

    // <smasson>
    //Visuel des spawners
    string spawnerPath = "Ressources\\Sprites\\GEMS\\orbs.png";
    if (!spawner01.Init(spawnerPath) || !spawner02.Init(spawnerPath))
    {
        return false;
    }
	// </smasson>

	for (int i = 0; i < BACKGROUNDS; i++)
	{
        //Application des textures découpées sur les morceaux
		background[i].setTexture(backgroundT[i]);
	}
	//Initialisation du random time
	srand(time(NULL));

	// <SBerube>
    //Création + positionnement des tuiles
	for (size_t x = 0; x < NOMBRE_TUILES_X; ++x)
	{
        //Les lignes pleines
		// Plafond complet
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1]->setPosition(x * TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 1));
		// Sol complet
		grilleDeTuiles[x][1] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][1]->setPosition(x * TAILLE_TUILES_X, 0);

        //Lignes personnalisées
		// etage 1
		//grilleDeTuiles[x][4] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		//grilleDeTuiles[x][4]->setPosition(x * TAILLE_TUILES_X, 4 * TAILLE_TUILES_Y);
		// etage 2
		//grilleDeTuiles[x][8] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		//grilleDeTuiles[x][8]->setPosition(x * TAILLE_TUILES_X, 8 * TAILLE_TUILES_Y);
		// etage 3
		//grilleDeTuiles[x][11] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		//grilleDeTuiles[x][11]->setPosition(x * TAILLE_TUILES_X, 11 * TAILLE_TUILES_Y);
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
	//grilleDeTuiles[NOMBRE_TUILES_X - 1][2] = nullptr;
	//grilleDeTuiles[NOMBRE_TUILES_X - 1][3] = nullptr;
	// Acces 1er etage
	grilleDeTuiles[1][4] = nullptr;
	grilleDeTuiles[2][4] = nullptr;
	// Acces 3e etage
	grilleDeTuiles[11][8] = nullptr;
	grilleDeTuiles[12][8] = nullptr;
	// Acces 4e etage
	grilleDeTuiles[1][11] = nullptr;
	grilleDeTuiles[2][11] = nullptr;
	grilleDeTuiles[17][11] = nullptr;
	grilleDeTuiles[18][11] = nullptr;

	//Position arbitraire pour le joueur en x, pas arbitraire en y (sur le plancher)
	joueur.setPosition(150, window->getSize().y - TAILLE_TUILES_Y * 2- 50);
    // <smasson>
    //SetPos des spawners
    spawner01.SetPosition(TAILLE_TUILES_X*3.5f, window->getSize().y - TAILLE_TUILES_Y*14.5);
    
    // </smasson>
	this->mainWin = window;
	isRunning = true;
	
	return true;
}
// <SBerube>
//Vector2i SceneNiveau1::DeterminerTuileDe(float posX, float posY)
//{
//
//	return Vector2i(posX / TAILLE_TUILES_X, posY / TAILLE_TUILES_Y);
//}
//Sprite* SceneNiveau1::GetGrilleAt(int x, int y)
//{
//	//grilleDeTuiles[x][y]->setOrigin(0, 0);
//	return grilleDeTuiles[x][y];
//}
// </SBerube>

// <smasson>
// </smasson>

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
	// <SBerube>
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
    //Pour tester uniquement
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		interfaceCommande |= 8;
	}*/
	// </SBerube>
}

void SceneNiveau1::update()
{
	// <SBerube>
    //Bouger vers la gauche le joueur
    if (interfaceCommande == 1 || interfaceCommande == 5)
    {
        Vector2f lastPos = joueur.getPosition();
        joueur.move(-1);
        bool collides = false;
        for (int x = 0; x < NOMBRE_TUILES_X; ++x)
        {
            for (int y = 0; y < NOMBRE_TUILES_Y; ++y)
            {
                //S'il y a une tuile
                if (grilleDeTuiles[x][y] != nullptr)
                {
                    if (grilleDeTuiles[x][y]->getGlobalBounds().intersects(joueur.getGlobalBounds()) && grilleDeTuiles[x][y]->getPosition().y <= joueur.getPosition().y)
                    {
                        grilleDeTuiles[x][y]->setColor(Color::Black);
                        joueur.setPosition(lastPos);
                    }
                    else
                    {
                        grilleDeTuiles[x][y]->setColor(Color::White);
                    }
                }
            }
        }
    }
    //Bouger vers la droite le joueur
	else if(interfaceCommande == 2 || interfaceCommande == 6)
	{
        Vector2f lastPos = joueur.getPosition();
        joueur.move(1);
        bool collides = false;
        for (int x = 0; x < NOMBRE_TUILES_X; ++x)
        {
            for (int y = 0; y < NOMBRE_TUILES_Y; ++y)
            {
                //S'il y a une tuile
                if (grilleDeTuiles[x][y] != nullptr)
                {
                    if (grilleDeTuiles[x][y]->getGlobalBounds().intersects(joueur.getGlobalBounds()) && grilleDeTuiles[x][y]->getPosition().y <= joueur.getPosition().y)
                    {
                        grilleDeTuiles[x][y]->setColor(Color::Black);
                        joueur.setPosition(lastPos);
                    }
                    else
                    {
                        grilleDeTuiles[x][y]->setColor(Color::White);
                    }
                }
            }
        }
	}
//	if (interfaceCommande == 4 || interfaceCommande == 5 || interfaceCommande == 6)
    if (interfaceCommande & 4 )
    {
        if (joueur.IsJumping() == false)
            joueur.Jump();
	}
    else if (interfaceCommande == 0)
    {
        joueur.move(0);
    }
	if (interfaceCommande == 8)
	{
        
	}
	// </SBerube>
    joueur.Update();
    // <smasson>
    // Effets de la gravité
    Vector2f lastPos = joueur.getPosition();
    if (!joueur.IsJumping())
    {
        joueur.moveDown();
    }
    else
    {
        joueur.moveUp();
    }
    bool collides = false;
    for (int x = 0; x < NOMBRE_TUILES_X; ++x)
    {
        for (int y = 0; y < NOMBRE_TUILES_Y; ++y)
        {
            //S'il y a une tuile
            if (grilleDeTuiles[x][y] != nullptr)
            {
                if (grilleDeTuiles[x][y]->getGlobalBounds().intersects(joueur.getGlobalBounds()) && grilleDeTuiles[x][y]->getPosition().y > joueur.getPosition().y)
                {
                    grilleDeTuiles[x][y]->setColor(Color::Black);
                    joueur.setPosition(lastPos);
                }
                else
                {
                    grilleDeTuiles[x][y]->setColor(Color::White);
                }
            }
        }
    }
    //Update des ou du spawner
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

