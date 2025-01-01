#pragma once

#include "../Lib/defs.h"
#include <SFML/Window.hpp>
#include <string>

using namespace std;

class ENGINE_API TextGameEngine
{
private:
    void Render();
    void HandleInput();
    void GameLoop();

private:
    sf::Window window;

public:  
    TextGameEngine();
    ~TextGameEngine();

    int Start(sf::VideoMode videoMode, string title);
};