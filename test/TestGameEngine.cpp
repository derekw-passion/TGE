#include "TestGameEngine.h"

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
    
    m_Text.Init(GetWindow());
    m_Text.setFont(*FontManager::GetFont(FONT_ARIAL));
    m_Text.setFillColor(sf::Color::White);
    m_Text.setCharacterSize(24);
    
    sf::RectangleShape bg;
    bg.setOutlineColor(sf::Color::Green);
    bg.setOutlineThickness(1);
    bg.setFillColor(sf::Color(0, 255, 0, 100));
    m_Text.SetBackground(bg);
    m_Text.SetBackgroundVisible(false);
    m_Text.GetUIRect().padding = UI4Vec(10, 10, 10, 10);
    m_Text.SetDebug(true);
    m_Text.SetText("/c:0:255:0[Hello ] /c:0:0:255[World ] /c:255:255:0/b/i[bold! ] /grad:0:255:0:255:0:0:255:255[gradient]");

    return 0;
}
void TestGameEngine::HandleInput(sf::Event event) {}
void TestGameEngine::Update()
{
    m_Text.Update();
}
void TestGameEngine::Render()
{
    RenderBegin();

    m_Text.Draw();

    RenderEnd();
}
