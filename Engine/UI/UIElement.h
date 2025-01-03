#pragma once

#include "../Lib/defs.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

class ENGINE_API UIElement
{
protected:
    sf::FloatRect m_Rect;

public:
    virtual void Update() = 0;

public:
    inline sf::FloatRect GetRect() { return m_Rect; }
    inline void SetRect(sf::FloatRect rect) { m_Rect = rect; }
};