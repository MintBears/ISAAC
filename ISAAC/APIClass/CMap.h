#pragma once
#include "CObj.h"

class CTexture;
class CCollider;

class CMap :
	public CObj
{
public:
	CMap();
	virtual ~CMap();

private:
	CTexture*	m_pTex;

	Vec2		m_vOffset;

	UINT		m_fWallScale;
	CCollider*	m_CameraCollider;

public:

	virtual void tick() override;
	virtual void final_tick() override;
	virtual void render(HDC _dc) override;

private:
	void ImageRender(HDC _dc, CTexture* m_pTex);

	CLONE(CMap)
};