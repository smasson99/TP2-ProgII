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
       vector<IntRect>* ShredSingleSheet(const Texture sheet);
       vector<IntRect>* ShredSingleSheet(const Texture sheet, float width, float height);
    private:
        AnimationShredder();
        /*L'instance statique*/
        static AnimationShredder* instance;
    };
}