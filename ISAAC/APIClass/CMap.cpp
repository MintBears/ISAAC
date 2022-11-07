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
	, m_fWallScale(90)
	, m_CameraCollider(nullptr)
{
	//이미지 추가
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MainMap_1", L"Map\\MainMap_1.bmp");
	SetScale(Vec2(m_pTex->Widht(), m_pTex->Height()));

	//콜리더 추가
	CreateCollider();
	m_CameraCollider = new CCollider(this);
	//캐릭터와 맵간의 충돌 
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(m_pTex->Widht() - (m_fWallScale * 2), m_pTex->Height() - (m_fWallScale * 2)));
	//카메라와 맵간의 충돌
	m_CameraCollider->SetOffsetPos(Vec2(0.f, 0.f));
	m_CameraCollider->SetScale(GetScale());
}

CMap::~CMap()
{
	DEL(m_CameraCollider);
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
	//if (nullptr != m_CameraCollider)
	//{
	//	m_CameraCollider->render(_dc);
	//}
	ImageRender(_dc , m_pTex);
	CObj::render(_dc);
}

void CMap::ImageRender(HDC _dc , CTexture* m_pTex)
{
	Vec2 Pos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 Size = GetScale();

	BitBlt(_dc
		, Pos.x
		, Pos.y
		, m_pTex->Widht()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0
		, 0
		, SRCCOPY);



	/*
	tAnimFrm frm = m_vecFrm[m_iCurFrm];

	BitBlt(_dc
		, (int)(Pos.x - frm.Size.x / 2.0f + frm.Offset.x), (int)(Pos.y - frm.Size.y / 2.0f + frm.Offset.y)
		, (int)frm.Size.x, (int)frm.Size.y
		, m_pAtlas->GetDC()
		, (int)frm.LeftTopPos.x, (int)frm.LeftTopPos.y
		, (int)frm.Size.x, (int)frm.Size.y
		, RGB(255, 0, 255));
	*/
}
