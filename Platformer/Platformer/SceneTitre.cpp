#include "SceneTitre.h"

using namespace platformer;

SceneTitre::SceneTitre()
{
	
}

SceneTitre::~SceneTitre()
{
}

Scene::scenes SceneTitre::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneTitre::init(RenderWindow * const window)
{
	if (!ecranTitreT.loadFromFile("Ressources\\Sprites\\Title.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

	ecranTitre.setTexture(ecranTitreT);

	//Les positions sont arbitraires, obtenus par essai et erreur.
	//par rapport au fond d'écran
	textbox.init(480, 24, Vector2f(430, 320), font);
	textboxErreur.initInfo(Vector2f(430, 290), font, true);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void SceneTitre::getInputs()
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

		//Si on a un événement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textbox avec la souris
			if (textbox.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox; //Ce textbox devient actif
				textbox.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				textboxActif = nullptr;
				textbox.deSelectionner();
			}

		}

		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère

				//Condition bison pour voir que la transition fonctionne.
				if (textbox.getTexte() == "password")
				{
					isRunning = false;
					transitionVersScene = Scene::scenes::NIVEAU1;
				}
				else
				{
					//On affiche notre erreur.
					textboxErreur.insererTexte("Mauvais mot de passe, entrez-en un bon!");
				}
			}
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
		}

		//Attention : TextEntered est différent de KeyPressed
		//Voir ici pour l'explication: https://www.sfml-dev.org/tutorials/2.4/window-events-fr.php
		if (!backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre à vous d'aller plus loin si vous voulez)
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}

	//Dans tous les cas on netoie ces conditions après chaque boucle.
	enterActif = false;
	backspaceActif = false;
}

void SceneTitre::update()
{
}

void SceneTitre::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	textbox.dessiner(mainWin);
	textboxErreur.dessiner(mainWin);
	mainWin->display();
}