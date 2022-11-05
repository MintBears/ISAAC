#pragma once
#include "CLevel.h"
class CPlayer;
class CPanelUI;

class CStartLevel :
    public CLevel
{
public:
    CStartLevel();
    ~CStartLevel();

private:
    CPlayer* m_Player;

    CPanelUI* m_pPanelUI;

public: 
    CPlayer* GetPlayer() { return m_Player; }
    CPanelUI* GetPanelUI() { return m_pPanelUI; }

public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter();           //레벨에 진입할때 호출
    virtual void Exit();            //레벨을 벗어날때 호출

private:
    void CreateUI();
};

