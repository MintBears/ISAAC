#pragma once
#include "CObj.h"

class CTexture;
class CCollider;


class CMap :
	public CObj
{
public:
	CMap(Vec2 _vPos, Vec2 _vScale);
	virtual ~CMap();

private:
	CTexture*	m_pTex;

	Vec2		m_vOffset;

	UINT		m_fWallScale;


public : 

	UINT GetWallScale() { return m_fWallScale; }
	Vec2 GetOffset() { return m_vOffset; }

public:

	virtual void tick() override;
	virtual void final_tick() override;
	virtual void render(HDC _dc) override;

private:
	void ImageRender(HDC _dc, CTexture* m_pTex);

	CLONE(CMap)

public:
	virtual void BeginOverlap(CCollider* _Other) {};
	virtual void OnOverlap(CCollider* _Other) {};
	virtual void EndOverlap(CCollider* _Other) {};
};