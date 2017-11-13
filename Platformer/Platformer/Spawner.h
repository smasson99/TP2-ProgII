#pragma once

#include <SFML\Graphics.hpp>
#include "ObjectAnimator.h"
#include <vector>

using namespace std;
using namespace sf;

namespace platformer
{
    class Spawner
    {
    public:
        Spawner();
        ~Spawner();
        bool Init(string path);
        void AddPatrolPoint(Vector2f coord);
        void Update();
        void SetPosition(Vector2f position);
        void SetPosition(float x, float y);
        Vector2f GetPosition();
        vector<Vector2f> GetPatrolCoords();
        void Draw(RenderWindow* mainWin);
    private:
        //Le visuel
        Texture texture;
        Sprite visual;
        //Les dimensions
        const float SCALE_X = 0.30f;
        const float SCALE_Y = SCALE_X;
        //Infos de patrouille
        vector<Vector2f> coords;
    };
}