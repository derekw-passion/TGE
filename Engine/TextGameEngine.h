#pragma once

#include "../Lib/defs.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

struct ENGINE_API EngineSettings
{
    string title = "Game";
    sf::VideoMode videoMode = sf::VideoMode({800, 600});
    unsigned int frameRateLimit = 60;
    sf::Color clearColor = sf::Color::Black;
};

class ENGINE_API TextGameEngine
{
private:
    sf::RenderWindow window;
    sf::Font font;

private:
    void GameLoop();

protected:
    void RenderBegin();
    void RenderEnd();
    
    virtual void Render();
    virtual void HandleInput(sf::Event event) = 0;

protected:
    EngineSettings settings;

public:  
    TextGameEngine();
    ~TextGameEngine();

    int Start();
};