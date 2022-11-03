#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CAI.h"
#include "CIdleState.h"
#include "CtraceState.h"

CMonster::CMonster()
	: m_HP(3)
	, m_Speed(100.f)
	, m_pTex(nullptr)
	, m_tInfo{}
	, m_iHp(3)
	, m_fCollisionTime(0.f)
	, m_fInvincibleTime(1.f)
	, m_bisCollision(false)
{
	CreateCollider();
	CreatAI();

	//충돌체 체크
	GetCollider()->SetScale(Vec2(150.f, 150.f));
	m_pTex = CResMgr::GetInst()->FindTexture(L"Monster");

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


	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255 * fRatio);
	//tBlend.SourceConstantAlpha = 0;


	AlphaBlend(_dc, (int)(vPos.x - m_pTex->Widht() / 2.0f)
		, (int)(vPos.y - m_pTex->Height() / 2.0f)
		, m_pTex->Widht()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0, 0
		, m_pTex->Widht()
		, m_pTex->Height()
		, tBlend);

	CObj::render(_dc);
}

void CMonster::BeginOverlap(CCollider* _Other)
{
	m_bisCollision = true;

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
