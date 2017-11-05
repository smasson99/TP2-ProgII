#include "Spawner.h"

using namespace platformer;

Spawner::Spawner()
{

}

Spawner::~Spawner()
{

}

bool Spawner::Init(string path)
{
    bool res = (texture.loadFromFile(path));
    /*animator.AddAnim(texture);
    animator.InitAnim(0, 0.5f);
    visual.setOrigin(animator.GetCurAnimRect().width / 2, animator.GetCurAnimRect().height / 2);*/
    visual.setTexture(texture);
    visual.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    visual.setScale(SCALE_X, SCALE_Y);
    return res;
}

void Spawner::Update()
{
    //visual.setTexture(animator.GetCurAnimTexture());
    //visual.setTextureRect(animator.GetCurAnimRect());
}

void Spawner::SetPosition(Vector2f position)
{
    visual.setPosition(position);
}

void Spawner::SetPosition(float x, float y)
{
    visual.setPosition(Vector2f(x, y));
}

void Spawner::Draw(RenderWindow* mainWin)
{
    mainWin->draw(visual);
}
