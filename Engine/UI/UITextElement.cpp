#include "UITextElement.h"

UITextElement::UITextElement() {
  m_Background.setFillColor(sf::Color::Transparent);
  m_Background.setOutlineColor(sf::Color::White);
  m_Background.setOutlineThickness(1);
  m_bBackgroundVisible = false;
}

void UITextElement::UpdateBackground()
{
    m_Background.setPosition(m_Rect.inner.left, m_Rect.inner.top);
    m_Background.setSize(sf::Vector2f(m_Rect.inner.width, m_Rect.inner.height));
}

void UITextElement::Init(sf::RenderWindow* window)
{
    UIDrawableElement::Init(window);
}

void UITextElement::Update()
{
    m_Rect.outer.width = getGlobalBounds().width + m_Rect.padding.left + m_Rect.padding.right;
    m_Rect.outer.height = getGlobalBounds().height + m_Rect.padding.top + m_Rect.padding.bottom;

    UIDrawableElement::Update();
    UpdateBackground();

    setPosition(m_Rect.inner.left, m_Rect.inner.top);
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