#include "UIElement.h"

namespace TGE
{
    void UIElement::Update()
    {
        m_Rect.inner.left = m_Rect.outer.left + m_Rect.padding.left;
        m_Rect.inner.top = m_Rect.outer.top + m_Rect.padding.top;
        m_Rect.inner.width = m_Rect.outer.width - m_Rect.padding.left - m_Rect.padding.right;
        m_Rect.inner.height = m_Rect.outer.height - m_Rect.padding.top - m_Rect.padding.bottom;
    }

    void UIElement::SetUIPosition(float x, float y)
    {
        m_Rect.outer.left = x;
        m_Rect.outer.top = y;
    }
} // namespace TGE