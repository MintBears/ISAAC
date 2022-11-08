#pragma once
#include "CObj.h"


class CTexture;
class CAnimator;
class CMap;

class CPlayer :
    public CObj
{
public:
    CPlayer(Vec2 _vPos, Vec2 _vScale);
    virtual ~CPlayer();

private:
    //캐릭터 추가 이미지
    CAnimator*      m_SubAnimator;
    CMap*           m_pMap;
    
    //이동속도
    FLOAT           m_fSpeed;    

    //채력
    UINT            m_iHp;

    //사격 관련
    FLOAT           m_fAttackSpeed;
    FLOAT           m_CurAttackTime;
    bool            m_bIsAttack;

    //충돌 관련
    FLOAT           m_fCollisionTime;
    FLOAT           m_fInvincibleTime;
    bool            m_bisCollision;

public:

    void SetSpeed(FLOAT _fSpeed) { m_fSpeed = _fSpeed; }
    FLOAT GetSpeed() { return m_fSpeed; }

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

