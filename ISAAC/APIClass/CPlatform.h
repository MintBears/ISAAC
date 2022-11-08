#pragma once
#include "CObj.h"
class CPlayer;

class CPlatform :
    public CObj
{

private:
    CPlayer* m_pPlayer;
public:
    CPlatform(Vec2 _vPos, Vec2 _vScale);
    ~CPlatform();

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CPlatform)

    virtual void BeginOverlap(CCollider* _Other) override;
    virtual void OnOverlap(CCollider* _Other) override;
    virtual void EndOverlap(CCollider* _Other) override;
private:

};

