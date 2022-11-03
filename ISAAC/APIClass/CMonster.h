#pragma once
#include "CObj.h"

class CPlayer;
class CTexture;
class CMonster :
    public CObj
{
public:
    CMonster();
    virtual ~CMonster();

private:

    UINT            m_HP;

    FLOAT           m_Speed;
    CTexture*       m_pTex;

    tMonsterInfo    m_tInfo;

    //채력
    UINT            m_iHp;

    //충돌 관련
    FLOAT           m_fCollisionTime;
    FLOAT           m_fInvincibleTime;
    bool            m_bisCollision;

public:

    tMonsterInfo& GetMonsterInfo() { return m_tInfo; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CMonster)

    virtual void BeginOverlap(CCollider* _Other) override;
    virtual void OnOverlap(CCollider* _Other) override;
    virtual void EndOverlap(CCollider* _Other) override;

public:
     
};

