#include "TextGameEngine.h"
#include "../Lib/Logger.h"

TextGameEngine::TextGameEngine() {}
TextGameEngine::~TextGameEngine()
{
    FontManager::UnloadFonts();
}

void TextGameEngine::GameLoop()
{
    while(m_Window.isOpen())
    {
        sf::Event event;
        while(m_Window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_Window.close();
            }

            HandleInput(event);
        }

        Render();
    }
}

void TextGameEngine::RenderBegin()
{
    m_Window.clear(settings.clearColor);
}

void TextGameEngine::RenderEnd()
{
    m_Window.display();
}

int TextGameEngine::Start()
{
    Logger::Log(LogLevel::INFO, "Building window");
    
    m_Window.create(settings.videoMode, settings.title);
    m_Window.setFramerateLimit(settings.frameRateLimit);

    Logger::Log(LogLevel::INFO, "Initializing engine");
    if(Init() != 0)
    {
        Logger::Log(LogLevel::ERROR, "Failed to initialize engine");
        return -1;
    }
    else
    {
        Logger::Log(LogLevel::INFO, "Engine initialized");
    }

    Logger::Log(LogLevel::INFO, "Entering game loop");
    GameLoop();
    
    return 0;
}