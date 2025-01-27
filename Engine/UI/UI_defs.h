#pragma once

#include "../defs.h"
#include <SFML/Graphics.hpp>

namespace TGE
{
    struct ENGINE_API UI4IVec
    {
        int top = 0;
        int right = 0;
        int bottom = 0;
        int left = 0;

        UI4IVec(int top, int right, int bottom, int left)
        {
            this->top = top;
            this->right = right;
            this->bottom = bottom;
            this->left = left;
        }
    };
    struct ENGINE_API UI4FVec
    {
        float top = 0;
        float right = 0;
        float bottom = 0;
        float left = 0;

        UI4FVec(float top, float right, float bottom, float left)
        {
            this->top = top;
            this->right = right;
            this->bottom = bottom;
            this->left = left;
        }
    };

    struct ENGINE_API UIIRect
    {
        sf::IntRect inner = sf::IntRect(0, 0, 0, 0);
        sf::IntRect outer = sf::IntRect(0, 0, 0, 0);
        UI4IVec padding = UI4IVec(0, 0, 0, 0);
    };
    struct ENGINE_API UIFRect
    {
        sf::FloatRect inner = sf::FloatRect(0, 0, 0, 0);
        sf::FloatRect outer = sf::FloatRect(0, 0, 0, 0);
        UI4IVec padding = UI4IVec(0, 0, 0, 0);
    };


    struct ENGINE_API UIDrawableRect
    {
        sf::RectangleShape inner = sf::RectangleShape();
        sf::RectangleShape outer = sf::RectangleShape();
        bool visible = false;
    };

    struct ENGINE_API UIDebugRect : public UIDrawableRect
    {
        sf::Color debugColor = sf::Color::Red;
    };
} // namespace TGE