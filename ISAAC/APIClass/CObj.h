#pragma once
#include "CEntity.h"

#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidbody;
class CAI;

class CObj :
    public CEntity
{
public:
    CObj();
    CObj(const CObj& _other);
    virtual ~CObj();

private: 
    Vec2            m_vPos;
    Vec2            m_vScale;

    CCollider*      m_Collider;
    CAnimator*      m_Animator;
    CRigidbody*     m_Rigidbody;
    CAI*            m_pAI;

    LAYER           m_eLayer;

    bool            m_Dead;
    bool            m_bIsValid;


public : 
    void SetPos(Vec2 _v) { m_vPos = _v; }
    Vec2 GetPos() { return m_vPos; }

    void SetScale(Vec2 _v) { m_vScale = _v; }
    Vec2 GetScale() { return m_vScale; }

    void SetLayerType(LAYER _elayer) { m_eLayer = _elayer; }
    LAYER GetLayerType() { return m_eLayer; }

    CCollider* GetCollider() { return m_Collider; }
    CAnimator* GetCAnimator() { return m_Animator; }
    CRigidbody* GetCRigidbody() { return m_Rigidbody; }
    CAI* GetCAI() { return m_pAI; }

    bool IsDead() { return m_Dead; }
    void SetDead();

    bool GetValid() { return m_bIsValid; }
    void SetValid(bool _bIsValid) { m_bIsValid = _bIsValid; }


public : 
    virtual void tick();
    virtual void final_tick();
    virtual void render(HDC _dc);

    virtual CObj* Clone() = 0;

    void CreateCollider();
    void CreateAnimator();
    void CreatRigidbody();
    void CreatAI();


public:
    virtual void BeginOverlap(CCollider* _Other) {};
    virtual void OnOverlap(CCollider* _Other) {};
    virtual void EndOverlap(CCollider* _Other) {};

    friend class CEventMge;
};

