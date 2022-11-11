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
    FLOAT       m_fSpeed;           //미사일 속도
    FLOAT       m_fDegree;          //미사일 방향
    FLOAT       m_fLifeTime;        //미사일 생존시간
    bool        a;
    //CTexture*   m_pTex;             //미사일 이미지

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

