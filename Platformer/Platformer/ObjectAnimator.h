#pragma once
// <smasson>
#include "AnimationShredder.h"

namespace platformer
{
    class ObjectAnimator
    {
    public:
        ObjectAnimator();
        ~ObjectAnimator();
        void AddAnim(Texture texture);
        void PlayAnim(const int animNumber, const float animPerSeconds);
        void Update();
        IntRect& GetCurAnimRect();
        Texture& GetCurAnimTexture();
    private:
        vector<vector<IntRect>*>* anims;
        vector<Texture>* textures;
        Clock animClock;
        Time animTime;
        int curAnim;
        int curFrame;
    };
}
// </smasson>