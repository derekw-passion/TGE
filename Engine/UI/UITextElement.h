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

private:
    void UpdateBackground();

public:
    UITextElement();

public:
    virtual void Init(sf::RenderWindow* window);
    virtual void Update();
    virtual void Draw();
    
public:
    inline void SetBackgroundVisible(bool visible) { m_bBackgroundVisible = visible; }
    inline void SetBackground(sf::RectangleShape background) { m_Background = background; }
};