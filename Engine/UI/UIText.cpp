#include "UIText.h"

namespace TGE
{
    UIText::UIText()
    {
        m_Background.setFillColor(sf::Color::Transparent);
        m_Background.setOutlineColor(sf::Color::White);
        m_Background.setOutlineThickness(1);
        m_bBackgroundVisible = false;
    }

    void UIText::UpdateBackground()
    {
        m_Background.setPosition(m_Rect.inner.left, m_Rect.inner.top);
        m_Background.setSize(sf::Vector2f(m_Rect.inner.width, m_Rect.inner.height));
    }

    void UIText::ParseCommand(string command, vector<string> args, UITextSettings& outSettings)
    {
        // color
        if(command == "c")
        {
            for(size_t j = 0; j < args.size()-1; j++)
            {
                int value = stoi(args[j]);
                switch(j)
                {
                    case 0:
                        outSettings.color.r = value;
                        break;
                    case 1:
                        outSettings.color.g = value;
                        break;
                    case 2:
                        outSettings.color.b = value;
                        break;
                    case 3:
                        outSettings.color.a = value;
                        break;
                    default:
                        break;
                }
            }
        }
        
        // bold
        else if(command == "b")
        {
            outSettings.bold = true;
        }

        // italic
        else if(command == "i")
        {
            outSettings.italic = true;
        }
    }

    void UIText::Init(sf::RenderWindow* window)
    {
        UIDrawableElement::Init(window);
    }

    void UIText::Update()
    {
        // get the width and height of the total text
        m_Rect.inner.width = 0;
        for(const auto& text : m_TextElems)
        {
            m_Rect.inner.width += text.getLocalBounds().width;
        }

        // update outer rect
        m_Rect.outer.width = m_Rect.inner.width + m_Rect.padding.left + m_Rect.padding.right;
        m_Rect.outer.height = getGlobalBounds().height + m_Rect.padding.top + m_Rect.padding.bottom;

        UIDrawableElement::Update();
        UpdateBackground();

        float currentX = m_Rect.inner.left;
        for(auto& text : m_TextElems)
        {
            // text.getGlobalBounds().height / 3 to center vertically to compensate for weird text positioning by SFML
            text.setPosition(currentX, m_Rect.inner.top - text.getGlobalBounds().height / 3);
            currentX = currentX + text.getGlobalBounds().width;
        }
    }

    void UIText::Draw()
    {
        UIDrawableElement::Draw();

        if (m_bBackgroundVisible)
        {
            m_pWindow->draw(m_Background);
        }

        for(auto& text : m_TextElems)
        {
            m_pWindow->draw(text);
        }
    }

    void UIText::SetText(string text)
    {
        vector<CommandObject> objs;
        string newStr = "";
        CommandParser::ParseMultipleObjects(text, objs);

        if(objs.empty())
        {
            setString(text);

            sf::Text t = sf::Text(*this);
            t.setFillColor(sf::Color::White);
            t.setString(text);

            m_TextElems.push_back(t);
        }

        else
        {
            for(size_t i = 0; i < objs.size(); i++)
            {
                const auto& obj = objs[i];

                UITextSettings settings;

                for(size_t j = 0; j < obj.commands.size(); j++)
                {
                    ParseCommand(obj.commands[j], obj.args[j], settings);
                }

                string objVal = obj.value;

                sf::Text t = sf::Text(*this);
                t.setFillColor(settings.color);
                t.setStyle((settings.bold ? sf::Text::Bold : sf::Text::Regular) | (settings.italic ? sf::Text::Italic : sf::Text::Regular));
                t.setString(objVal);
                m_TextElems.push_back(t);

                newStr += objVal;
            }

            setString(newStr);
        }
    } 
} // namespace TGE