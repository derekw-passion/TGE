#pragma once

#include "../defs.h"
#include "UIElement.h"
#include "../FontManager.h"
#include "../Util/CommandParser.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace TGE
{
    struct SFMLTextSettings
    {
        sf::Color color;
        bool bold, italic;
    };

    class ENGINE_API UIText : public UIElement, public sf::Text
    {
    private:
        sf::RectangleShape m_Background;
        bool m_bBackgroundVisible = false;
        vector<sf::Text> m_TextElems;

    private:
        void UpdateBackground();
        void ExecuteCommandObject(CommandObject object);

    public:
        UIText();
        UIText(vector<sf::Text> textElems) : m_TextElems(textElems) {}

    public:
        virtual void Init(sf::RenderWindow* window);
        virtual void SetText(string text);
        virtual void Update();
        virtual void Draw();
        virtual void Select();
        virtual void Deselect();
        
    public:
        inline void SetBackgroundVisible(bool visible) { m_bBackgroundVisible = visible; }
        inline void SetBackground(sf::RectangleShape background) { m_Background = background; }
        inline vector<sf::Text>& GetRawElements() { return m_TextElems; }
    };
} // namespace TGE