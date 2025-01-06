#include "UIDrawableElement.h"

namespace TGE
{
    void UIDrawableElement::Init(sf::RenderWindow *window)
    {
        if(window == nullptr)
        {
            throw "Trying to initialized UIDrawableElement with null window";
        }

        m_pWindow = window;

        m_DebugRect.visible = false;
        m_DebugRect.inner.setFillColor(sf::Color::Transparent);
        m_DebugRect.inner.setOutlineColor(m_DebugRect.debugColor);
        m_DebugRect.inner.setOutlineThickness(1);
        m_DebugRect.outer.setFillColor(sf::Color::Transparent);
        m_DebugRect.outer.setOutlineColor(m_DebugRect.debugColor);
        m_DebugRect.outer.setOutlineThickness(1);

        m_bInitialized = true;
    }

    void UIDrawableElement::Update()
    {
        if(!m_bInitialized)
        {
            throw "UIDrawableElement not initialized";
        }

        UIElement::Update();

        if(m_DebugRect.visible)
        {
            m_DebugRect.inner.setPosition(m_Rect.inner.left, m_Rect.inner.top);
            m_DebugRect.inner.setSize(sf::Vector2f(m_Rect.inner.width, m_Rect.inner.height));
            m_DebugRect.outer.setPosition(m_Rect.outer.left, m_Rect.outer.top);
            m_DebugRect.outer.setSize(sf::Vector2f(m_Rect.outer.width, m_Rect.outer.height));
        }
    }

    void UIDrawableElement::Draw()
    {
        if(!m_bInitialized)
        {
            throw "UIDrawableElement not initialized";
        }

        if(m_DebugRect.visible)
        {
            m_pWindow->draw(m_DebugRect.inner);
            m_pWindow->draw(m_DebugRect.outer);
        }
    }
} // namespace TGE