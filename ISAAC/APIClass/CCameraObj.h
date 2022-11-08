#pragma once
#include "CObj.h"

class CCameraObj :
    public CObj
{
private:

public:
    CCameraObj(Vec2 _vPos, Vec2 _vScale);
    virtual ~CCameraObj();

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CCameraObj)
};

