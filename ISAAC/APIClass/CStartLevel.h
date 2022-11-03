#pragma once
#include "CLevel.h"
class CPlayer;

class CStartLevel :
    public CLevel
{
public:
    CStartLevel();
    ~CStartLevel();

private:
    CPlayer* Player;

public: 
    CPlayer* GetPlayer() { return Player; }

public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter();           //������ �����Ҷ� ȣ��
    virtual void Exit();            //������ ����� ȣ��

private:
    void CreateUI();
};

