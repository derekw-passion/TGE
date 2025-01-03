#pragma once

#include "../Lib/defs.h"
#include "UIElement.h"

class ENGINE_API UIDrawableElement : public UIElement
{
private:
    bool m_bInitialized = false;

protected:
    sf::RenderWindow* m_pWindow;

public:
    virtual void Init(sf::RenderWindow* window);
    virtual void Update();
    virtual void Draw();
};