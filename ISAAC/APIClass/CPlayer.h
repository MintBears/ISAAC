#pragma once
#include "CObj.h"


class CTexture;

class CPlayer :
    public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

private:
    FLOAT           m_fSpeed;    
    CAnimator*      m_SubAnimator;

    //사격 관련
    FLOAT           m_fAttackSpeed;
    FLOAT           m_CurAttackTime;
    bool            m_bIsAttack;


public:

    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CPlayer)

    virtual void BeginOverlap(CCollider* _Other) override;
    virtual void OnOverlap(CCollider* _Other) override;
    virtual void EndOverlap(CCollider* _Other) override;

private:
    void Move();
    void Ani();
    void Attack();

};

