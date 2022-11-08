#pragma once
#include "CLevel.h"
class CPlayer;
class CPanelUI;
class CCameraObj;

class CStartLevel :
    public CLevel
{
public:
    CStartLevel();
    ~CStartLevel();

private:
    CPlayer* m_Player;
    CCameraObj* m_pCameraRoom;

public: 
    CPlayer* GetPlayer() { return m_Player; }

public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter();           //������ �����Ҷ� ȣ��
    virtual void Exit();            //������ ����� ȣ��

private:
    void CreateUI();
};

