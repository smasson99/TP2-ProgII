#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

namespace platformer
{
    class AnimationShredder
    {
    public:
        static AnimationShredder* GetInstance();
        ~AnimationShredder();
       vector<IntRect>* ShredSingleSheet(Texture sheet);
    private:
        AnimationShredder();
        /*L'instance statique*/
        static AnimationShredder* instance;
    };
}