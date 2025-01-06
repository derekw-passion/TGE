#include "FontManager.h"

namespace TGE
{
    map<string, sf::Font*> FontManager::m_Fonts;

    int FontManager::LoadFont(string name, string path)
    {
        sf::Font* pFont = new sf::Font();
        if(!pFont->loadFromFile(path))
        {
            Logger::Log(LogLevel::ERROR, "Failed to load font '" + name + "' from path '" + path + "'");
            delete pFont;
            return -1;
        }
        else
        {
            m_Fonts[name] = pFont;
            return 0;
        }
    }

    sf::Font* FontManager::GetFont(string name)
    {
        if(m_Fonts.at(name)->getInfo().family == "")
        {
            throw std::runtime_error("Font '" + name + "' not loaded");
        }

        return m_Fonts.at(name);
    }

    void FontManager::UnloadFonts()
    {
        for(auto& font : m_Fonts)
        {
            delete font.second;
        }
        m_Fonts.clear();
    }
} // namespace TGE