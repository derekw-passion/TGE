#include "TextGameEngine.h"
#include "../Lib/Logger.h"

TextGameEngine::TextGameEngine() {}
TextGameEngine::~TextGameEngine() {}

void TextGameEngine::Render()
{
    
}

void TextGameEngine::HandleInput()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void TextGameEngine::GameLoop()
{
    while(window.isOpen())
    {
        HandleInput();
    }
}

int TextGameEngine::Start(sf::VideoMode videoMode, string title)
{
    Logger::Log(LogLevel::INFO, "Building window");
    
    window.create(videoMode, title);
    window.setFramerateLimit(60);

    Logger::Log(LogLevel::INFO, "Entering game loop");
    GameLoop();
    
    return 0;
}