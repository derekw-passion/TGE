#pragma once

#include "../Lib/defs.h"
#include "UI_defs.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

using namespace std;

struct ENGINE_API UIElementSettings
{
    UI4Vec padding = {0, 0, 0, 0};
    UI4Vec margin = {0, 0, 0, 0};
};

class ENGINE_API UIElement
{
protected:
    sf::FloatRect m_Rect = sf::FloatRect(0, 0, 0, 0);
    UIElementSettings m_UISettings;

public:
    virtual void Update() = 0;

public:
    inline sf::FloatRect GetUIRect() const { return m_Rect; }
    inline void SetUIRect(sf::FloatRect rect) { m_Rect = rect; }
    inline UIElementSettings GetUIElementSettings() const { return m_UISettings; }
    inline void SetUIElementSettings(UIElementSettings settings) { m_UISettings = settings; }
};