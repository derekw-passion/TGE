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

    void UIText::Init(sf::RenderWindow* window)
    {
        UIDrawableElement::Init(window);
    }

    void UIText::Update()
    {
        m_Rect.outer.width = getGlobalBounds().width + m_Rect.padding.left + m_Rect.padding.right;
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
        UITextCommandList commands;
        string newStr = "";
        CommandParser::ParseCommands(text, commands);

        if(commands.empty())
        {
            setString(text);

            sf::Text t = sf::Text(*this);
            t.setFillColor(sf::Color::White);
            t.setString(text);

            m_TextElems.push_back(t);
        }

        else
        {
            // go through each command
            for(const auto& command : commands)
            {
                // color command
                if(command.first == "c")
                {
                    int r, g, b, a = 255;

                    for(size_t i = 0; i < command.second.size()-1; i++)
                    {
                        switch(i)
                        {
                            case 0:
                                r = stoi(command.second[i]);
                                break;
                            case 1:
                                g = stoi(command.second[i]);
                                break;
                            case 2:
                                b = stoi(command.second[i]);
                                break;
                            case 3:
                                a = stoi(command.second[i]);
                                break;
                            default:
                                break;
                        }
                    }

                    string obj = command.second[command.second.size()-1];

                    sf::Text t = sf::Text(*this);
                    t.setFillColor(sf::Color(r, g, b, a));
                    t.setString(obj);

                    m_TextElems.push_back(t);
                    newStr += obj;
                }
            }

            setString(newStr);
        }
    } 
} // namespace TGE