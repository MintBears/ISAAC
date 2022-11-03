#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2    m_vLeftRightPadding;
    Vec2    m_vTopBottomPadding;
    Vec2    m_vInnerPadding;


    Vec2    m_vPressPos;

    bool    m_bIsMove;

public:
    void SetIsMove(bool _bIsMove) { m_bIsMove = _bIsMove; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnClicked() override;

public:
    CLONE(CPanelUI)

public:
    CPanelUI();
    ~CPanelUI();
};

