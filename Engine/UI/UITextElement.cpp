#include "UITextElement.h"

UITextElement::UITextElement()
{
    m_Background.setFillColor(sf::Color::Transparent);
    m_Background.setOutlineColor(sf::Color::White);
    m_Background.setOutlineThickness(1);
    m_bBackgroundVisible = false;
}

void UITextElement::Init(sf::RenderWindow* window)
{
    UIDrawableElement::Init(window);

    m_Background.setPosition(m_Rect.left, m_Rect.top);
    m_Background.setSize(sf::Vector2f(m_Rect.width, m_Rect.height));
}

void UITextElement::Update()
{
    UIDrawableElement::Update();

    m_Rect = getGlobalBounds();
    m_Background.setPosition(m_Rect.left, m_Rect.top);
    m_Background.setSize(sf::Vector2f(m_Rect.width, m_Rect.height));
}

void UITextElement::Draw()
{
    UIDrawableElement::Draw();

    if (m_bBackgroundVisible)
    {
        m_pWindow->draw(m_Background);
    }

    m_pWindow->draw(*this);
}