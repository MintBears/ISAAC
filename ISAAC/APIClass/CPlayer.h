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
    FLOAT           m_fAttackSpeed;
    CAnimator*      m_SubAnimator;
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

