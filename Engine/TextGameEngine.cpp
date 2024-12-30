#include "TextGameEngine.h"
#include "../Lib/Logger.h"

TextGameEngine::TextGameEngine() {}
TextGameEngine::~TextGameEngine() {}

void TextGameEngine::Render()
{
    
}

void TextGameEngine::HandleInput()
{

}

void TextGameEngine::GameLoop()
{
    HandleInput();
    Render();
}

int TextGameEngine::Start()
{
    Logger::Log(LogLevel::INFO, "Building window");
    

    
    return 0;
}