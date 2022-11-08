#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMap.h"
#include "CCamera.h"
#include "CCameraObj.h"

#include "CCollisionMgr.h"
#include "CPanelUI.h"

void CStartLevel::init()
{
	//화면 해상도
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	//택스트 로딩
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"PlayUIBackGround", L"Map\\PlayUIBackGround.bmp");
	CTexture* pMapTex = CResMgr::GetInst()->LoadTexture(L"MainMap_1", L"Map\\MainMap_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"Monster", L"texture\\magicmushroom.bmp");

	// UI 배치
	// Button 이 사용할 텍스쳐
	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetPos(Vec2(0.f, 0.f));
	pPanelUI->SetIdleTex(pPanelTex);
	pPanelUI->SetIsMove(false);
	pPanelUI->SetLayerType(LAYER::UI);
	AddObject(pPanelUI, pPanelUI->GetLayerType());

	//map 배치
	CMap* pMap = new CMap(Vec2(0.f, (FLOAT)(pPanelUI->GetIdleTex()->Height())), Vec2(pMapTex->Widht(), pMapTex->Height()));
	pMap->SetLayerType(LAYER::BACKGROUND);
	AddObject(pMap, pMap->GetLayerType());

	//캐릭터 로드
	m_Player = new CPlayer(Vec2((FLOAT)(CEngine::GetInst()->GetResolution().x / 2), (FLOAT)(CEngine::GetInst()->GetResolution().y / 2)), Vec2(30.f, 33.f));
	m_Player->SetLayerType(LAYER::PLAYER);
	AddObject(m_Player, m_Player->GetLayerType());

	//카메라 초기세팅
	CCamera::GetInst()->SetLook(m_Player->GetPos());

	//몬스터 로드
	//CMonster* Monster = new CMonster;
	//Monster->SetPos(Vec2(50.f, 50.f));
	//Monster->SetScale(Vec2(100.f, 100.f));
	//Monster->SetLayerType(LAYER::MONSTER);
	//AddObject(Monster, Monster->GetLayerType());

	m_pCameraRoom = new CCameraObj(pMap->GetOffset(), pMap->GetScale());
	m_pCameraRoom->SetLayerType(LAYER::CAMERA);
	AddObject(m_pCameraRoom, m_pCameraRoom->GetLayerType());



	//level의 충돌 체크(여기에 적힌 충돌들만 충돌 체크 하기로했다.)
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::BACKGROUND, LAYER::PLAYER);
	//CCollisionMgr::GetInst()->LayerCheck(LAYER::BACKGROUND, LAYER::PLAYER_PROJECTILE);
	//CCollisionMgr::GetInst()->LayerCheck(LAYER::BACKGROUND, LAYER::MONSTER);
	//CCollisionMgr::GetInst()->LayerCheck(LAYER::BACKGROUND, LAYER::MONSTER_PROJECTILE);


}

void CStartLevel::CreateUI()
{
	


	

}