#pragma once

#include "defs.h"
#include "FontManager.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

namespace TGE
{
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
        sf::RenderWindow m_Window;

    private:
        void GameLoop();

    protected:
        void RenderBegin();
        void RenderEnd();
        sf::RenderWindow* GetWindow() { return &m_Window; }
        
    protected:
        virtual int Init() = 0;
        virtual void HandleInput(sf::Event event) = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        EngineSettings settings;

    public:  
        TextGameEngine();
        ~TextGameEngine();

        int Start();
    };
} // namespace TGE