#include "TestGameEngine.h"

TestGameEngine::TestGameEngine()
{
    settings.title = "Test";
}
TestGameEngine::~TestGameEngine() = default;

void TestGameEngine::HandleInput(sf::Event event) {}

void TestGameEngine::Render()
{
    TextGameEngine::Render();
}
