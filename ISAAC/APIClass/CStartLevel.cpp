#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"

#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CRigidbody.h"

#include "CCamera.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMap.h"
#include "CForce.h"
#include "CPlatform.h"
#include "CCameraObj.h"



CStartLevel::CStartLevel()
	: m_Player(nullptr)
	, m_pCameraRoom(nullptr)
	, m_pMap(nullptr)
{
}

CStartLevel::~CStartLevel()
{

}

void CStartLevel::tick()
{
	//카메라 세팅
	//Vec2 CameraCorrection = Vec2(0.f, -50.f);
	//잠시 폐기
	//CCamera::GetInst()->SetLook(m_Player->GetPos());
	//CCamera::GetInst()->SetPos(m_pMap->GetOffset());
	//CCamera::GetInst()->SetCamRoomPos(m_pMap->GetPos(), m_pMap->GetPos() + m_pMap->GetScale());
	CLevel::tick();


	if (IsTap(KEY::ENTER))
	{
		//CCamera::GetInst()->FadeOut(1.0f);
		//CCamera::GetInst()->FadeIn(1.0f);
		//CCamera::GetInst()->CameraShake(20.f, 300.f, 0.5f);
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	/*
	if (IsTap(KEY::LBTN))
	{
		//중앙기준으로 퍼지는힘 작용
		CForce* pForce = new CForce;
		pForce->SetLifeTime(5.0f);
		pForce->SetForceScale(200.f);
		pForce->SetForceRadius(250.f);
		
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
		
		Instantiate(pForce, vMousePos, LAYER::FORCE);
		
	}

	if (IsTap(KEY::RBTN))
	{
		CPlatform* pPlatform = new CPlatform;

		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		Instantiate(pPlatform, vMousePos, LAYER::PLATFORM);
	}
	*/
}

void CStartLevel::Enter()
{
	init();
}

void CStartLevel::Exit()
{
	DeleteAllobject();
}
