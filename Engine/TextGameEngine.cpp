#include "TextGameEngine.h"
#include "../Lib/Logger.h"

TextGameEngine::TextGameEngine() {}
TextGameEngine::~TextGameEngine() {}

void TextGameEngine::Render()
{
    window.clear(sf::Color::Black);

    sf::Text text;
    text.setFont(font);
    text.setString("Hello, world!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    window.draw(text);

    window.display();
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
        Render();
    }
}

int TextGameEngine::Start(sf::VideoMode videoMode, string title)
{
    Logger::Log(LogLevel::INFO, "Building window");
    
    window.create(videoMode, title);
    window.setFramerateLimit(60);

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