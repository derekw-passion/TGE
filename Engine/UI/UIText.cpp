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

                int r, g, b, a = 255;
                bool bold = false;
                bool italic = false;

                int cmdNum = 0;
                for(const auto& cmd : obj.commands)
                {
                    // color command
                    if(cmd == "c")
                    {
                        for(size_t j = 0; j < obj.args[cmdNum].size()-1; j++)
                        {
                            string arg = obj.args[cmdNum][j];
                            int value = stoi(arg);

                            switch(j)
                            {
                                case 0:
                                    r = value;
                                    break;
                                case 1:
                                    g = value;
                                    break;
                                case 2:
                                    b = value;
                                    break;
                                case 3:
                                    a = value;
                                    break;
                                default:
                                    break;
                            }
                        }
                    }

                    else if(cmd == "b")
                    {
                        bold = true;
                    }

                    else if(cmd == "i")
                    {
                        italic = true;
                    }

                    cmdNum++;
                }

                vector<string> args = obj.args[0];
                string objVal = args.size() > 0 ? args.back() : "";
                
                if(objVal.empty())
                {
                    continue;
                }

                sf::Text t = sf::Text(*this);
                t.setFillColor(sf::Color(r, g, b, a));
                t.setStyle((bold ? sf::Text::Bold : sf::Text::Regular) | (italic ? sf::Text::Italic : sf::Text::Regular));
                t.setString(objVal);

                m_TextElems.push_back(t);
                newStr += objVal;
            }

            setString(newStr);
        }
    } 
} // namespace TGE