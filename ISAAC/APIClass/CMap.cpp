#include "pch.h"
#include "CMap.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CMap::CMap()
	: m_pTex(nullptr)
	, m_pUI(nullptr)
{
	//이미지 추가
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayUIBackGround", L"Map\\PlayUIBackGround.bmp");
	m_pUI = CResMgr::GetInst()->LoadTexture(L"MainMap_1", L"Map\\MainMap_1.bmp");

	//콜리더 추가
	CreateCollider();
}

CMap::~CMap()
{
}


void CMap::final_tick()
{
}

void CMap::render(HDC _dc)
{
	ImageRender(_dc, m_pUI);
	ImageRender(_dc , m_pTex);
}

void CMap::ImageRender(HDC _dc , CTexture* m_pTex)
{
	BitBlt(_dc
		, 0
		, 0
		, m_pTex->Widht()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0
		, 0
		, SRCCOPY);
}
