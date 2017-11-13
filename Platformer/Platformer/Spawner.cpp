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
    visual.setTexture(texture);
    visual.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    visual.setScale(SCALE_X, SCALE_Y);
    return res;
}

void Spawner::AddPatrolPoint(Vector2f coord)
{
    coords.push_back(coord);
}

void Spawner::Update()
{
}

void Spawner::SetPosition(Vector2f position)
{
    visual.setPosition(position);
}

void Spawner::SetPosition(float x, float y)
{
    visual.setPosition(Vector2f(x, y));
}

Vector2f Spawner::GetPosition()
{
    return visual.getPosition();
}

vector<Vector2f> platformer::Spawner::GetPatrolCoords()
{
    return coords;
}

void Spawner::Draw(RenderWindow* mainWin)
{
    mainWin->draw(visual);
}
