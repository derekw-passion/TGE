#pragma once

#include "../Lib/defs.h"
#include "../Lib/Logger.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;

class ENGINE_API FontManager
{
private:
    static map<string, sf::Font*> m_Fonts;

public:
    static int LoadFont(string name, string path);
    static sf::Font* GetFont(string name);
    static void UnloadFonts();
};