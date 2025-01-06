#pragma once

#include "../Engine/TextGameEngine.h"
#include "../Engine/UI/UIText.h"
#include "test_defs.h"

class TestGameEngine : public TextGameEngine
{
private:
    UIText m_Text;

protected:
    int Init() override;
    void HandleInput(sf::Event event) override;
    void Update() override;
    void Render() override;

public:
    TestGameEngine();
    ~TestGameEngine();
};