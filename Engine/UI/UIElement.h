#pragma once

#include "../defs.h"
#include "UI_defs.h"
#include <SFML/Window.hpp>

namespace TGE
{
    class ENGINE_API UIElement
    {
    private:
        UIFRect m_PctRect;
        bool m_bInitialized = false;
        UIDebugRect m_DebugRect;

    protected:
        UIIRect m_PixelRect;
        sf::RenderWindow* m_pWindow;
        bool m_bCenteredHorizontal = false;
        bool m_bCenteredVertical = false;

    protected:
        void Recenter();

    public:
        bool CenteredHorizontal = false;
        bool CenteredVertical = false;

    public:
        virtual void Init(sf::RenderWindow* window);
        virtual void Update();
        virtual void Draw();
        virtual void Select() = 0;
        virtual void Deselect() = 0;

    public:
        inline UIIRect GetUIPixelRect() { return m_PixelRect; }
        inline UIFRect GetUIPctRect() { return m_PctRect; }
        inline UIDebugRect GetDebugRect() { return m_DebugRect; }
        inline bool GetDebug() const { return m_DebugRect.visible; }
        inline void SetDebug(bool debug) { m_DebugRect.visible = debug; }

    public:
        void SetUIPixelPosition(unsigned int x, unsigned int y);
        void SetUIPctPosition(float xpct, float ypct);
        void SetUIPixelSize(unsigned int width, unsigned int height);
        void SetUIPctSize(float widthpct, float heightpct);
        inline void SetUIPadding(UI4IVec padding) { m_PixelRect.padding = padding; }
        void Center(bool horizontal = true, bool vertical = true);
    };
} // namespace TGE