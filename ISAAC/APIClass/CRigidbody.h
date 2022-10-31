#pragma once
#include "CComponent.h"
class CRigidbody :
    public CComponent
{
public:
    CRigidbody(CObj* _pOwner);
    CRigidbody(const CRigidbody& _other);
    ~CRigidbody();

private:

    Vec2            m_vVelocity;        //�ӵ�
    Vec2            m_vForce;           //��
    float           m_fMass;            //����

    float           m_fFriction;        //������
    float           m_fFrictionScale;   //�������

    float           m_fVelocityLimit;   //���Ѽӵ�

    //�߷� ����
    bool            m_bGround;          //��üũ


public:
    void AddForce(Vec2 _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }


    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec2 GetVelocity() { return m_vVelocity; }

    void AddVelocity(Vec2 _vAddV) { m_vVelocity += _vAddV; }

    void SetFriction(float _fFriction) { m_fFriction = _fFriction; }
    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }
    void IsGround(bool _bGround) { m_bGround = _bGround; }




public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CRigidbody)
    
};

