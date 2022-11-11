#pragma once
#include "CObj.h"

class CTexture;

class CMissile :
    public CObj
{
public:
    CMissile(Vec2 _vPos, Vec2 _vScale);
    virtual ~CMissile();

private:
    FLOAT       m_fSpeed;           //�̻��� �ӵ�
    FLOAT       m_fDegree;          //�̻��� ����
    FLOAT       m_fLifeTime;        //�̻��� �����ð�
    bool        a;
    //CTexture*   m_pTex;             //�̻��� �̹���

public:
    void SetSpeed(FLOAT _speed) { m_fSpeed = _speed; }
    void SetDir(FLOAT _fDegree) { m_fDegree = _fDegree; }

    //CTexture* GetTex() { return m_pTex; }
    //void SetTex(CTexture* _pTex) { m_pTex = _pTex; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc)override;

    CLONE(CMissile)

    virtual void BeginOverlap(CCollider* _Other) override;
};

