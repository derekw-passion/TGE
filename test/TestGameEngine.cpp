#include "TestGameEngine.h"

TestGameEngine::TestGameEngine()
{
    settings.title = "Test";
}
TestGameEngine::~TestGameEngine() = default;

int TestGameEngine::Init()
{
    Logger::Log(LogLevel::INFO, "Loading fonts");
    return FontManager::LoadFont(FONT_ARIAL, FONT_ARIAL_PATH);
}
void TestGameEngine::HandleInput(sf::Event event) {}
void TestGameEngine::Render()
{
    RenderBegin();

    sf::Text text;
    text.setFont(*FontManager::GetFont(FONT_ARIAL));
    text.setString("Hello, World!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 0);
    GetWindow().draw(text);

    // TODO: Add input options here

    RenderEnd();
}
