#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CMissile::CMissile(Vec2 _vPos, Vec2 _vScale)
	: m_fSpeed(400.f)
	, m_fDegree(80.f)
	, m_fLifeTime(1.0f)
	, a(true)

{
	SetPos(_vPos);
	SetScale(_vScale);

	CreateCollider();
	CreateAnimator();

	GetCollider()->SetScale(GetScale());

	CTexture* Missile = CResMgr::GetInst()->LoadTexture(L"Missile", L"texture\\Player\\Player_Missile.bmp");
	GetCAnimator()->CreateAnimation(L"Missile", Missile, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(0.f, 0.f), 16, 0.02f);
	GetCAnimator()->FindAnimation(L"Missile")->Save(L"animation\\Missile.anim");

	GetCAnimator()->Stop(L"Missile");
}

CMissile::~CMissile()
{
}

void CMissile::tick()
{
	Vec2 vPos = GetPos();
	//vPos.y -= m_fSpeed * DT;
	float fRadian = (m_fDegree * PI) / 180.f;

	vPos.x += m_fSpeed * cosf(fRadian) * DT;
	vPos.y -= m_fSpeed * sinf(fRadian) * DT;
	SetPos(vPos);

	m_fLifeTime -= DT;

	if (m_fLifeTime < 0.f && a == true)
	{
		GetCAnimator()->Play(L"Missile", false);
		a = false;
	}

	CObj::tick();
}

void CMissile::render(HDC _dc)
{
	//Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	//Vec2 vSize = GetScale();
	//Ellipse(_dc, (int)(vPos.x - vSize.x / 2.f)
	//			  , (int)(vPos.y - vSize.y / 2.f)
	//			  , (int)(vPos.x + vSize.x / 2.f)
	//			  , (int)(vPos.y + vSize.y / 2.f));
	//
	CObj::render(_dc);
}

void CMissile::BeginOverlap(CCollider* _Other)
{
	SetDead();
}
