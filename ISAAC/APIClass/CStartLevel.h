#pragma once
#include "CLevel.h"
class CPlayer;
class CPanelUI;
class CCameraObj;
class CMap;

class CStartLevel :
    public CLevel
{
public:
    CStartLevel();
    ~CStartLevel();

private:
    CPlayer*        m_Player;
    CCameraObj*     m_pCameraRoom;
    CMap*           m_pMap;

public: 
    CPlayer* GetPlayer() { return m_Player; }
    CMap* GetMap() { return m_pMap; }

public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter();           //������ �����Ҷ� ȣ��
    virtual void Exit();            //������ ����� ȣ��

private:
    void CreateUI();
};

