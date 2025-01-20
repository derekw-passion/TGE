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

    void UIText::ParseObject(CommandObject object)
    {
        sf::Color start, end;
        bool gradient = false, bold = false, italic = false;

        for(size_t i = 0; i < object.commands.size(); i++)
        {
            const auto& cmd = object.commands[i];
            const auto& args = object.args;

            // color
            if(cmd == "c")
            {
                for(size_t j = 0; j < args[i].size()-1; j++)
                {
                    int arg = stoi(args[i][j]);
                    switch(j)
                    {
                        case 0:
                            start.r = arg;
                            break;
                        case 1:
                            start.g = arg;
                            break;
                        case 2:
                            start.b = arg;
                            break;
                        case 3:
                            start.a = arg;
                            break;
                        default:
                            break;
                    }
                }
            }
            
            // bold
            else if(cmd == "b")
            {
                bold = true;
            }

            // italic
            else if(cmd == "i")
            {
                italic = true;
            }

            // gradient
            else if(cmd == "grad")
            {
                gradient = true;

                for(size_t j = 0; j < args[i].size()-1; j++)
                {
                    int arg = stoi(args[i][j]);
                    switch(j)
                    {
                        case 0:
                            start.r = arg;
                            break;
                        case 1:
                            start.g = arg;
                            break;
                        case 2:
                            start.b = arg;
                            break;
                        case 3:
                            start.a = arg;
                            break;
                        case 4:
                            end.r = arg;
                            break;
                        case 5:
                            end.g = arg;
                            break;
                        case 6:
                            end.b = arg;
                            break;
                        case 7:
                            end.a = arg;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        string objVal = object.value;
        sf::Uint32 style = (bold ? sf::Text::Bold : sf::Text::Regular) | (italic ? sf::Text::Italic : sf::Text::Regular);

        if(gradient)
        {
            sf::Color color = start;
            sf::Color diff;
            diff.r = (end.r - start.r) / objVal.size();
            diff.g = (end.g - start.g) / objVal.size();
            diff.b = (end.b - start.b) / objVal.size();
            diff.a = (end.a - start.a) / objVal.size();

            for(size_t j = 0; j < objVal.size(); j++)
            {
                color += diff; // at the start of the loop seems to work better than at the end
                sf::Text t = sf::Text(*this);
                t.setFillColor(color);
                t.setString(objVal[j]);
                t.setStyle(style);

                m_TextElems.push_back(t);
            }
        }

        else
        {
            sf::Text t = sf::Text(*this);
            t.setFillColor(start);
            t.setStyle(style);
            t.setString(objVal);

            m_TextElems.push_back(t);
        }
    }

    void UIText::Init(sf::RenderWindow *window)
    {
        UIDrawableElement::Init(window);
    }

    void UIText::Update()
    {
        UIDrawableElement::Update();
        UpdateBackground();

        for (const auto &text : m_TextElems)
        {
            if (text.getGlobalBounds().height > m_Rect.inner.height)
            {
                m_Rect.inner.height = text.getGlobalBounds().height;
            }
        }

        m_Rect.outer.height =
            m_Rect.inner.height + m_Rect.padding.top + m_Rect.padding.bottom;

        float addX = 0;
        for (auto &text : m_TextElems)
        {
            // temporary solution to height problem
            text.setPosition(m_Rect.inner.left + addX, m_Rect.inner.top - text.getGlobalBounds().height / 3);
            addX += text.getGlobalBounds().width;

            if (text.getString().getSize() == 1)
            {
                // sf::Glyph::advance doesn't seem to work, so this is a temporary solution
                addX += (text.getCharacterSize() / 8.f) * text.getLetterSpacing();
            }
        }

        m_Rect.outer.width = addX + m_Rect.padding.left + m_Rect.padding.right;
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
                ParseObject(objs[i]);
            }
        }
    }
} // namespace TGE