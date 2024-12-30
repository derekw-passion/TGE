#pragma once

#include "../Lib/defs.h"
#include <string>

using namespace std;

class ENGINE_API TextGameEngine
{
private:
    void Render();
    void HandleInput();
    void GameLoop();

public:  
    TextGameEngine();
    ~TextGameEngine();

    int Start();
};