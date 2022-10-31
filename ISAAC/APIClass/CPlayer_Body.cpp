#include "pch.h"
#include "CPlayer_Body.h"

#include "CResMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

CPlayer_Body::CPlayer_Body()
{
	CreateAnimator();

	CTexture* Head = CResMgr::GetInst()->LoadTexture(L"Head", L"texture\\Head.bmp");
	CTexture* Body = CResMgr::GetInst()->LoadTexture(L"Body", L"texture\\Body.bmp");
	//MoveBody
	
	GetCAnimator()->CreateAnimation(L"LeftMove", Body, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(0.f, 5.f), 10, 0.1f);
	GetCAnimator()->FindAnimation(L"LeftMove")->Save(L"animation\\LeftMove.anim");
	GetCAnimator()->CreateAnimation(L"RightMove", Body, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(0.f, 5.f), 10, 0.1f);
	GetCAnimator()->FindAnimation(L"RightMove")->Save(L"animation\\RightMove.anim");
	GetCAnimator()->CreateAnimation(L"UpMove", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 5.f), 10, 0.1f);
	GetCAnimator()->FindAnimation(L"UpMove")->Save(L"animation\\UpMove.anim");
	GetCAnimator()->CreateAnimation(L"DownMove", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 5.f), 10, 0.1f);
	GetCAnimator()->FindAnimation(L"DownMove")->Save(L"animation\\DownMove.anim");
}

CPlayer_Body::~CPlayer_Body()
{
}

void CPlayer_Body::tick()
{
}

void CPlayer_Body::render(HDC _dc)
{
	CObj::render(_dc);
}
