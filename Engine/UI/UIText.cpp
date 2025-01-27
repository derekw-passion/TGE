#include "UIText.h"
#include <stdlib.h>

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
        m_Background.setPosition(m_PixelRect.inner.left, m_PixelRect.inner.top);
        m_Background.setSize(sf::Vector2f(m_PixelRect.inner.width, m_PixelRect.inner.height));
    }

    void UIText::ExecuteCommandObject(CommandObject object)
    {
        sf::Color start, end;
        bool gradient = false;
        bool rainbow = false;
        bool random = false;
        bool bold = false, italic = false;

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

            // rainbow
            else if(cmd == "rbw")
            {
                rainbow = true;
            }

            // random
            else if(cmd == "rnd")
            {
                random = true;
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
                sf::Text t = sf::Text(*this);
                t.setFillColor(color);
                t.setString(objVal[j]);
                t.setStyle(style);

                m_TextElems.push_back(t);

                color.r += diff.r;
                color.g += diff.g;
                color.b += diff.b;
                color.a += diff.a;
            }
        }

        else if(rainbow)
        {
            vector<sf::Color> rainbowColors = {
                sf::Color::Red,
                sf::Color::Yellow,
                sf::Color::Green,
                sf::Color::Cyan,
                sf::Color::Blue,
                sf::Color::Magenta
            };

            size_t colorIndex = 0;
            for(size_t j = 0; j < objVal.size(); j++)
            {
                sf::Text t = sf::Text(*this);
                t.setFillColor(rainbowColors[colorIndex]);
                t.setString(objVal[j]);
                t.setStyle(style);

                m_TextElems.push_back(t);

                colorIndex++;
                if(colorIndex == rainbowColors.size())
                {
                    colorIndex = 0;
                }
            }
        }

        else if(random)
        {
            for(size_t j = 0; j < objVal.size(); j++)
            {
                sf::Text t = sf::Text(*this);
                t.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
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
        UIElement::Init(window);
    }

    void UIText::Update()
    {
        UIElement::Update();
        UpdateBackground();

        for (const auto &text : m_TextElems)
        {
            if (text.getGlobalBounds().height > m_PixelRect.inner.height)
            {
                m_PixelRect.inner.height = text.getGlobalBounds().height;
            }
        }

        m_PixelRect.outer.height =
            m_PixelRect.inner.height + m_PixelRect.padding.top + m_PixelRect.padding.bottom;

        float addX = 0;
        for (auto &text : m_TextElems)
        {
            // temporary height fix
            text.setPosition(m_PixelRect.inner.left + addX, m_PixelRect.inner.top - (float)m_PixelRect.inner.height / 3);
            addX += text.getGlobalBounds().width;

            if (text.getString().getSize() == 1)
            {
                // sf::Glyph::advance doesn't seem to work, so this is a temporary solution
                addX += (text.getCharacterSize() / 10.f) * text.getLetterSpacing();
            }
        }

        m_PixelRect.outer.width = addX + m_PixelRect.padding.left + m_PixelRect.padding.right;
    }

    void UIText::Draw()
    {
        UIElement::Draw();

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
                ExecuteCommandObject(objs[i]);
            }
        }
    }
} // namespace TGE