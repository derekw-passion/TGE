#pragma once

#include "../defs.h"
#include "UIElement.h"

namespace TGE
{
    class ENGINE_API UIDrawableElement : public UIElement
    {
    private:
        bool m_bInitialized = false;
        UIDebugRect m_DebugRect;

    protected:
        sf::RenderWindow* m_pWindow;

    public:
        virtual void Init(sf::RenderWindow* window);
        virtual void Update();
        virtual void Draw();

    public:
        inline bool GetDebug() const { return m_DebugRect.visible; }
        inline UIDebugRect& GetDebugRect() { return m_DebugRect; }
        inline void SetDebug(bool debug) { m_DebugRect.visible = debug; }
    };
} // namespace TGE