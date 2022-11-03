#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMap.h"

#include "CCollisionMgr.h"
#include "CPanelUI.h"

void CStartLevel::init()
{
	// UI 배치
	//CreateUI();

	//map 배치

	//택스트 로딩
	CResMgr::GetInst()->LoadTexture(L"Monster", L"texture\\magicmushroom.bmp");

	CMap* Map = new CMap;
	AddObject(Map, LAYER::BACKGROUND);

	Player = new CPlayer;
	Player->SetPos(Vec2((FLOAT)(CEngine::GetInst()->GetResolution().x / 2), (FLOAT)(CEngine::GetInst()->GetResolution().y / 2)));
	Player->SetScale(Vec2(100.f, 100.f));
	AddObject(Player, LAYER::PLAYER);

	CMonster* Monster = new CMonster;
	Monster->SetPos(Vec2(50.f, 50.f));
	Monster->SetScale(Vec2(100.f, 100.f));
	AddObject(Monster, LAYER::MONSTER);

	//level의 충돌 체크
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);


	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(Resolution / 2.f);


}

void CStartLevel::CreateUI()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// Button 이 사용할 텍스쳐
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"Map\\MainMap_1.bmp");

	// Panel UI
	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetIdleTex(pPanelTex);
	pPanelUI->SetIsMove(false);
	pPanelUI->SetPos(Vec2(0.f,0.f));

	AddObject(pPanelUI, LAYER::BACKGROUND);

}