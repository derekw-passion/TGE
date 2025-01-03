#include "UIDrawableElement.h"

void UIDrawableElement::Init(sf::RenderWindow *window)
{
    if(window == nullptr)
    {
        throw "Trying to initialized UIDrawableElement with null window";
    }

    m_pWindow = window;
    m_bInitialized = true;
}

void UIDrawableElement::Update()
{
    if(!m_bInitialized)
    {
        throw "UIDrawableElement not initialized";
    }
}

void UIDrawableElement::Draw()
{
    if(!m_bInitialized)
    {
        throw "UIDrawableElement not initialized";
    }
}
