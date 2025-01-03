#pragma once

#include "../Lib/defs.h"

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