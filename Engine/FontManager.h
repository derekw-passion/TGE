#pragma once

#include "defs.h"
#include "Util/Logger.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;

namespace TGE
{
    class ENGINE_API FontManager
    {
    private:
        static map<string, sf::Font*> Fonts;

    public:
        static int LoadFont(string name, string path);
        static sf::Font* GetFont(string name);
        static void UnloadFonts();
    };
} // namespace TGE