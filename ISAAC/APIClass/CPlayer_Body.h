#pragma once
#include "CObj.h"
class CPlayer_Body :
    public CObj
{
public:
    CPlayer_Body();
    virtual ~CPlayer_Body();

private:

public:

    virtual void tick() override;
    virtual void render(HDC _dc) override;

    CLONE(CPlayer_Body)
};

