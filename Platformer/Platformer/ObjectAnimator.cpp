// <smasson>
#include "ObjectAnimator.h"
#include "AnimationShredder.h"

using namespace platformer;

ObjectAnimator::ObjectAnimator()
{
    anims = new vector<vector<IntRect>*>;
    textures = new vector<Texture>;
    curAnim = 0;
    curFrame = 0;
}

ObjectAnimator::~ObjectAnimator()
{
    /*Nettoyage des anims*/
    for (size_t i = 0; i < anims->size(); ++i)
    {
        delete anims->at(i);
    }
    delete anims;
    /*Nettoyage des textures*/
    delete textures;
}

void ObjectAnimator::AddAnim(const Texture texture)
{
    AnimationShredder* instanceShredder = AnimationShredder::GetInstance();
    textures->push_back(texture);
    anims->push_back(instanceShredder->ShredSingleSheet(texture));
}

void ObjectAnimator::Update()
{
    if (animClock.getElapsedTime().asSeconds() > animTime.asSeconds())
    {
        ++curFrame;
        if (curFrame > anims->at(curAnim)->size()-1)
        {
            curFrame = 0;
        }
        animClock.restart();
    }
}

void ObjectAnimator::InitAnim(const int animNumber, const float animPerSeconds)
{
    curAnim = animNumber;
    curFrame = 0;
    animTime = seconds(animPerSeconds);
    animClock.restart();
}

void ObjectAnimator::PlayAnim(const int animNumber, const float animPerSeconds)
{
    if (curAnim != animNumber)
    {
        curAnim = animNumber;
        curFrame = 0;
        if (animPerSeconds != 0)
        {
            animTime = seconds(animPerSeconds);
            animClock.restart();
        }
    }
}

IntRect& ObjectAnimator::GetCurAnimRect()
{
    return anims->at(curAnim)->at(curFrame);
}

Texture& ObjectAnimator::GetCurAnimTexture()
{
    return textures->at(curAnim);
}
// <SBerube>
void ObjectAnimator::SetCurAnimRect(const IntRect rect)
{
	anims->at(curAnim)->at(curFrame) = rect;
}
// </SBerube>
// </smasson>