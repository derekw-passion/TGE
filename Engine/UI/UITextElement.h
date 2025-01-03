#pragma once

#include "../Lib/defs.h"
#include "UIDrawableElement.h"
#include "../Util/FontManager.h"
#include <SFML/Graphics.hpp>

class ENGINE_API UITextElement : public UIDrawableElement, public sf::Text
{
private:
    sf::RectangleShape m_Background;
    bool m_bBackgroundVisible = false;

public:
    UITextElement();

public:
    virtual void Init(sf::RenderWindow* window);
    virtual void Update();
    virtual void Draw();
    
public:
    inline void SetBackgroundVisible(bool bVisible) { m_bBackgroundVisible = bVisible; }
    inline void SetBackgroundColor(sf::Color color) { m_Background.setFillColor(color); }
};