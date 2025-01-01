#include "Engine/TextGameEngine.h"

int main(int argc, char* argv[])
{
    TextGameEngine engine;
    if(engine.Start(
        sf::VideoMode({800, 600}), 
        "Test") == 0)
    {
        return 0;
    }
    else
        return -1;
    return 0;
}