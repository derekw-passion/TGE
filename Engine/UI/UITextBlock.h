#pragma once

#include "../defs.h"
#include "UI_defs.h"
#include "UIText.h"
#include <vector>

namespace TGE
{
    class ENGINE_API UITextBlock : public UIText
    {
    private:
        vector<UIText> m_Lines;

    public:
        virtual void SetText(string text) override;
        virtual void Update() override;
        virtual void Draw() override;
        virtual void Select() override;
        virtual void Deselect() override;
    };
}