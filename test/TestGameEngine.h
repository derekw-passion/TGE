#pragma once

#include "../Engine/TextGameEngine.h"
#include "../Engine/UI/UITextElement.h"
#include "test_defs.h"

class TestGameEngine : public TextGameEngine
{
private:
    UITextElement m_TextElement;

protected:
    int Init() override;
    void HandleInput(sf::Event event) override;
    void Update() override;
    void Render() override;

public:
    TestGameEngine();
    ~TestGameEngine();
};