#include "Engine/TextGameEngine.h"

int main(int argc, char* argv[])
{
    TextGameEngine engine;
    if(engine.Start() == 0)
    {
        return 0;
    }
    else
        return -1;
}