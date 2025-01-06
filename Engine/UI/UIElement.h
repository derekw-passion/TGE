#pragma once

#include "../defs.h"
#include "UI_defs.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

using namespace std;

class ENGINE_API UIElement
{
protected:
    UIRect m_Rect;

public:
    virtual void Update();

public:
    inline UIRect& GetUIRect() { return m_Rect; }
    void SetUIPosition(float x, float y);
};