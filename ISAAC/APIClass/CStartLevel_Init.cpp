#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMap.h"
#include "CCamera.h"

#include "CCollisionMgr.h"
#include "CPanelUI.h"

void CStartLevel::init()
{
	//화면 해상도
	Vec2 vResolution = CEngine::GetInst()->GetResolution();



	// UI 배치
	// Button 이 사용할 텍스쳐
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"PlayUIBackGround", L"Map\\PlayUIBackGround.bmp");

	// Panel UI
	m_pPanelUI = new CPanelUI;
	m_pPanelUI->SetIdleTex(pPanelTex);
	m_pPanelUI->SetIsMove(false);
	m_pPanelUI->SetPos(Vec2(0.f, 0.f));
	m_pPanelUI->SetLayerType(LAYER::UI);

	AddObject(m_pPanelUI, m_pPanelUI->GetLayerType());

	//map 배치

	//택스트 로딩
	CResMgr::GetInst()->LoadTexture(L"Monster", L"texture\\magicmushroom.bmp");

	//맵 꾸미지
	CMap* pMap = new CMap;
	pMap->SetPos(Vec2(0.f, (FLOAT)(m_pPanelUI->GetIdleTex()->Height())));

	wchar_t szBuff[256] = {};
	swprintf_s(szBuff, L"FPS : %f %f", pMap->GetPos().x, pMap->GetPos().y);
	SetWindowText(CEngine::GetInst()->GethMainWnd(), szBuff);

	pMap->SetLayerType(LAYER::BACKGROUND);
	AddObject(pMap, pMap->GetLayerType());
	//캐릭터 로드
	m_Player = new CPlayer;
	m_Player->SetPos(Vec2((FLOAT)(CEngine::GetInst()->GetResolution().x / 2), (FLOAT)(CEngine::GetInst()->GetResolution().y / 2)));
	m_Player->SetScale(Vec2(100.f, 100.f));
	m_Player->SetLayerType(LAYER::PLAYER);
	AddObject(m_Player, m_Player->GetLayerType());
	//카메라 초기세팅
	CCamera::GetInst()->SetLook(m_Player->GetPos());


	//몬스터 로드
	CMonster* Monster = new CMonster;
	Monster->SetPos(Vec2(50.f, 50.f));
	Monster->SetScale(Vec2(100.f, 100.f));
	Monster->SetLayerType(LAYER::MONSTER);
	AddObject(Monster, Monster->GetLayerType());
	//level의 충돌 체크(여기에 적힌 충돌들만 충돌 체크 하기로했다.)
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);

}

void CStartLevel::CreateUI()
{
	


	

}