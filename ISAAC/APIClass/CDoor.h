#pragma once
#include "CObj.h"
class CDoor :
    public CObj
{
public:
	CDoor(Vec2 _vPos, Vec2 _vScale);
	virtual ~CDoor();

private:

public:



public:

	virtual void tick() override;
	virtual void final_tick() override;
	virtual void render(HDC _dc) override;

private:
	CLONE(CDoor)

public:
	virtual void BeginOverlap(CCollider* _Other) {};
	virtual void OnOverlap(CCollider* _Other) {};
	virtual void EndOverlap(CCollider* _Other) {};
};

