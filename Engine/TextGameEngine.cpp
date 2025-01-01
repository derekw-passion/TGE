#include "TextGameEngine.h"
#include "../Lib/Logger.h"

TextGameEngine::TextGameEngine() {}
TextGameEngine::~TextGameEngine() {}

void TextGameEngine::Render()
{
    RenderBegin();

    sf::Text text;
    text.setFont(font);
    text.setString("Hello, world!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    window.draw(text);

    RenderEnd();
}

void TextGameEngine::GameLoop()
{
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            HandleInput(event);
        }

        Render();
    }
}

void TextGameEngine::RenderBegin()
{
    window.clear(settings.clearColor);
}

void TextGameEngine::RenderEnd()
{
    window.display();
}

int TextGameEngine::Start()
{
    Logger::Log(LogLevel::INFO, "Building window");
    
    window.create(settings.videoMode, settings.title);
    window.setFramerateLimit(settings.frameRateLimit);

    Logger::Log(LogLevel::INFO, "Loading fonts");
    if(!font.loadFromFile("resources/fonts/arial.ttf"))
    {
        Logger::Log(LogLevel::ERROR, "Failed to load fonts.");
        return -1;
    }

    Logger::Log(LogLevel::INFO, "Entering game loop");
    GameLoop();
    
    return 0;
}