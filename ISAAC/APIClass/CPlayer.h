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
    //ĳ���� �߰� �̹���
    CAnimator*      m_SubAnimator;
    CMap*           m_pMap;
    
    //�̵��ӵ�
    FLOAT           m_fSpeed;    

    //ä��
    UINT            m_iHp;

    //��� ����
    FLOAT           m_fAttackSpeed;
    FLOAT           m_CurAttackTime;
    bool            m_bIsAttack;

    //�浹 ����
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

