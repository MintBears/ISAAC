#include "pch.h"
#include "CMap.h"

#include "CEngine.h"

#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CStartLevel.h"
#include "CPanelUI.h"
#include "CPlayer.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CRigidbody.h"

CMap::CMap(Vec2 _vPos, Vec2 _vScale)
	: m_pTex(nullptr)
	, m_fWallScale(90)	
{
	SetPos(_vPos);
	SetScale(_vScale);

	m_pTex = CResMgr::GetInst()->FindTexture(L"MainMap_1");
	
	//캐릭터와 맵간의 충돌체만들기
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(GetScale().x / 2, GetScale().y / 2));
	GetCollider()->SetScale(Vec2(GetScale().x - (m_fWallScale * 2), GetScale().y - (m_fWallScale * 2)));

	m_vOffset = GetPos() + Vec2(GetScale().x / 2, GetScale().y / 2);
}

CMap::~CMap()
{
}


void CMap::tick()
{

}

void CMap::final_tick()
{
	CObj::final_tick();
}

void CMap::render(HDC _dc)
{

	ImageRender(_dc, m_pTex);
	CObj::render(_dc);

}

void CMap::ImageRender(HDC _dc , CTexture* m_pTex)
{
	Vec2 Pos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 Size = GetScale();

	BitBlt(_dc
		, (int)Pos.x
		, (int)Pos.y
		, (int)GetScale().x
		, (int)GetScale().y
		, m_pTex->GetDC()
		, 0
		, 0
		, SRCCOPY);
}

