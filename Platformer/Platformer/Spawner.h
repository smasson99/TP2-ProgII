#pragma once

#include <SFML\Graphics.hpp>
#include "ObjectAnimator.h"

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
        void Update();
        void SetPosition(Vector2f position);
        void SetPosition(float x, float y);
        void Draw(RenderWindow* mainWin);
    private:
        Texture texture;
        Sprite visual;
        const float SCALE_X = 0.30f;
        const float SCALE_Y = SCALE_X;
        float rayon;

        ObjectAnimator animator;
    };
}