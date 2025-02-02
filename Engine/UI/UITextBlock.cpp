#include "UITextBlock.h"

void TGE::UITextBlock::SetText(string text)
{
    UIText::SetText(text);
    UIText::Update();
    m_Lines.clear();

    // break up m_TextElems into sf::Text objects for single words
    for(auto& text : GetRawElements())
    {
        // break up text into words
        vector<sf::Text> words;
        while(text.getString().find(' ') != string::npos)
        {
            sf::Text word = sf::Text(text);
            word.setString(text.getString().substring(0, text.getString().find(' ')));
            words.push_back(word);
            text.setString(text.getString().substring(text.getString().find(' ') + 1));
        }

        // add last word
        words.push_back(text);

        // compose UIText line objects
        bool bLinesComposed = false;
        while(!bLinesComposed && !words.empty())
        {
            // add words to a UIText line object until the line width is exceeded
            bool bEndLine = false;
            while(!bEndLine)
            {
                UIText line = UIText(*this);
                line.SetUIPadding(UI4IVec(0, 0, 0, 0));
                float addX = 0;
                for(auto& word : words)
                {
                    if(addX + word.getLocalBounds().width > m_PixelRect.inner.width)
                    {
                        line.Update(); // update pixel rect
                        line.SetUIPixelPosition(
                            m_PixelRect.inner.left, 
                            m_PixelRect.inner.top + line.GetUIPixelRect().outer.height);
                        m_Lines.push_back(line);
                        bEndLine = true;
                        break;
                    }

                    line.GetRawElements().push_back(word);
                    addX += word.getLocalBounds().width;
                }

                // remove used words
                for(size_t i = 0; i < line.GetRawElements().size(); i++)
                {
                    words.erase(words.begin());
                }
            }

            if(words.empty())
            {
                bLinesComposed = true;
            }
        }

        // auto set height of UITextBlock
        int heightOfLines = 0;
        for(auto& line : m_Lines)
        {
            heightOfLines += line.GetUIPixelRect().outer.height;
        }

        SetUIPixelSize(
            m_PixelRect.outer.width, 
            heightOfLines);
    }

    // clear these elements so they don't draw
    GetRawElements().clear();
}

void TGE::UITextBlock::Update()
{
    UIElement::Update();

    for(auto& line : m_Lines)
    {
        line.Update();
    }
}

void TGE::UITextBlock::Draw()
{
    UIElement::Draw();

    for(auto& line : m_Lines)
    {
        line.Draw();
    }
}

void TGE::UITextBlock::Select()
{
    for (auto& line : m_Lines)
    {
        line.Select();
    }
}

void TGE::UITextBlock::Deselect()
{
    for (auto& line : m_Lines)
    {
        line.Deselect();
    }
}