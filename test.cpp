#include "Engine/TextGameEngine.h"
#include "Lib/Logger.h"

int main(int argc, char* argv[])
{
    TextGameEngine engine;
    if(engine.Start(
        sf::VideoMode({800, 600}), 
        "Test") == 0)
    {
        Logger::Log(LogLevel::INFO, "Exiting...");
        return 0;
    }
    else
    {
        Logger::Log(LogLevel::ERROR, "Exiting...");
        return -1;
    }
}