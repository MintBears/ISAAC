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

    virtual void Enter();           //������ �����Ҷ� ȣ��
    virtual void Exit();            //������ ����� ȣ��

private:
    void CreateUI();
};

