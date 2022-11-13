#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CPlayer.h"

#include "CAI.h"
#include "CIdleState.h"
#include "CtraceState.h"

CMonster::CMonster(Vec2 _vPos, Vec2 _vScale)
	: m_HP(3)
	, m_Speed(100.f)
	, m_pTex(nullptr)
	, m_tInfo{}
	, m_iHp(3)
	, m_fCollisionTime(0.f)
	, m_fInvincibleTime(1.f)
	, m_bisCollision(false)
{
	SetPos(_vPos);
	SetScale(_vScale);

	CreateCollider();
	CreateAnimator();
	CreatAI();

	//충돌체 체크
	GetCollider()->SetScale(GetScale());

	//Animator
	m_pTex = CResMgr::GetInst()->LoadTexture(L"moterfly", L"Monster\\moterfly.bmp");

	//MoveLook
	GetCAnimator()->CreateAnimation(L"moterfly", m_pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f,0.f), 2, 0.1f);
	 GetCAnimator()->FindAnimation(L"moterfly")->Save(L"animation\\moterfly.anim");

	GetCAnimator()->Play(L"moterfly", true);

	m_tInfo.m_fSpeed = 100.f;
	m_tInfo.m_fDetectRange = 500.f;

	//ai 설정
	GetCAI()->AddState(L"Idle", new CIdleState);
	GetCAI()->AddState(L"Trace", new CtraceState);

	GetCAI()->ChangeState(L"Idle");
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
	CObj::tick();

	//사망
	if (m_iHp == 0)
	{
		//캐릭터가 갑자기 죽으면 애러 뜨니까 잠시 주석
		SetDead();
	}
}

void CMonster::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	static float fRatio = 0.f;
	static float Dir = 1.0f;
	fRatio += DT * Dir * 8.0f;
	if (1.0f < fRatio)
	{
		fRatio = 1.0f;
		Dir = -1.0f;
	}
	else if (fRatio < 0.f)
	{
		fRatio = 0.0f;
		Dir = 1.0f;
	}
	CObj::render(_dc);
}

void CMonster::BeginOverlap(CCollider* _Other)
{
	//m_bisCollision = true;

	if (_Other->GetOwner()->GetLayerType() == LAYER::PLAYER_PROJECTILE)
	{
		if (m_fCollisionTime == 0.f)
		{
			//충돌처리
			m_iHp--;
		}


	}

}

void CMonster::OnOverlap(CCollider* _Other)
{

}

void CMonster::EndOverlap(CCollider* _Other)
{
	m_bisCollision = false;
}
