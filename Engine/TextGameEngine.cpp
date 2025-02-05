#include "TextGameEngine.h"
#include "Util/Logger.h"

namespace TGE
{
    TextGameEngine::TextGameEngine() {}
    TextGameEngine::~TextGameEngine()
    {
        FontManager::UnloadFonts();
    }

    void TextGameEngine::GameLoop()
    {
        while(m_Window.isOpen())
        {
            try
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

                Update();
                Render();
            }
            catch(const char* e)
            {
                Logger::Log(LogLevel::ERROR, e);
                Logger::Log(LogLevel::ERROR, "Exiting...");
                exit(-1);
            }
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
} // namespace TGE