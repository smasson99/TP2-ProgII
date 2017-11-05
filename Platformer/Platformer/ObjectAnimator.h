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
        void InitAnim(const int animNumber, const float animPerSeconds);
        void PlayAnim(const int animNumber, const float animPerSeconds);
        void Update();
        IntRect& GetCurAnimRect();
        Texture& GetCurAnimTexture();
		// <SBerube>
		void SetCurAnimRect(IntRect rect);
		// </SBerube>
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