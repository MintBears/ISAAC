#pragma once
#include "CObj.h"

class CTexture;
class CMap :
	public CObj
{
public:
	CMap();
	virtual ~CMap();

private:
	CTexture* m_pTex;
	CTexture* m_pUI;
public:

	virtual void final_tick() override;
	virtual void render(HDC _dc) override;

private:
	void ImageRender(HDC _dc, CTexture* m_pTex);

	CLONE(CMap)
};