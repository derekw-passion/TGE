#pragma once

#include "../Lib/defs.h"
#include <SFML/Graphics.hpp>

struct ENGINE_API UI4Vec
{
    float top = 0;
    float right = 0;
    float bottom = 0;
    float left = 0;

    UI4Vec(float top, float right, float bottom, float left)
    {
        this->top = top;
        this->right = right;
        this->bottom = bottom;
        this->left = left;
    }
};

struct ENGINE_API UIRect
{
    sf::FloatRect inner = sf::FloatRect(0, 0, 0, 0);
    sf::FloatRect outer = sf::FloatRect(0, 0, 0, 0);
    UI4Vec padding = UI4Vec(0, 0, 0, 0);
};

struct ENGINE_API UIDrawableRect
{
    sf::RectangleShape inner;
    sf::RectangleShape outer;
    bool visible = false;
};

struct ENGINE_API UIDebugRect : public UIDrawableRect
{
    sf::Color debugColor = sf::Color::Red;
};