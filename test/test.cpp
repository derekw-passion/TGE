#include "TestGameEngine.h"
#include "../Lib/Logger.h"

int main(int argc, char* argv[])
{
    TestGameEngine engine;
    if(engine.Start() == 0)
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