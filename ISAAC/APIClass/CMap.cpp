#include "pch.h"
#include "CMap.h"

#include "CEngine.h"

#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CStartLevel.h"
#include "CPanelUI.h"

#include "CTexture.h"
#include "CCollider.h"

CMap::CMap()
	: m_pTex(nullptr)
{
	//이미지 추가
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MainMap_1", L"Map\\MainMap_1.bmp");


	//콜리더 추가
	CreateCollider();
}

CMap::~CMap()
{
}


void CMap::tick()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
}

void CMap::final_tick()
{
}

void CMap::render(HDC _dc)
{
	ImageRender(_dc , m_pTex);
}

void CMap::ImageRender(HDC _dc , CTexture* m_pTex)
{
	BitBlt(_dc
		, 0
		, 0 + GetPos().y
		, m_pTex->Widht()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0
		, 0
		, SRCCOPY);
}
