#include "TestGameEngine.h"

TestGameEngine::TestGameEngine() = default;
TestGameEngine::~TestGameEngine() = default;

void TestGameEngine::HandleInput(sf::Event event) {}

void TestGameEngine::Render()
{
    TextGameEngine::Render();
}
