#include "TestGameEngine.h"
#include "../Engine/UI/UIElement.h"

TestGameEngine::TestGameEngine()
{
    settings.title = "Test";
    settings.videoMode = sf::VideoMode({800, 600});
    settings.frameRateLimit = 60;
    settings.clearColor = sf::Color::Black;
}
TestGameEngine::~TestGameEngine() = default;

int TestGameEngine::Init()
{
    Logger::Log(LogLevel::INFO, "Loading fonts");
    if(FontManager::LoadFont(FONT_ARIAL, FONT_ARIAL_PATH) != 0)
    {
        Logger::Log(LogLevel::ERROR, "Failed to load font");
        return -1;
    }

    Logger::Log(LogLevel::INFO, "Initializing UI");
    
    m_TextElement.Init(GetWindow());
    m_TextElement.setFont(*FontManager::GetFont(FONT_ARIAL));
    m_TextElement.setFillColor(sf::Color::White);
    m_TextElement.setString("Hello, World!");
    m_TextElement.setCharacterSize(16);
    m_TextElement.SetBackgroundVisible(true);
    
    sf::RectangleShape bg;
    bg.setOutlineColor(sf::Color::Green);
    bg.setOutlineThickness(1);
    bg.setFillColor(sf::Color(0, 255, 0, 100));
    m_TextElement.SetBackground(bg);

    UIElementSettings settings;
    settings.padding = {10, 10, 10, 10};
    settings.margin = {10, 10, 10, 10};
    m_TextElement.SetUIElementSettings(settings);

    return 0;
}
void TestGameEngine::HandleInput(sf::Event event) {}
void TestGameEngine::Update()
{
    m_TextElement.Update();
}
void TestGameEngine::Render()
{
    RenderBegin();

    m_TextElement.Draw();

    RenderEnd();
}
