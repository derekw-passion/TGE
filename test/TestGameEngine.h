#pragma once

#include "../Engine/TextGameEngine.h"
#include "test_defs.h"

class TestGameEngine : public TextGameEngine
{
protected:
    int Init() override;
    void HandleInput(sf::Event event) override;
    void Render() override;

public:
    TestGameEngine();
    ~TestGameEngine();
};