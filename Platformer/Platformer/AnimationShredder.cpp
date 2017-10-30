// <smasson>
#include "AnimationShredder.h"

using namespace platformer;

/*Init par d�faut des statiques*/
/*L'instace statique*/
AnimationShredder* AnimationShredder::instance = nullptr;

AnimationShredder::AnimationShredder()
{

}

AnimationShredder::~AnimationShredder()
{
    delete instance;
    AnimationShredder::instance = nullptr;
}

/*Singleton de la classe AnimationShredder*/
AnimationShredder* AnimationShredder::GetInstance()
{
    if (instance == nullptr)
        instance = new AnimationShredder();
    return instance;
}

/// <summary>
/// Fonction dont le r�le est de d�couper une spritesheet d'une seule ligne
/// et d'en retourner le r�sultat sous forme d'un pointeur de vecteur de pointeurs d'IntRect.
/// </summary>
/// <param name="sheet">La spritesheet.</param>
/// <returns>Pointeur de Vecteur de pointeur d'IntRects repr�sentant les frames de l'animation
/// d�coup�es.</returns>
vector<IntRect>* AnimationShredder::ShredSingleSheet(Texture sheet)
{
    /*D�claration des variables de base*/
    int nbFrames = sheet.getSize().x / sheet.getSize().y;
    int height = sheet.getSize().y;
    int width = sheet.getSize().x / nbFrames;
    /*D�claration du vecteur de retour*/
    vector<IntRect>* frames = new vector<IntRect>;
    /*D�coupage des frames*/
    for (size_t i = 0; i < nbFrames; ++i)
    {
        IntRect curFrame;
        
        curFrame.left = width * i; /*Multipli� par la colonne courante*/
        curFrame.top = height * 0; /*Qu'une seule ligne*/
        curFrame.width = width; /*ma largeur*/
        curFrame.height = height; /*ma hauteur*/

        frames->push_back(curFrame); /*Ajout du r�sultat*/
    }
    return frames;
}
// </smasson>