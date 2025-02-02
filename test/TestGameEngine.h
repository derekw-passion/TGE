#pragma once

#include "../Engine/TextGameEngine.h"
#include "../Engine/UI/UIText.h"
#include "../Engine/UI/UITextBlock.h"
#include "test_defs.h"

using namespace TGE;

class TestGameEngine : public TGE::TextGameEngine
{
private:
    UIText m_Text;
    UITextBlock m_TextBlock;

protected:
    int Init() override;
    void HandleInput(sf::Event event) override;
    void Update() override;
    void Render() override;

public:
    TestGameEngine();
    ~TestGameEngine();
};