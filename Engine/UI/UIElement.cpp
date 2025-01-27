#include "UIElement.h"

namespace TGE
{
    void UIElement::Init(sf::RenderWindow *window)
    {
        if(window == nullptr)
        {
            throw "Trying to initialized UIElement with null window";
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

    void UIElement::Update()
    {
        if(!m_bInitialized)
        {
            throw "UIElement not initialized";
        }

        m_PixelRect.inner.left = m_PixelRect.outer.left + m_PixelRect.padding.left;
        m_PixelRect.inner.top = m_PixelRect.outer.top + m_PixelRect.padding.top;
        m_PixelRect.inner.width = m_PixelRect.outer.width - m_PixelRect.padding.left - m_PixelRect.padding.right;
        m_PixelRect.inner.height = m_PixelRect.outer.height - m_PixelRect.padding.top - m_PixelRect.padding.bottom;

        m_PctRect.inner.left = m_PctRect.outer.left / m_pWindow->getSize().x;
        m_PctRect.inner.top = m_PctRect.outer.top / m_pWindow->getSize().y;
        m_PctRect.inner.width = m_PctRect.outer.width / m_pWindow->getSize().x;
        m_PctRect.inner.height = m_PctRect.outer.height / m_pWindow->getSize().y;


        if(m_DebugRect.visible)
        {
            m_DebugRect.inner.setPosition(m_PixelRect.inner.left, m_PixelRect.inner.top);
            m_DebugRect.inner.setSize(sf::Vector2f(m_PixelRect.inner.width, m_PixelRect.inner.height));
            m_DebugRect.outer.setPosition(m_PixelRect.outer.left, m_PixelRect.outer.top);
            m_DebugRect.outer.setSize(sf::Vector2f(m_PixelRect.outer.width, m_PixelRect.outer.height));
        }
    }

    void UIElement::Draw()
    {
        if(!m_bInitialized)
        {
            throw "UIElement not initialized";
        }

        if(m_DebugRect.visible)
        {
            m_pWindow->draw(m_DebugRect.inner);
            m_pWindow->draw(m_DebugRect.outer);
        }
    }

    void UIElement::SetUIPixelPosition(unsigned int x, unsigned int y)
    {
        if(!m_bInitialized)
        {
            throw "UIElement not initialized";
        }

        if(x < 0 || x > m_pWindow->getSize().x) x = m_pWindow->getSize().x / 2;
        if(y < 0 || y > m_pWindow->getSize().y) y = m_pWindow->getSize().y / 2;

        m_PixelRect.outer.left = x;
        m_PixelRect.outer.top = y;
        m_PctRect.outer.left = (float)x / m_pWindow->getSize().x;
        m_PctRect.outer.top = (float)y / m_pWindow->getSize().y;
    }

    void UIElement::SetUIPctPosition(float xpct, float ypct)
    {
        if(!m_bInitialized)
        {
            throw "UIElement not initialized";
        }

        if(xpct < 0 || xpct > 1) xpct = 0.5;
        if(ypct < 0 || ypct > 1) ypct = 0.5;

        m_PctRect.outer.left = xpct;
        m_PctRect.outer.top = ypct;
        m_PixelRect.outer.left = m_pWindow->getSize().x * xpct;
        m_PixelRect.outer.top = m_pWindow->getSize().y * ypct; 
    }

    void UIElement::SetUIPixelSize(unsigned int width, unsigned int height)
    {
        if(!m_bInitialized)
        {
            throw "UIElement not initialized";
        }

        if(width < 0 || width > m_pWindow->getSize().x) width = m_pWindow->getSize().x / 2;
        if(height < 0 || height > m_pWindow->getSize().y) height = m_pWindow->getSize().y / 2;

        m_PixelRect.outer.width = width;
        m_PixelRect.outer.height = height;
        m_PctRect.outer.width = (float)width / m_pWindow->getSize().x;
        m_PctRect.outer.height = (float)height / m_pWindow->getSize().y;
    }

    void UIElement::SetUIPctSize(float widthpct, float heightpct)
    {
        if(!m_bInitialized)
        {
            throw "UIElement not initialized";
        }

        if(widthpct < 0 || widthpct > 1) widthpct = 0.5;
        if(heightpct < 0 || heightpct > 1) heightpct = 0.5;

        m_PctRect.outer.width = widthpct;
        m_PctRect.outer.height = heightpct;
        m_PixelRect.outer.width = m_pWindow->getSize().x * widthpct;
        m_PixelRect.outer.height = m_pWindow->getSize().y * heightpct;
    }
} // namespace TGE